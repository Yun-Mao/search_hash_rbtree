#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbtree.h"
#define BUCKETCOUNT 9000
	struct _hash_Entry
	{
		const char* key;//键
		RBRoot* value;//值
		struct _hash_Entry* next;//下一个结点
	};//结点的内容
	typedef struct _hash_Entry entry;
	typedef struct _Table
	{
		entry bucket[BUCKETCOUNT];  //定义桶
	}hashTable;
	char* strDup(const char* str);
	unsigned int hashfunc(char*key, int len);//哈希值的计算
	void initHashTable(hashTable* t);//初始化哈希表
	void freeHashTable(hashTable* t);//释放哈希表
	int insertEntry(hashTable* t, char *key, RBRoot *value);//插入数据
	RBRoot* findValue(hashTable*t, char *key);//查找
	//entry* removeTable(hashTable*t, char key);//删除，暂时不用