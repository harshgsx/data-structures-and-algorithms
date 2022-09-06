/*******************************************************************************************
* File Name          : Hshah5830-LinkedList.c
* Description        : Prog8130 - Assignment 1: Linked Lists
*					   This program uses linked lists to hold and print a list of words
*					   organized by index number assosciated with each word. Each word can
*					   consist of maximum 30 characters.
*
* Author			 : Harsh Shah
* Date				 : 03/OCT/2021                
* StudentId			 : 8715830		
********************************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_DATA_ITEMS   10					// the number of data items to be used in list
#define NUMBER_OF_CHARACTERS_IN_WORD 30				// the number of characters in word.

// structure/typedef used for holding data
typedef struct {
	char name[NUMBER_OF_CHARACTERS_IN_WORD];
	int index;
} inputData;

// definition of linked list data nodes
typedef struct LinkedListNode {
	struct LinkedListNode* ptrNextNode;		// pointer to next node in list (NULL if the end)
	char						NameData[NUMBER_OF_CHARACTERS_IN_WORD];		// the name to be stored (no need to store index)
} LinkedListNodeDef;

// prototypes
LinkedListNodeDef* CreateLinkedList(LinkedListNodeDef* ptrHead);
LinkedListNodeDef* DeleteElementsLinkedList(LinkedListNodeDef* ptrHead);
LinkedListNodeDef* DeleteStartNodeLinkedList(LinkedListNodeDef* ptrHead);
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex, int CurrentIndex);
LinkedListNodeDef* InsertAtBeginOfLinkedList(LinkedListNodeDef* ptrHead, char* NameData);
LinkedListNodeDef* InsertAtEndOfLinkedList(LinkedListNodeDef* ptrHead, char* NameData);
LinkedListNodeDef* InsertAtIndexOfLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int InsertIndex);
void PrintLinkedList(LinkedListNodeDef* ptrHead);
void DryRun(void);

// my student number is 8715830.
// the following input data was generated as per my student id.

// input data
inputData iData[10] = {
		{ "chocolate", 7 },
		{ "carrot", 9 },
		{ "allan", 4 },
		{ "milk", 9 },
		{ "kiwi", 2 },
		{ "water", 5 },
		{ "pickels", 1 },
		{ "car", 5 },
		{ "orange", 1 },
		{ "fish", 8 }
};
//end of data for assignment

// Correct order after inserting into list is:
// 1. orange
// 2. pickels
// 3. chocolate
// 4. kiwi
// 5. carrot
// 6. car
// 7. allan
// 8. fish
// 9. water
// 10. milk
//


int main(void) {
	
	int option = 0;
	struct LinkedListNode* ptrHead = NULL;
	do
	{


		printf("\n\t...Liked List test program... \n\n\n");
		printf("---\nThe default character limit is 30 characters per word.\n---\n");
		printf("Rule 1: If a linked list position is greater than the last item in the list, the item should be placed at the end.\n");
		printf("Rule 2: If a linked list position is 0 or 1, it should be placed on the start of the list\n---\n\n");
		printf("\n MENU: \n1. Dry run (Produces predetermined output against 15830 student id) \n");
		printf("2. Create new dynamic linked list as per the two rules? \n");	
		printf("3. Delete all elements from dynamic linked list? \n");
		printf("4. Print all the elements of the dynamic linked list \n");
		printf("5. Exit.\n");
		scanf_s("%d", &option);
		switch (option)
		{
		case 1:
			DryRun();
			break;
		case 2:
			ptrHead = CreateLinkedList(ptrHead);
			break;
		case 3:
			printf("Removing elements of the linked list: \n");
			ptrHead = DeleteElementsLinkedList(ptrHead);
			break;
		case 4:
			printf("Listing Elemets of the linked list: \n");
			PrintLinkedList(ptrHead);
			break;
		case 5:	
			printf("Exiting...\n");
			break;
		}
	} while (option != 5);
	
	
	return 0;
}

// FUNCTION      : DryRun()
// DESCRIPTION   : This function showcases the assigenment task. 
// PARAMETERS    : void
// RETURNS       : void
void DryRun(void)
{

	// define linked list head
	struct LinkedListNode* ptrHead = NULL;
	int currentIndex = 1, i = 0;
	// Print out the input data
	printf("\nData before Linked List is:\n\n");
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
		printf("%s , %d\n", iData[i].name, iData[i].index);

	// insert the data into Linked List
	for (i = 0; i < NUMBER_OF_DATA_ITEMS; i++)
	{
		ptrHead = AddToLinkedList(ptrHead, iData[i].name, iData[i].index, currentIndex);
		currentIndex++;
	}
	printf("\nCorrect order after inserting into list is: \n\n");

	// printing the list starting at head.
	PrintLinkedList(ptrHead);
}

// FUNCTION      : CreateLinkedList()
// DESCRIPTION   : Creates new list from user's input.
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* CreateLinkedList(LinkedListNodeDef* ptrHead) {
	
	char inputString[NUMBER_OF_CHARACTERS_IN_WORD] = { '\0' };
	int index = 0, stringLength, choice = 0, list_index = 0;
	errno_t rc;
	
	do {
		printf("Enter String: ");
		scanf_s("%s", &inputString, NUMBER_OF_CHARACTERS_IN_WORD);
		printf("Enter Index: ");
		scanf_s("%d", &index);
		printf("Enter -1 to exit or any number to contine: ");
		scanf_s("%d", &choice);
		ptrHead = AddToLinkedList(ptrHead, inputString, index, list_index);
		list_index++;
	} while (choice != -1);


	
	return ptrHead;

}

// FUNCTION      : DeleteElementsLinkedList()
// DESCRIPTION   : Remove all the elements from the linked list
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* DeleteElementsLinkedList(LinkedListNodeDef* ptrHead) {

	if (ptrHead == NULL)
	{
		printf("Empty list. \n");
		return NULL;
	}

	LinkedListNodeDef* iteam;
	iteam = ptrHead;
	
		while (iteam->ptrNextNode != NULL)
		{
			printf("Removing %s from list.\n", iteam->NameData);
			ptrHead = DeleteStartNodeLinkedList(iteam);
			iteam = ptrHead;
		}

		if (iteam->ptrNextNode == NULL && strlen(iteam->NameData) != 0)
		{
			printf("Removing %s from list.\n", iteam->NameData);
			free(iteam);
			ptrHead = NULL;
		}


	return ptrHead;

}

// FUNCTION      : DeleteStartNodeLinkedList()
// DESCRIPTION   : Removes starting node from the list.
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* DeleteStartNodeLinkedList(LinkedListNodeDef* ptrHead) {



	LinkedListNodeDef* iteam;		
	iteam = ptrHead;	
	ptrHead = ptrHead->ptrNextNode;
	free(iteam);

	return ptrHead;

}

// FUNCTION      : AddToLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
//		           int DataIndex				- Index of data
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* AddToLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int DataIndex, int currentIndex) {
	
	//Rules : 
	/*
		If alinked list position is greater than the last item in the list, the item should be placed at the end.
		If a linked list position is 0or 1, it should be placed on the start of the list
	*/
	
	if (DataIndex == 1 || DataIndex == 0 || ptrHead == NULL)
	{
		ptrHead = InsertAtBeginOfLinkedList(ptrHead, NameData);
	}
	else if (DataIndex > currentIndex)
	{
		ptrHead = InsertAtEndOfLinkedList(ptrHead, NameData);
	}
	else
	{
		//printf("DataIndex: %d \t CurrentIndex: %d \n", DataIndex, currentIndex);
		ptrHead = InsertAtIndexOfLinkedList(ptrHead, NameData, DataIndex-1);	
	}

	return ptrHead;

}


