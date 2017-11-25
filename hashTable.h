#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"
#define BUCKETCOUNT 9000
	struct _hash_Entry
	{
		const char* key;//��
		RBRoot* value;//ֵ
		struct _hash_Entry* next;//��һ�����
	};//��������
	typedef struct _hash_Entry entry;
	typedef struct _Table
	{
		entry bucket[BUCKETCOUNT];  //����Ͱ
	}hashTable;
	char* strDup(const char* str);
	unsigned int hashfunc(char*key, int len);//��ϣֵ�ļ���
	void initHashTable(hashTable* t);//��ʼ����ϣ��
	void freeHashTable(hashTable* t);//�ͷŹ�ϣ��
	int insertEntry(hashTable* t, char *key, RBRoot *value);//��������
	RBRoot* findValue(hashTable*t, char *key);//����
	//entry* removeTable(hashTable*t, char key);//ɾ������ʱ����