/*******************************************************************************************
* File Name          : Hshah5830-BinaryTree.cpp
* Description        : Prog8130 - Assignment 2: Binary tree
*						This program stores the string in the binary tree.
*						It follows both, recursive and iterative approaches to store and print the data.
*						further it also calucates the height and nodes in the binary tree.
*						It also uses the given skelleton.
*						PROG8130 assignment #2 skeleton revised June 9, 2021
* 
* Ref 1.			 :	https://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/
  Ref 2.			 : https://mitpress.mit.edu/books/introduction-algorithms-third-edition
* Author			 : Harsh Shah
* Date				 : 18/OCT/2021
* StudentId			 : 8715830
********************************************************************************************/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structure defining a binary tree node.  Lower sorted values will go the the left, higher to the right.
struct nodeData {
	char name[30];				// character string of the data being stored in the node
	struct nodeData* left;		// pointer to the next node in the tree that is less than current node OR NULL if empty
	struct nodeData* right;		// pointer to the next node in the tree that is greater than current node OR NULL if empty
};

/* Structure of a stack node. Linked List implementation is used for
   stack. A stack node contains a pointer to tree node and a pointer to
   next stack node */
struct sNode
{
	struct nodeData* t;
	struct sNode* next;
};


//function definations
void addToBinaryTree(char* newString);
void printBinaryTree(void);
void preorderTraversal(struct nodeData* temp);
void inorderTraversal(struct nodeData* temp);
void inOrderItr(struct nodeData* root);
void postorderTraversal(struct nodeData* temp);
struct nodeData* createNewTree(char* str);
struct nodeData* insertElementToBinaryTreeRec(struct nodeData* root, char* str);
struct nodeData* insertElementToBinaryTreeItr(struct nodeData* root, char* str);
int getTotalNodes(struct nodeData* root);
int getHeight(struct nodeData* root);
void stackPush(struct sNode** top_ref, struct nodeData* t);
struct nodeData* stackPop(struct sNode** top_ref);
int isEmpty(struct sNode* top);

struct nodeData* root = NULL;	// head of the binary tree
struct nodeData* itrHead = NULL;
// data to be stored in tree.  In this case there is just a character string but this could have contained more

const char* inputData[12] = {
		{ "ooyik"},
		{ "yaeac"},
		{ "vrxwa"},
		{ "fqyuw"},
		{ "qhbur"},
		{ "objfv"},
		{ "ypola"},
		{ "almbc"},
		{ "iujbr"},
		{ "doqod"},
		{ "ftxop"},
		{ "qxrfn"}
};


// The correct sorted order using a binary tree is:
//      almbc
//      doqod
//      fqyuw
//      ftxop
//      iujbr
//      objfv
//      ooyik
//      qhbur
//      qxrfn
//      vrxwa
//      yaeac
//      ypola



int main() {
	int i;


	for (i = 0; i < 12; i++)
	{
		char* temp;
		temp = _strdup(inputData[i]);
		addToBinaryTree(temp);
	}

	printBinaryTree();

	return 0;
}


// FUNCTION      : addToBinaryTree
//
// DESCRIPTION   :
//   This function will store the data in newNode into a binary tree according to alphabetical order
//
// PARAMETERS    :
//   newString - the string that is to be stored in the binary tree in alphabetica order
//
// RETURNS       :
//   Nothing
void addToBinaryTree(char* newString) {
	// add code to put items into binary tree in alphabetical order here
	// consider using strcmp library function to decide if a name is greater or less than
	
	//recursive appraoch.
	root = insertElementToBinaryTreeRec(root, newString);
	
	//iterative approach.
	itrHead = insertElementToBinaryTreeItr(itrHead, newString);

}

