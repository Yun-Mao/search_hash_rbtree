#pragma once
#include "hashTable.h"
#define MAX_PRIME_LESS_THAN_HASH_LEN 7993
char* strDup(const char* str)
{
	int len;
	char* ret;
	if (str == NULL)return NULL;

	len = strlen(str);
	ret = (char*)malloc(len + 1);
	if (ret != NULL) {
		memcpy(ret, str, len);
		ret[len] = '\0';
	}
	return ret;
}
unsigned int hashfunc(char *str, int len)
{
	register unsigned int sum = 0;
	register unsigned int h = 0;
	register char *p = str;
	while (p - str < len)
	{
		register unsigned short a = *(p++);
		sum ^= a * (p - str);
		h ^= a / (p - str);
	}
	return ((sum << 16) | h) % MAX_PRIME_LESS_THAN_HASH_LEN;
}


void initHashTable(hashTable* t)
{
	int i;
	if (t == NULL)return;
	for (i = 0; i < BUCKETCOUNT; ++i) {
		t->bucket[i].key = NULL;
		t->bucket[i].value = NULL;
		t->bucket[i].next = NULL;
	}
}
void freeHashTable(hashTable* t)
{
	int i;
	entry* e, *ep;
	if (t == NULL)return;
	for (i = 0; i<BUCKETCOUNT; ++i) {
		e = &(t->bucket[i]);
		while (e->next != NULL) {
			ep = e->next;
			e->next = ep->next;
			free(ep->key);
			free(ep->value);
			free(ep);
		}
	}
}
int insertEntry(hashTable* t, char *key, RBRoot *value)
{
	int index, vlen1, vlen2;
	entry* e, *ep;

	if (t == NULL || key == NULL || value == NULL) {
		return -1;
	}
	index = hashfunc(key, strlen(key));

	if (t->bucket[index].key == NULL) {
		t->bucket[index].key = (char *)malloc(strlen(key)*sizeof(char));
		t->bucket[index].key = key;
		t->bucket[index].value = (RBRoot *)malloc(sizeof(RBRoot));
		t->bucket[index].value = value;
	}
	else {
		e = ep = &t->bucket[index];
		while (e != NULL) {
			if (strcmp(e->key, key) == 0)
			{
				memcpy(e->value, value, sizeof(RBRoot));
				return index;
			}
			ep = e;
			e = e->next;
		}
		e = (entry*)malloc(sizeof(entry));
		e->key = strDup(key);
		e->value= (RBRoot *)malloc(sizeof(RBRoot));
		e->value = value;
		e->next = NULL;
		ep->next = e;
	}
	return index;
}
RBRoot* findValue(hashTable*t, char *key)
{
	int index;
	entry* e;
	if (t == NULL || key == NULL)
	{
		return NULL;
	}
	index = hashfunc(key,strlen(key));
	e = &(t->bucket[index]);
	if (e->key == NULL)return NULL;
	while (e != NULL)
	{
		if (strcmp(key, e->key)==0)
		{
			return e->value;
		}
		e = e->next;
	}
	return NULL;
}