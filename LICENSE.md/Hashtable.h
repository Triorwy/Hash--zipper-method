#pragma once

#include<stdio.h>
#include<windows.h>
#include<assert.h>

typedef int KeyType;
typedef int ValueType;

typedef struct HashNode
{
	KeyType _key;
	ValueType _value;
	struct HashNode* _next;

}HashNode;

typedef struct HashTable
{
	//HashNode* _tables[];
	HashNode** _tables;
	size_t _size;
	size_t N;

}HashTable;

HashNode* BuyHashNode(KeyType key, ValueType value);//插入节点
size_t GetNextPrimeNum(size_t cur);//构建一个扩容数字，将扩容的值都存在里面,ul代表这些值得类型
size_t HashFunc(KeyType key, size_t N);//得到下标

void HashTableInit(HashTable *ht);
int HashTableInsert(HashTable *ht, KeyType key, ValueType value);//插入
void HashtablePrint(HashTable *ht);//打印
HashNode* HashTableFind(HashTable* ht, KeyType key);//查找
int HashTableRemove(HashTable* ht, KeyType key);//删除
void HashTableDestory(HashTable* ht);//销毁
