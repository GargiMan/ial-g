#ifndef DLLIST_H
#define DLLIST_H

#include<stdio.h>
#include<stdlib.h>
#include"../include/graph.h"

typedef struct DLLElement {
	struct node *data;
	int visited;
	struct DLLElement *previousElement;
	struct DLLElement *nextElement;
} *DLLElementPtr;

typedef struct {
	DLLElementPtr firstElement;
	DLLElementPtr activeElement;
	DLLElementPtr lastElement;
} DLList;

void DLL_Init( DLList * );

void DLL_Dispose( DLList * );

void DLL_InsertFirst( DLList *, struct node *data);

void DLL_InsertLast( DLList *, struct node *data);

void DLL_First( DLList * );

void DLL_Last( DLList * );

void DLL_GetFirst( DLList *, struct node *data);

void DLL_GetLast( DLList *, struct node **data);

void DLL_DeleteFirst( DLList * );

void DLL_DeleteLast( DLList * );

void DLL_DeleteAfter( DLList * );

void DLL_DeleteBefore( DLList * );

void DLL_InsertAfter( DLList *, struct node *data);

void DLL_InsertBefore( DLList *, struct node *data);

void DLL_GetValue( DLList *, struct node **data);

void DLL_SetValue( DLList *, struct node *data);

void DLL_Next( DLList * );

void DLL_Previous( DLList * );

int DLL_IsActive( DLList * );

bool DLL_IsIn(DLList *, struct node *data);

int DLL_Visited(DLList * );

void DLL_VisitedInc( DLList * );

bool DLL_IsOne(DLList *list);

int DLL_Len(DLList * );
#endif //DLLIST_H