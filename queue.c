
/**********************************************
*YANIV LEVY
*T.Z.316464817
*Group 01 (Computer Science)
*ass05
*File: queue.c

**********************************************/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "queue.h"
#include "stack.h"

/***********
*Function Name: initQueue
*Input: void
*Output: Queue*
*Function Operation:
	This function initiates a Queue of two stacks using malloc.
	The stacks are in turn initiated by initStack (see notes for stack.c).
	
***********/


Queue* initQueue() {
	Queue* Qstruct = (Queue*)malloc(sizeof(Queue));
	//If malloc for Qstruct fails
	if (Qstruct == NULL) {
		printf("Memory allocation returned NULL.\n File name: queue.c\n Function name: initQueue\n");
		return Qstruct;
	}


	//If malloc for Qstruct succeeds, we initialize stack 1
	Qstruct->s1 = initStack();
	//If initiation for stack 1 fails
	if (Qstruct->s1 == NULL) {
		printf("Memory allocation returned NULL.\n File name: queue.c\n Function name: initQueue\n");
		//Preventing memory leakage
		free(Qstruct);
		Qstruct = NULL;
		return Qstruct;
	}


	//If stack 1 is successfuly initialized, we initialize stack 2
	Qstruct->s2 = initStack();
	//If initiation for stack 2 fails
	if (Qstruct->s2 == NULL) {
		printf("Memory allocation returned NULL.\n File name: queue.c\n Function name: initQueue\n");
		//Preventing memory leakage from existing stacks
		free(Qstruct->s1);
		free(Qstruct);
		Qstruct = NULL;
		return Qstruct;
	}


	return Qstruct;
}


/***********
*Function Name: destroyQueue
*Input: Queue* queue
*Output: void
*Function Operation:
	Frees memory allocated for the element arrays and the "control centers" of both stack,
	and then the queue that leads to the stacks. Prevents data leak.
*************/

void destroyQueue(Queue* queue) {
	free(queue->s1->content);
	free(queue->s1);
	free(queue->s2->content);
	free(queue->s2);
	free(queue);
}

/***********
*Function Name: isQueueEmpty
*Input: Queue*
*Output: int
*Function Operation:
	Returns boolean T/F value if stack 1 is empty or not.
	(Stack 2 is only used for dequeue)
*************/

int isQueueEmpty(Queue* queue) {
	if (queue->s1->topIndex == -1) {
		return 1;
	}
	else return 0;
}

/***********
*Function Name: capacityOfQueue
*Input: Queue*
*Output: int
*Function Operation:
	Returns capacity of the element array for stack 1.
	(Stack 2 is only used for dequeue)

	NOTE!!! THIS IS capacityOfQueue, AS IT SHOULD BE! THE MISTAKE WAS ONLY IN THE SHEET FOR STACK
*************/



int capacityOfQueue(Queue* queue) {
	return queue->s1->size;
}

/***********
*Function Name: lenOfQueue
*Input: Queue*
*Output: int
*Function Operation:
	Returns how many elements are in stack 1.
	(Stack 2 is only used for dequeue)

	NOTE!!! THIS IS lenofQueue, AS IT SHOULD BE! THE MISTAKE WAS ONLY IN THE SHEET FOR STACK
*************/

int lenOfQueue(Queue* queue) {
	return (1 + queue->s1->topIndex);
}

/***********
*Function Name: enqueue
*Input: Queue*, Element
*Output: void
*Function Operation:
	Pushes element from user into Stack 1 (stack 2 is only used for dequeue...)
*************/

void enqueue(Queue* queue, Element element) {
	push(queue->s1, element);
}

/***********
*Function Name: dequeue
*Input: Queue*
*Output: Element*
*Function Operation:
	Pops content of stack 1 into stack 2 (in LIFO), and then pops the FIRST original element
	from stack 2 (FIFO for whole queue) before popping stack 2's contents back into stack 1.
*************/

Element dequeue(Queue* queue) {
	assert(!isQueueEmpty(queue));
	//Popping stack 1 into stack 2
	for (int i = queue->s1->topIndex; i > -1; i--) {
		push(queue->s2, pop(queue->s1));
	}

	//The element that is being popped is removed
	Element PopPiece = pop(queue->s2);

	//Remaining elements are popped back into stack 1
	for (int j = queue->s2->topIndex; j > -1; j--) {
		push(queue->s1, pop(queue->s2));
	}

	return PopPiece;
}

/***********
*Function Name: peek
*Input: Queue*
*Output: Element
*Function Operation:
	Tells the user what element is first in the queue without removing it.
*************/

Element peek(Queue* queue) {
	assert(!isQueueEmpty(queue));
	return queue->s1->content[0];
}