// FUNCTION      : InsertAtBeginOfLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and addes that word to the top of the link list. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* InsertAtBeginOfLinkedList(LinkedListNodeDef* ptrHead, char* NameData) {

	LinkedListNodeDef* newIteam;
	errno_t rc;
	newIteam = (LinkedListNodeDef*)malloc(sizeof(LinkedListNodeDef));
	int stringLength = strnlen(NameData, NUMBER_OF_CHARACTERS_IN_WORD);
	
	if (newIteam != NULL) {

		rc = strncpy_s(newIteam->NameData, NameData, stringLength);
		//link the node with head.
		newIteam->ptrNextNode = ptrHead;
		//change head with this new iteam.
		ptrHead = newIteam;
	}
	
	return ptrHead;

}

// FUNCTION      : InsertAtEndOfLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list organized by priority of index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* InsertAtEndOfLinkedList(LinkedListNodeDef* ptrHead, char* NameData) {

	LinkedListNodeDef *iteamWalker, *newIteam;
	errno_t rc;
	newIteam = (LinkedListNodeDef*)malloc(sizeof(LinkedListNodeDef));
	int stringLength = strnlen(NameData, NUMBER_OF_CHARACTERS_IN_WORD);
	iteamWalker = ptrHead;

	if (newIteam != NULL) {
		//copy the new itam to the temp node.
		rc = strncpy_s(newIteam->NameData, NameData, stringLength);
		newIteam->ptrNextNode = NULL;
		
	}

	iteamWalker = ptrHead;
	//walk to the end of the list.
	while (iteamWalker->ptrNextNode != NULL)
	{
		iteamWalker = iteamWalker->ptrNextNode;
	}

	//link the new iteam with the end node.
	iteamWalker->ptrNextNode = newIteam;

	return ptrHead;

}