// FUNCTION      : printBinaryTree
//
// DESCRIPTION   :
//   This function will print the entire binary tree out.  You can choose to print
//   it using recursion but more marks will be awarded if you do it non recursively.
//
// PARAMETERS    :
//   None
//
// RETURNS       :
//   Nothing
void printBinaryTree(void) {
	// add code to print data in order starting at the "head" pointer
	printf("---------------------------------------------------------\n");
	printf("+++++++++++++++++++++++++++Recursive+++++++++++++++++++++\n");
	printf("---------------------------------------------------------\n");
	printf("\n\t-------Inorder--------\n\n");
	inorderTraversal(root);
	printf("\n\n");
	printf("\n\t-------Preorder--------\n\n");
	preorderTraversal(root);
	printf("\n\n");
	printf("\n\t-------Postorder--------\n\n");
	postorderTraversal(root);
	printf("\n\n");
	printf("Height: %d \n", getHeight(root));
	printf("Total Nodes: %d \n", getTotalNodes(root));
	printf("---------------------------------------------------------\n");
	printf("++++++++++++++++++Iterative++++++++++++++++++++++++++++++\n");
	printf("---------------------------------------------------------\n");
	printf("\n\t-------Inorder--------\n\n");
	inorderTraversal(itrHead);
	printf("\n\n");
	printf("\n\t-------Preorder--------\n\n");
	preorderTraversal(itrHead);
	printf("\n\n");
	printf("\n\t-------Postorder--------\n\n");
	postorderTraversal(itrHead);
	printf("\n\n");
	printf("\nHeight: %d \n", getHeight(itrHead));
	printf("Total Nodes: %d \n", getTotalNodes(itrHead));
	printf("---------------------------------------------------------\n");
	printf("++++++++++++++++++Iterative Inorder Print++++++++++++++++++++++++++++++\n");
	printf("---------------------------------------------------------\n");
	printf("\n\n");
	inOrderItr(itrHead);
	printf("\n\n");
	printf("\n\n");

}

// FUNCTION      : preorderTraversal
//
// DESCRIPTION   :
//   This function prints the binary tree in pre-order, it will print the data as it was inserted. 
//   
// PARAMETERS    :
//   nodeData - the elemnt we wish to travel
//
// RETURNS       :
//   Nothing
void preorderTraversal(struct nodeData* temp)
{
	if (temp == NULL)
		return;
	printf("%s \t", temp->name);
	preorderTraversal(temp->left);
	preorderTraversal(temp->right);

}

// FUNCTION      : inorderTraversal
//
// DESCRIPTION   :
//   This function prints the binary tree in-order. first left then right.
//   
// PARAMETERS    :
//   nodeData - the elemnt we wish to travel
//
// RETURNS       :
//   Nothing
void inorderTraversal(struct nodeData* temp)
{
	if (temp == NULL)
		return;
	inorderTraversal(temp->left);
	printf("%s \t", temp->name);
	inorderTraversal(temp->right);

}

// FUNCTION      : postorderTraversal
//
// DESCRIPTION   :
//   This function prints the binary tree in post-order. it will traverse first and then print the data.
//   
// PARAMETERS    :
//   nodeData - the elemnt we wish to travel
//
// RETURNS       :
//   Nothing
void postorderTraversal(struct nodeData* temp)
{
	if (temp == NULL)
		return;
	postorderTraversal(temp->left);
	postorderTraversal(temp->right);
	printf("%s \t", temp->name);
}

// FUNCTION      : createNewTree
//
// DESCRIPTION   :
//   This function will initialize the new tree with string data.   
//
// PARAMETERS    :
//   newString - the string that is to be stored in the binary tree in alphabetica order
//
// RETURNS       :
//   nodeData - updated root information with string data.
struct nodeData* createNewTree(char* str)   // Function to create new node
{
	struct nodeData* temp;
	temp = (struct nodeData*)malloc(sizeof(nodeData));

	if (temp != NULL)
	{
		strcpy_s(temp->name, str);
		temp->left = NULL;
		temp->right = NULL;
	}
	return temp;
}

// FUNCTION      : insertElementToBinaryTreeRec
//
// DESCRIPTION   :
//   This function will store the data in newNode into a binary tree according to alphabetical order
//   It will follow the recursive approach.
// PARAMETERS    :
//   newString - the string that is to be stored in the binary tree in alphabetica order
//   nodeData* - starting index of the root elemnet in the tree.
// RETURNS       :
//   nodeData* - updated index of the root element after inserting the string.
struct nodeData* insertElementToBinaryTreeRec(struct nodeData* root, char* str) // Function to insert a node
{
	if (root == NULL)
	{
		root = createNewTree(str);
	}
	else if (strcmp(str, root->name) < 0)
	{
		root->left = insertElementToBinaryTreeRec(root->left, str);
	}
	else if (strcmp(str, root->name) > 0)
	{
		root->right = insertElementToBinaryTreeRec(root->right, str);
	}
	return root;
}

