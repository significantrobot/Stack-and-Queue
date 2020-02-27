#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"


/***********
*Function Name: halveCapacity
*Input: Stack* stack
*Output: Element*
*Function Operation:
	The function uses realloc to halve the capacity of a stack when less than half of it is being used.
	Element* address is initiated at NULL in case your compiler is having a bad day.
*************/

Element* halveCapacity(Stack* stack) {
	Element* address = NULL;
	address = (Element*)realloc(stack->content, (lenOfStack(stack) / 2));
	return address;
}


/***********
*Function Name: doubleCapacity
*Input: Stack* stack
*Output: Element*
*Function Operation:
	The function uses realloc to double the capacity of a stack when the entire stack is being used.
*************/

Element* doubleCapacity(Stack* stack) {
	Element* address = NULL;
	address = (Element*)realloc(stack->content, stack->size * 2);
	return address;
}

/***********
*Function Name: initStack
*Input: void
*Output: Stack*
*Function Operation:
	The function initiates and alocates memory for a "control center" that keeps track
	of an Element* to an array of elements, stored in dynamically allocated memory.
	The stack* control center also keeps track of the capacity of the Element array
	using ->size, and of how many elements are stored therein, using ->topIndex.

	The Element* array, pointed to by ->content, is also allocated memory in this function.
*************/

Stack* initStack(){
	Stack* StackStruct = (Stack*)malloc(sizeof(Stack));
	//If the malloc fails or there is insufficient memory
	if (StackStruct == NULL) {
		printf("Memory allocation returned NULL.\n File name: stack.c\n Function name: initStack\n");
		return StackStruct;
	}
	//Initializing size, index, and pointer values
	StackStruct->size = 0;
	StackStruct->topIndex = 0;
	StackStruct->content = NULL;

	//Initializing memory for the Element* pointer
	Element* ElementStruct = (Element*)malloc(sizeof(Element));
	//If malloc fails
	if (ElementStruct == NULL) {
		printf("Memory allocation returned NULL.\n File name: stack.c\n Function name: initStack\n");
		//StackStruct must be freed to prevent leak
		free(StackStruct);
		StackStruct = NULL;
		return StackStruct;
	}
	//Re-initializing size, index, because there is now an array for them to describe
	StackStruct->size = 1;
	StackStruct->topIndex = -1;
	StackStruct->content = ElementStruct;

	return StackStruct;
}

/***********
*Function Name: destroyStack
*Input: Stack* stack
*Output: void
*Function Operation:
	Frees memory allocated for the element array and the "control center." Prevents data leak.
*************/

void destroyStack(Stack* stack) {
	free(stack->content);
	free(stack);
}

/***********
*Function Name: lenOfStack
*Input: stack*
*Output: int
*Function Operation:
	Retunns capacity of the element array (how much memory is allocated to it).

	NOTE!!! THE EXERCISE SHEET HAD A MISTAKE IN IT -- THIS *SHOULD* BE capacityOfStack
	INSTEAD OF lenOfStack, LIKE IT IS FOR THE QUEUE FUNCTIONS! DON'T GET MAD AT ME
	THAT len AND capacity ARE MIXED UP - I'M JUST DOING EXACTLY WHAT YOU TOLD US TO DO
	BECAUSE I'M A GOOD STUDENT WHO JUST WANTS A PASSING GRADE.
*************/

int lenOfStack(Stack* stack) {
	return stack->size;
}

/***********
*Function Name: capacityOfStack
*Input: stack*
*Output: int
*Function Operation:
	Retunns how many elements are in the stack.

	NOTE!!! THE EXERCISE SHEET HAD A MISTAKE IN IT -- THIS *SHOULD* BE lenOfStack
	INSTEAD OF capacityOfStack, LIKE IT IS FOR THE QUEUE FUNCTIONS! DON'T GET MAD AT ME
	THAT len AND capacity ARE MIXED UP - I'M JUST DOING EXACTLY WHAT YOU TOLD US TO DO
	BECAUSE I'M A GOOD STUDENT WHO JUST WANTS A PASSING GRADE.
*************/

int capacityOfStack(Stack* stack) {
	//1 is added because starting index is 0
	return (1 + stack->topIndex);
}

/***********
*Function Name: isStackEmpty
*Input: stack*
*Output: int
*Function Operation:
	Returns boolean T/F value if the stack is empty or not.
*************/