// FUNCTION      : InsertAtIndexOfLinkedList()
// DESCRIPTION   : This function takes an input of Data of 30 Char word and an index and 
//				   places them in a linked list at a specifc index number. 
// PARAMETERS    : LinkedListNodeDef *ptrHead	- variable to store address of ptrHead
//				   char *NameData				- Array of Characters with data 
//				   int InsertIndex				- Index of the element.
// RETURNS       : possibly updated pointer to the head of the list
LinkedListNodeDef* InsertAtIndexOfLinkedList(LinkedListNodeDef* ptrHead, char* NameData, int InsertIndex) {

	LinkedListNodeDef *previousIteam, *newIteam, *currentIteam{};
	errno_t rc;
	

	int i = 0;
	newIteam = (LinkedListNodeDef*)malloc(sizeof(LinkedListNodeDef));
	int stringLength = strnlen(NameData, NUMBER_OF_CHARACTERS_IN_WORD);
	
	// added check to remove dereferening warning
	if (newIteam != NULL)
	{

		rc = strncpy_s(newIteam->NameData, NameData, stringLength);

	}
	
	// find the correct place to insert
	previousIteam = NULL;
	for (currentIteam = ptrHead; currentIteam != NULL; currentIteam = currentIteam->ptrNextNode, i++)
	{
		if (i >= InsertIndex)
		{
			break;
		}
			
		previousIteam = currentIteam;
	}

	// link up the element that will follow the new node	
	// added check to remove dereferening warning
	if (newIteam != NULL)
	{
		newIteam->ptrNextNode = currentIteam;		
	}
	

	// insert into middle or end of list
	if (previousIteam != NULL)
	{
		previousIteam->ptrNextNode = newIteam;
	}
	// insert into empty list or _before_ the first node
	else
	{
		ptrHead = newIteam;
	}

	return ptrHead;
}

// FUNCTION      : PrintLinkedList()
// DESCRIPTION   : This function will print the linked list.
// PARAMETERS    : LinkedListNodeDef *ptrHead 
// RETURNS       : void
void PrintLinkedList(LinkedListNodeDef* ptrHead) {
	
	if (ptrHead == NULL)
	{
		printf("Empty list. \n");
		return;
	}

	LinkedListNodeDef *dataWalker;
	dataWalker = ptrHead;
	int currentIndex = 1;
	while (dataWalker != NULL)
	{
		printf("%d. %s\n", currentIndex,dataWalker->NameData);
		dataWalker = dataWalker->ptrNextNode;
		currentIndex++;
	}

}
