/*******************************************************************************************
* File Name :	HShah5830-DataStructure-Midterm.cpp
* Description : PROG8130 Section 1 midterm starter code
*
*				I have written the code to take the supplied data and put it into a sorted
*				Singly Linked List.
*
*				Create the two functions:
*					removeDuplicates - which will delete only the nodes that have the same data in it
*					removeLastNode - will delete the last node from list
*
*				After the program is complete use the provided function to print out the list.
*
* Author : Harsh Shah
* Date : 21 Oct 2021
********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS	12					// the number of data items to be used in list
#define MAX_STRING_LEN			10					// the number of characters maximum (including \0 char)

// definition of linked list data nodes (DO NOT CHANGE)
typedef struct LinkedListNode {
	struct LinkedListNode* ptrNextNode;		// pointer to next node in list (NULL if the end)
	char						NameData[MAX_STRING_LEN];		// the name to be stored (no need to store index)
} LinkedListNodeDef;

// prototypes
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, const char* NameData);
void PrintLinkedList(LinkedListNodeDef* ptrHead);
LinkedListNodeDef* removeDuplicates(LinkedListNodeDef* ptrHead);
void removeLastNode(LinkedListNodeDef* ptrHead);


// data to be used for this programming question (DO NOT CHANGE)
const char* iData[NUMBER_OF_DATA_ITEMS] = {
	{"fish" },
	{ "airplane" },
	{ "allan" },
	{ "carrot" },
	{ "pickels" },
	{ "fish" },
	{ "milk" },
	{ "kiwi" },
	{ "orange" },
	{ "kiwi" },
	{ "butter" },
	{ "car" }
};

// your output from the program should look like this when working correctly:
//Data before Linked List Operations is :
//1.      fish
//2.      airplane
//3.      allan
//4.      carrot
//5.      pickels
//6.      fish
//7.      milk
//8.      kiwi
//9.      orange
//10.     kiwi
//11.     butter
//12.     car
//
//Data after inserted into linked list in alphabetical order :
//1.      airplane
//2.      allan
//3.      butter
//4.      car
//5.      carrot
//6.      fish
//7.      fish
//8.      kiwi
//9.      kiwi
//10.     milk
//11.     orange
//12.     pickels
//
//Data after processing :
//1.      airplane
//2.      allan
//3.      butter
//4.      car
//5.      carrot
//6.      fish
//7.      kiwi
//8.      milk
//9.      orange

// START OF CODE YOU ARE ALLOWED TO CHANGE

// FUNCTION      : removeDuplicates()
// DESCRIPTION   : This function will iterate through a linked list and remove all duplicate entries 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* removeDuplicates(LinkedListNodeDef* ptrHead) {

	/*
	* 
	* Algorithm :
	* 
	* considering that data is sorted then the repetative elements would be next to each other. 
	* start picking up the elements from the list.
	* start looking for the match from the next node. 
	* if match is found, assign the next iteam's address and remove the duplicate element from memory.
	* else move on to the next element for the match.
	* 
	*/
	LinkedListNodeDef *firstNode = NULL, *secondNode = NULL, *dup = NULL;
	
	firstNode = ptrHead;
	
	//checking if the first and the next node are not empty.
	while (firstNode != NULL && firstNode->ptrNextNode != NULL) {

		secondNode = firstNode;

		//iterating over all the member to find a match
		while (secondNode->ptrNextNode != NULL) {

			//checking if the current and next items are match. considering that they are sorted.
			if (strcmp(firstNode->NameData,secondNode->ptrNextNode->NameData) == 0) {

				//if they match, then skiping one element and assigining the address that removes the duplicate.
				secondNode->ptrNextNode = secondNode->ptrNextNode->ptrNextNode;
				
				if (dup != NULL)
				{
					//removing from the memory.
					free(dup);
				}
				
			}
			else {
				//if it is not a match.
				secondNode = secondNode->ptrNextNode;
			}
				
		}
		//moving on to the next element.
		firstNode = firstNode->ptrNextNode;
	}
	return ptrHead;
}

