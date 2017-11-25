#pragma once
typedef struct Node_List
{
	int data;
	struct Node_List *next;
}Node_List;
typedef struct Node_List *LinkList; //∂®“ÂLinkList
int InitList(LinkList *L);
int ListInsert(LinkList *L, int i, int e);