int isStackEmpty(Stack* stack) {
	if (stack->topIndex == -1) {
		return 1;
	}
	
	else return 0;
}

/***********
*Function Name: push
*Input: Stack* stack, Element
*Output: void
*Function Operation:
	Inserts an element recieved from the user into the stack.
*************/

void push(Stack* stack, Element element) {
	//Just a double triple check that the memory allocation was successful. An assertion of sorts
	if (stack == NULL) {
		printf("Memory allocation returned NULL.\n File name: stack.c\n Function name: initStack\n");
		return;
	}


	//If there is ample room in the stack, the element is simply pushed
	if (capacityOfStack(stack) + 1 < lenOfStack(stack)) {
		stack->topIndex++;
		stack->content[stack->topIndex] = element;
	}

	//If there isn't room, capacity is doubled with doubleCapacity before pushing element
	else if (capacityOfStack(stack) + 1 == lenOfStack(stack)) {
		//Address is temporarily stored
		Element* tempMem = doubleCapacity(stack);
		//If the allocation fails, error message is printed and no action is carried out.
		if (tempMem == NULL) {
			printf("Memory allocation returned NULL.\n File name: stack.c\n Function name: doubleCapacity\n");
			free(tempMem);
			return;
		}

		//If the allocation simply extends existing memory
		else if (tempMem == stack->content) {
			//size is doubled because capacity was doubled
			stack->size = lenOfStack(stack) * 2;
			//Element is pushed
			stack->topIndex++;
			stack->content[stack->topIndex] = element;
			return;
		}

		//If the allocation returns a new address
		else if (tempMem != stack->content) {
			//size is doubled
			stack->size = lenOfStack(stack) * 2;
			//New address attached to Element array. Old address was freed by realloc
			stack->content = tempMem;
			//Element is pushed
			stack->topIndex++;
			stack->content[stack->topIndex] = element;
			return;
		}
	}
}


/***********
*Function Name: pop
*Input: Stack* stack
*Output: Element
*Function Operation:
	Removes and returns the element at the top of the stack (LIFO).
*************/

Element pop(Stack* stack) {
	//Asserts that the stack is not empty.
	assert(!isStackEmpty(stack));

	//If more than half of the allocated memory is being used (after removal)
	if (capacityOfStack(stack) - 1 >= lenOfStack(stack)/2) {
		Element PopPiece = stack->content[stack->topIndex];
		stack->topIndex--;
		return PopPiece;
	}

	//If less than half of allocated memory is being used (after removal)
	else if (capacityOfStack(stack) - 1 < lenOfStack(stack)/2) {
		//Capacity is halved, address temporarily stored.
		Element* tempMem = halveCapacity(stack);
		//If the allocation fails, error is printed, returns NULL element.
		if (tempMem == NULL) {
			printf("Memory allocation returned NULL.\n File name: stack.c\n Function name: halveCapacity\n");
			free(tempMem);
			Element PopPiece;
			PopPiece.c = '\0';
			return PopPiece;
		}

		//If existing array was simply shrunk
		else if (tempMem == stack->content) {
			//Size was halved
			stack->size = lenOfStack(stack) / 2;
			//Storing popped element
			Element PopPiece = stack->content[stack->topIndex];
			//Element is removed
			stack->topIndex--;
			return PopPiece;
		}
		
		//If a new address is given by realloc
		else if (tempMem != stack->content) {
			//Size was halved
			stack->size = lenOfStack(stack) / 2;
			//New address associated with array pointer
			stack->content = tempMem;
			//Storing popped element
			Element PopPiece = stack->content[stack->topIndex];
			//Bye bye element
			stack->topIndex--;
			return PopPiece;
		}
	}

}

/***********
*Function Name: top
*Input: Stack* stack
*Output: Element
*Function Operation:
	Tells the user what is at the top of the stack without removing the element in question.
*************/

Element top(Stack* stack){
	//Just to be safe.
	assert(!isStackEmpty(stack));
	return stack->content[stack->topIndex];
}

/***********
*Function Name: printStack
*Input: Stack* stack
*Output: void
*Function Operation:
	Prints the contents of the stack in descending order of insertion.
*************/

void printStack(Stack* stack) {
	int Location = stack->topIndex;
	for (int i = 0; i < capacityOfStack(stack); i++) {
		printf("%d: %c\n", capacityOfStack(stack) - i, stack->content[Location - i].c);
	}

}