// FUNCTION      : insertElementToBinaryTreeItr
//
// DESCRIPTION   :
//   This function will store the data in newNode into a binary tree according to alphabetical order
//   It will follow the iterative approach.
// PARAMETERS    :
//   newString - the string that is to be stored in the binary tree in alphabetica order
//   nodeData* - starting index of the root elemnet in the tree.
// RETURNS       :
//   nodeData* - updated index of the root element after inserting the string.
nodeData* insertElementToBinaryTreeItr(nodeData* root, char* str)
{
	struct nodeData* ptr, * nodeptr, * parentptr;
	ptr = (struct nodeData*)malloc(sizeof(nodeData));
	if (ptr != NULL)
	{
		strcpy_s(ptr->name, str);
		ptr->left = NULL;
		ptr->right = NULL;
	}

	if (root == NULL)
	{
		root = ptr;
		if (root != NULL)
		{
			root->left = NULL;
			root->right = NULL;
		}
	}
	else {

		parentptr = NULL;
		nodeptr = root;
		while (nodeptr != NULL)
		{
			parentptr = nodeptr;
			if (strcmp(str, nodeptr->name) < 0)
			{
				nodeptr = nodeptr->left;
			}
			else {
				nodeptr = nodeptr->right;
			}
		}

		if (parentptr == NULL)
		{
			parentptr = nodeptr;

		}
		else if (strcmp(str, parentptr->name) < 0) {
			parentptr->left = ptr;
		}
		else {
			parentptr->right = ptr;
		}

	}
	return root;
}

// FUNCTION      : getTotalNodes
//
// DESCRIPTION   :
//   get total number of nodes in the binary tree.
//
// PARAMETERS    :
//   nodeData - root element of the binary tree.
//
// RETURNS       :
//   total number of nodes for the segenment of the binary tree.
int getTotalNodes(nodeData* root)
{
	if (root == NULL)
	{
		return 0;
	}
	else {
		return(getTotalNodes(root->left) + getTotalNodes(root->right) + 1);
	}

}

// FUNCTION      : getHeight
//
// DESCRIPTION   :
//   Calculate the height of the binary tree.
//
// PARAMETERS    :
//   nodeData - root element of the binary tree.
//
// RETURNS       :
//   int level of the segenment of the tree.
int getHeight(nodeData* root)
{
	int leftHeight = 0, rightHeight = 0;

	if (root == NULL)
	{
		return 0;
	}
	else {

		leftHeight = getHeight(root->left);
		rightHeight = getHeight(root->right);

		if (leftHeight > rightHeight)
		{
			return leftHeight + 1;
		}
		else {
			return rightHeight + 1;
		}
	}
}

// FUNCTION      : inOrderItr
//
// DESCRIPTION   :
//   Inorder itrative traversal
//
// PARAMETERS    :
//   nodeData - root element of the binary tree.
//
// RETURNS       :
//   nothing
void inOrderItr(struct nodeData* root)
{
	
	struct nodeData* current = root;
	struct sNode* s = NULL;  /* Initialize stack s */
	int done = 0;

	while (!done)
	{
		
		if (current != NULL)
		{
			stackPush(&s, current);
			current = current->left;
		}
		else
		{
			if (!isEmpty(s))
			{
				current = stackPop(&s);
				printf("%s ", current->name);
				current = current->right;
			}
			else
				done = 1;
		}
	} 
}

// FUNCTION      : push
//
// DESCRIPTION   :
//   Inorder itrative traversal
//
// PARAMETERS    :
//   addes a binary tree elemnt to the stack.
//
// RETURNS       :
//   nothing
void stackPush(struct sNode** top_ref, struct nodeData* t)
{
	struct sNode* temp =
		(struct sNode*)malloc(sizeof(struct sNode));

	if (temp == NULL)
	{
		printf("Stack Overflow \n");
		exit(0);
	}

	temp->t = t;


	temp->next = (*top_ref);
	(*top_ref) = temp;
}

// FUNCTION      : isEmpty
//
// DESCRIPTION   :
//   check if the stack is empty
//
// PARAMETERS    :
//   sNode - Head ptr of stack
//
// RETURNS       :
//   true if empty
int isEmpty(struct sNode* top)
{
	return (top == NULL) ? 1 : 0;
}

// FUNCTION      : stackPop
//
// DESCRIPTION   :
//   Removes an element from the stack
//
// PARAMETERS    :
//   sNode - top node ptr to be removed from stack
//
// RETURNS       :
//   updated nodeData
struct nodeData* stackPop(struct sNode** top_ref)
{
	struct nodeData* res;
	struct sNode* top;
	
	if (isEmpty(*top_ref))
	{
		printf("Stack Underflow \n");		
		exit(0);
	}
	else
	{
		top = *top_ref;
		res = top->t;
		*top_ref = top->next;
		free(top);
		return res;
	}
}
