#pragma once
#include"List.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int InitList(LinkList *L)
{
	*L = (LinkList)malloc(sizeof(Node_List)); /* ����ͷ���,��ʹLָ���ͷ��� */
	if (!(*L)) /* �洢����ʧ�� */
		return 0;
	(*L)->next = NULL; /* ָ����Ϊ�� */

	return 1;
}
int ListInsert(LinkList *L, int i, int e)
{
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p && j < i)     /* Ѱ�ҵ�i����� */
	{
		p = p->next;
		++j;
	}
	if (!p || j > i)
		return 0;   /* ��i��Ԫ�ز����� */
	s = (LinkList)malloc(sizeof(Node_List));  /*  �����½��(C���Ա�׼����) */
	s->data = e;
	s->next = p->next;      /* ��p�ĺ�̽�㸳ֵ��s�ĺ��  */
	p->next = s;          /* ��s��ֵ��p�ĺ�� */
	return 1;
}