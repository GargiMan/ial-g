#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/DLList.h"

int error_flag;
int solved;

void DLL_Error() {
	//fprintf(stderr ,"*ERROR* The program has performed an illegal operation.\n");

}

void DLL_Init( DLList *list ) {
	list->firstElement=NULL;
	list->lastElement=NULL;
	list->activeElement=NULL;
}

void DLL_Dispose( DLList *list ) {
	DLLElementPtr Next;
	while (list->firstElement != NULL){
		Next = list->firstElement->nextElement;
		free(list->firstElement);
		list->firstElement = Next;
	}
	list->firstElement=NULL;
	list->lastElement=NULL;
	list->activeElement=NULL;
}

void DLL_InsertFirst( DLList *list, struct node *data) {
	DLLElementPtr newElemPtr = (DLLElementPtr) malloc(sizeof(struct DLLElement));
	if(newElemPtr==NULL){
		DLL_Error();
	}
	else{
		newElemPtr->previousElement=NULL;
		newElemPtr->nextElement=list->firstElement;
		newElemPtr->data=data;
		newElemPtr->visited=-1;
		if(list->lastElement==NULL){
			list->lastElement=newElemPtr;
		}
		else{
			list->firstElement->previousElement=newElemPtr;
		}
		list->firstElement=newElemPtr;
	}
}

void DLL_InsertLast( DLList *list, struct node *data) {
	DLLElementPtr newElemPtr = (DLLElementPtr) malloc(sizeof(struct DLLElement));
	if(newElemPtr==NULL){
		DLL_Error();
	}
	else{
		newElemPtr->previousElement=list->lastElement;
		newElemPtr->nextElement=NULL;
		newElemPtr->data=data;
		newElemPtr->visited=-1;
		if(list->firstElement==NULL){
			list->firstElement=newElemPtr;
		}
		else {
			list->lastElement->nextElement=newElemPtr;
		}
		list->lastElement=newElemPtr;
	}
}

void DLL_First( DLList *list ) {
	list->activeElement=list->firstElement;
}

void DLL_Last( DLList *list ) {
	list->activeElement=list->lastElement;
}

void DLL_GetFirst( DLList *list, struct node *data) {
	if (list->firstElement != NULL){
		data = list->firstElement->data;
	}
	else DLL_Error();
}

void DLL_GetLast( DLList *list, struct node **data) {
	if (list->lastElement != NULL){
		*data = list->lastElement->data;
	}
	else DLL_Error();
}

void DLL_DeleteFirst( DLList *list ) {
	DLLElementPtr Next;
	if (list->firstElement != NULL){
		Next = list->firstElement->nextElement;
		free(list->firstElement);
		list->firstElement=Next;
		if (Next == NULL){
			list->activeElement=NULL;
			list->lastElement=NULL;
		}
		else{
			Next->previousElement=NULL;
		}
	}
}

void DLL_DeleteLast( DLList *list ) {
	DLLElementPtr Prev;
	if (list->firstElement != NULL){
		Prev = list->lastElement->previousElement;
		free(list->lastElement);
		list->lastElement=Prev;
		if (Prev == NULL){
			list->activeElement=NULL;
			list->firstElement=NULL;
		}
		else{
			Prev->nextElement=NULL;
		}
	}
}

void DLL_DeleteAfter( DLList *list ) {
	DLLElementPtr TMP;
	if (list->activeElement != NULL &&  list->activeElement != list->lastElement){
		TMP=list->activeElement->nextElement;
		list->activeElement->nextElement=TMP->nextElement;
		if (TMP->nextElement != NULL){
			TMP->nextElement->previousElement=list->activeElement;
		}
		else{
			list->lastElement=list->activeElement;
		}
		free(TMP);
	}
}

void DLL_DeleteBefore( DLList *list ) {
	DLLElementPtr TMP;
	if (list->activeElement != NULL &&  list->activeElement != list->firstElement){
		TMP=list->activeElement->previousElement;
		list->activeElement->previousElement=TMP->previousElement;
		if (TMP->previousElement != NULL){
			TMP->previousElement->nextElement=list->activeElement;
		}
		else{
			list->firstElement=list->activeElement;
		}
		free(TMP);
	}
}

void DLL_InsertAfter( DLList *list, struct node *data) {
	if (list->activeElement != NULL){
		DLLElementPtr newElemPtr = (DLLElementPtr) malloc(sizeof(struct DLLElement));
		if (newElemPtr == NULL){
			DLL_Error();
		}
		else{
			newElemPtr->data=data;
			newElemPtr->nextElement = list->activeElement->nextElement;
			newElemPtr->previousElement=list->activeElement;
			newElemPtr->visited=-1;
			if(list->activeElement == list->lastElement){
				list->lastElement=newElemPtr;
			}
			if(list->activeElement->nextElement!=NULL){
				list->activeElement->nextElement->previousElement = newElemPtr;
			}
			list->activeElement->nextElement=newElemPtr;
		}
	}
}

void DLL_InsertBefore( DLList *list, struct node *data) {
	if (list->activeElement != NULL){
		DLLElementPtr newElemPtr = (DLLElementPtr) malloc(sizeof(struct DLLElement));
		if (newElemPtr == NULL){
			DLL_Error();
		}
		else{
			newElemPtr->data=data;
			newElemPtr->nextElement = list->activeElement;
			newElemPtr->previousElement=list->activeElement->previousElement;
			newElemPtr->visited=-1;
			if(list->activeElement == list->firstElement){
				list->firstElement=newElemPtr;
			}
			if(list->activeElement->previousElement!=NULL){
				list->activeElement->previousElement->nextElement = newElemPtr;
			}
			list->activeElement->previousElement=newElemPtr;
		}
	}
}

void DLL_GetValue( DLList *list, struct node **data) {
	if (list->activeElement != NULL){
		*data = list->activeElement->data;
	}
	else DLL_Error();
}

void DLL_SetValue( DLList *list, struct node *data) {
	if (list->activeElement != NULL){
		list->activeElement->data=realloc(list->activeElement->data, (strlen(data) + 1) * sizeof(char));
		strcpy(list->activeElement->data, data);
	}
}

void DLL_Next( DLList *list ) {
	if (list->firstElement != NULL && list->activeElement != NULL){
		if (list->activeElement->nextElement != NULL){
			list->activeElement = list->activeElement->nextElement;
		}
		else list->activeElement = NULL;
}
}

void DLL_Previous( DLList *list ) {
	if (list->firstElement != NULL && list->activeElement != NULL){
		if (list->activeElement->previousElement != NULL){
			list->activeElement = list->activeElement->previousElement;
		}
		else list->activeElement = NULL;
	}
}

int DLL_IsActive( DLList *list ) {
	return list->activeElement != NULL;
}

bool DLL_IsIn(DLList *list, struct node *data)
{
	if(list == NULL || data == NULL) return false;
	DLLElementPtr listElement = list->firstElement;	
	while(listElement != NULL)
	{
		if (!strcmp(listElement->data->name, data->name)) return true;
		listElement=listElement->nextElement;
	}
	return false;
}

int DLL_Visited(DLList *list)
{
	return list->activeElement->visited;
}

void DLL_VisitedInc(DLList *list)
{
	list->activeElement->visited++;
}

bool DLL_IsOne(DLList *list)
{
	return list->firstElement==list->lastElement;
}

int DLL_Len(DLList *list)
{
	DLLElementPtr listElement = list->firstElement;
	int i=0;
	while (listElement)
	{
		i++;
		listElement=listElement->nextElement;
	}
	return i;
}