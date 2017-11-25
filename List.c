#pragma once
#include"List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node_List)); /* 产生头结点,并使L指向此头结点 */
	if (!(*L)) /* 存储分配失败 */
		return 0;
	(*L)->next = NULL; /* 指针域为空 */

	return 1;
}
int ListInsert(LinkList *L, int i, int e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p && j < i)     /* 寻找第i个结点 */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return 0;   /* 第i个元素不存在 */
	s = (LinkList)malloc(sizeof(Node_List));  /*  生成新结点(C语言标准函数) */
	s->data = e;
	s->next = p->next;      /* 将p的后继结点赋值给s的后继  */
	p->next = s;          /* 将s赋值给p的后继 */
	return 1;
}