// FUNCTION      : removeLastNode()
// DESCRIPTION   : This function will iterate through a linked list and remove/free the last entry
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : Nothing
void removeLastNode(LinkedListNodeDef* ptrHead) {

	/*
	*  Algorithm : 
	*  Go to the last elemnt.
	*  update the second last elemnt's next node pointer to NULL
	*  clear the memory 
	*  
	*/
	struct LinkedListNode *ptr = NULL, *ptrTemp = NULL;
	ptr = ptrHead;

	//iterating over elements
	while (ptr->ptrNextNode != NULL)
	{
		ptrTemp = ptr;
		ptr = ptr->ptrNextNode;
	}

	if (ptrTemp != NULL)
	{
		//Updating the second last node's next pointer
		ptrTemp->ptrNextNode = NULL;
		//removing the last node from memory.
		free(ptr);
	}

	return;
}
// END OF CODE YOU ARE ALLOWED TO CHANGE

// DO NOT CHANGE ANY OF THE CODE BELOW!

int main(void) {
	int i;

	// define linked list head
	struct LinkedListNode* ptrHead = NULL;

	// Print out the input data
	printf("Data before Linked List Operations is:\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++) {
		printf("%d.\t%s\n", i + 1, iData[i]);
		ptrHead = AddToLinkedList(ptrHead, iData[i]);
	}

	// now print out the list in order it is stored starting at head
	printf("\nData after inserted into linked list in alphabetical order:\n");
	PrintLinkedList(ptrHead);

	removeDuplicates(ptrHead);
	removeLastNode(ptrHead);

	// now print out the list in order it is stored starting at head after required operations are complete
	printf("Data after processing:\n");
	PrintLinkedList(ptrHead);

	return 0;
}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized alphabetically 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, const char* NameData) {
	LinkedListNodeDef* ptrCurrent = ptrHead;
	LinkedListNodeDef* ptrNew = NULL;

	// allocate a new node to be added to linked list
	ptrNew = (LinkedListNodeDef*)calloc(1, sizeof LinkedListNode);
	if (ptrNew == NULL) {
		printf("calloc failure!!\n");
		exit(-1);
	}

	// load new node with data
	ptrNew->ptrNextNode = NULL;
	strncpy_s(ptrNew->NameData, NameData, MAX_STRING_LEN);

	if (ptrCurrent == NULL) {		// if list is empty simply change head to be new node
		ptrHead = ptrNew;
	}
	else {
		LinkedListNodeDef* ptrLast = NULL;

		// stop traversing if we reach the end of the list
		while (ptrCurrent != NULL) {
			// check for alphabetic order
			if (strncmp(ptrCurrent->NameData, NameData, MAX_STRING_LEN) > 0)
			{
				// we found where new node should go so need to link in to list
				if (ptrLast == NULL)		// if the last pointer is NULL this means no traversing happened so put on beginning
					ptrHead = ptrNew;
				else						// otherwise link it into chain between last node and current
					ptrLast->ptrNextNode = ptrNew;
				ptrNew->ptrNextNode = ptrCurrent;
				return ptrHead;
			}
			ptrLast = ptrCurrent;			// keep track of last node because sometimes it is needed to insert new data
			ptrCurrent = ptrCurrent->ptrNextNode;	// traverse to next node
		}
		if (ptrCurrent == NULL) {			// if the current pointer is NULL that means we reached the end of the list so put it there
			ptrLast->ptrNextNode = ptrNew;
		}
	}
	return ptrHead;
}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function takes an input of the head of the linked list, then loops through
//				   and prints each word in the linked list until the ptrNextNode is NULL.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead) {
	int i = 0;
	LinkedListNodeDef* ptrCurrent = ptrHead;

	// check for empty list
	if (ptrCurrent != NULL) {
		// traverse list looking for the end printing the items out as we go
		for (i = 1; ptrCurrent != NULL; i++)
		{
			printf("%i.\t%s\n", i, ptrCurrent->NameData);
			ptrCurrent = ptrCurrent->ptrNextNode;
		}
	}
	printf("\n");
	return;
}


