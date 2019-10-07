#include <stdio.h>
#include "fatal.h"
#include "hashsep.h"
#include <string.h>

typedef struct TreeNode* SearchTree;
struct ListNode
{
	unsigned long int mobile;
	unsigned long int home;
	char first_name[25];
	char last_name[25];
	char company_name[25];
	Position    Next;
};

typedef struct ListNode* Position;
typedef Position List;
struct TreeNode
{
	Position  Element;  //Trees Have been used to implement sorting as Hash Tables cannot be sorted
	SearchTree  Left;	
	SearchTree  Right;
};

SearchTree
MakeEmpty(SearchTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->Left);
		MakeEmpty(T->Right); 
		free(T);
	}
	return NULL;
}

SearchTree
TreeInsert(Position X, SearchTree T)
{
	if (T == NULL)
	{
	    T = malloc(sizeof(struct TreeNode));
		if (T == NULL)
		    FatalError("Out of space!!!");
		else
		{
			T->Element = X;
			T->Left = T->Right = NULL;
		}
	}                        

	/*
		First it sorts the contacts according to first name 
		if same first name are found than 
		it sorts with second name
	*/




	else  if (strcmp(X->first_name,  T->Element->first_name)<0)
	     T->Left = TreeInsert(X, T->Left);
	else  if (strcmp(X->first_name, T->Element->first_name) > 0)
	     T->Right = TreeInsert(X, T->Right);
	else if (strcmp(X->first_name, T->Element->first_name) == 0) {
		if (strcmp(X->last_name, T->Element->last_name) < 0) 
		{
			T->Left = TreeInsert(X, T->Left);
		}
		else 
			T->Right = TreeInsert(X, T->Right);
			}
	return T;  /* Do not forget this line!! */
}

void PrintAscend(SearchTree T) {
	if (T != NULL) {
		/// In Order Traversal of Node
		PrintAscend(T->Left); 
		if (strlen(T->Element->first_name) >= 8)
			printf("%s\t", T->Element->first_name);
		else 
			printf("%s\t\t",T->Element->first_name); //Then node is printed 
		if (strlen(T->Element->last_name) >= 8)
			printf("%s\t", T->Element->last_name);
		else
			printf("%s\t\t", T->Element->last_name);
		printf("0%u\t0%u\t%s\n", T->Element->mobile, T->Element->home, T->Element->company_name);
		PrintAscend(T->Right);
	}
}