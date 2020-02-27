#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#include "stack.h"

/***********
*Function Name: isLeftBracket
*Input: char c
*Output: int
*Function Operation:
	Examines if the character in question is one of the four left brackets <,(,[,{
*************/

int isLeftBracket(char c) {
	if (c == '(' || c == '<' || c == '{' || c == '[') {
		return 1;
	}
	else return 0;
}

/***********
*Function Name: isRightBracket
*Input: char c
*Output: int
*Function Operation:
	Examines if the character in question is one of the four right brackets >,),},]
*************/

int isRightBracket(char c) {
	if (c == ')' || c == '>' || c == '}' || c == ']') {
		return 1;
	}
	else return 0;
}

/***********
*Function Name: isLegalString
*Input: char str[]
*Output: int
*Function Operation:
	Examines if the string in question contains a corresponding R bracket
	for every L bracket.
*************/

int isLegalString(char str[]) {
	//Initiates the stack where the left brackets will be stored (as elements)
	Stack* stack = initStack();
	Element LeftBracket;

	//This will count how many lone right brackets there are
	int counter = 0;

	//Examines the string for left brackets
	for (int i = 0; str[i] != '\0'; i++) {
		if (isLeftBracket(str[i])) {
			LeftBracket.c = str[i];
			//Pushes left brackets into the stack
			push(stack, LeftBracket);
		}
	}

	//Examines the string again, this time for corresponding right brackets
	for (int j = 0; str[j] != '\0'; j++) {
		Element inspection = top(stack);
		if (isRightBracket(str[j])) {
			//Counting right bracket
			counter++;
			//Testing to see if right bracket has a match
			switch (str[j]) {
			//Switch/case is used to avoid magic numbers, make code more readable
			case ')': {
				if (inspection.c == '(') {
					//Removing the matching bracket from the stack
					pop(stack);
					//Downcounting number of unmatched right brackets
					counter--;
				}
				break;
			}

			case ']': {
				if (inspection.c == '[') {
					pop(stack);
					counter--;
				}
				break;
			}

			case '}': {
				if (inspection.c == '{') {
					pop(stack);
					counter--;
				}
				break;
			}
			case '>': {
				if (inspection.c == '<') {
					pop(stack);
					counter--;
				}
				break;
			}

			default: {
				break;
			}

			}
		}
	}

	//If there are no lone left brackets (empty stack) and no lone right brackets (counter = 0)
	if (stack->topIndex == -1 && counter == 0) {
		return 1;
	}
	else return 0;
}
