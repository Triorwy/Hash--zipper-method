#include"Hashtable.h"

size_t GetNextPrimeNum(size_t cur)// 使用素数表对齐做哈希表的容量，降低哈希冲突,ul代表这些值得类型
{
	static const unsigned long _PrimeList[28] =
	{
		53ul, 97ul, 193ul, 389ul, 769ul,
		1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
		49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
		1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
		50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
		1610612741ul, 3221225473ul, 4294967291ul
	};
	for (int i = 0; i < 28; i++)
	{
		if (cur < _PrimeList[i])
		{
			cur = _PrimeList[i];
			return cur;
		}
	}
	return _PrimeList[27];
}
size_t HashFunc(KeyType key, size_t N)
{
	return key%N;//返回存储在数组里位置的下标
}
void HashTableInit(HashTable *ht)
{
	ht->_size = 0;
	ht->N = 11;
	//这块强转时用二级指针，因为结构体里定义为HashNode** _tables;
	ht->_tables = (HashNode**)malloc(sizeof(HashNode*)*ht->N);
	assert(ht->_tables);
	for (size_t i = 0; i < ht->N; i++)
	{
		ht->_tables[i] = NULL;//将数组里都初始化为NULL
	}
}
HashNode* BuyHashNode(KeyType key, ValueType value)
{
	HashNode *node = (HashNode*)malloc(sizeof(HashNode));
	assert(node);
	node->_key = key;
	node->_value = value;
	return node;
}
int HashTableInsert(HashTable *ht, KeyType key, ValueType value)//插入
{
	if (10 * ht->_size / ht->N > 7)//超过负载因子，扩容
	{
		HashTable Newht;//重新创一个新的结构体变量
		size_t newN = GetNextPrimeNum(ht->N);//得到新的扩容后的容量
		Newht._tables = (HashNode**)malloc(sizeof(HashNode*)*newN);
		assert(Newht._tables);
		memset(Newht._tables, 0, sizeof(HashNode*)*newN);//初始化新结构体
		for (size_t i = 0; i < ht->N; i++)
		{
			if (ht->_tables[i] != NULL)
			{
				HashNode *cur = ht->_tables[i];//得到链表表头节点的地址
				
				while (cur)
				{
					HashNode *next = cur->_next;//保存下一个节点

					size_t Index = HashFunc(cur->_key, newN);//重新计算原表中的值在新表中的位置
					//将原表头结点的下一个（即原链表插入的第一个值）指向新表头结点
					cur->_next = Newht._tables[Index];
					Newht._tables[Index] = cur;//原表头结点赋给新表头节点实现原表值映射到新表中
					cur = next;

				}
				
			}
			
		}
		free(ht->_tables);//释放原表
		ht->N = newN;//将新表扩容后值赋给原表
		ht->_tables = Newht._tables;//新表重新赋给原表
	}

	size_t Index = HashFunc(key,ht->N);
	HashNode *next = NULL;
	HashNode *tmp = NULL;
	tmp = ht->_tables[Index];//得到链表表头节点的地址
	if (tmp)
	{
		while (tmp)//头结点不为空
		{
			if (key == tmp->_key)//插入时发现与插入值相等
			{
				return -1;//返回-1
			}
			tmp = tmp->_next;
		}
	}
	HashNode* cur = BuyHashNode(key, value);//得到插入值得新节点
	cur->_next = ht->_tables[Index];//新节点的下一个指向链表头节点（即插入值得第一个节点）头插
	ht->_tables[Index] =cur;//将新节点赋给链表头结点
	ht->_size++;
	return 0;
}
void HashtablePrint(HashTable *ht)//打印
{
	for (size_t i = 0; i < ht->N; i++)
	{
		printf("[%d]->",i);
		HashNode* node = ht->_tables[i];
		while (node)
		{
			printf("%d->", node->_key);
			node = node->_next;
		}
		printf("NULL\n");
	}

}
HashNode* HashTableFind(HashTable* ht, KeyType key)//查找
{
	assert(ht);
	size_t Index = HashFunc(key, ht->N);
	HashNode *cur = ht->_tables[Index];
	while (cur)
	{
		if (key == cur->_key)
		{
			return cur;
		}
		cur = cur->_next;
	}
	return NULL;

}
int HashTableRemove(HashTable* ht, KeyType key)//删除
{
	assert(ht);
	if (HashTableFind(ht, key) != NULL)
	{
		size_t Index = HashFunc(key, ht->N);
		HashNode* cur = ht->_tables[Index];
		HashNode* prev = NULL;
		while (cur)
		{

			HashNode *next = cur->_next;//保存下一个节点
			if (key == ht->_tables[Index]->_key)//如果头结点就是要删除的节点
			{
				ht->_tables[Index] = next;//将下一个节点直接赋给头结点
				ht->_size--;
				free(cur);
				cur = NULL;
				return 0;
			}
			 if (key == cur->_key)//删除节点不是头结点
			{
				prev->_next = next->_next;//将前一个节点与当前节点的下一个节点链接
				ht->_size--;
				free(cur);//释放当前节点
				cur = NULL;
				return 0;
			}
			prev = cur;
			cur = next;
		}
		return -1;
	}
	return -1;
}
void HashTableDestory(HashTable* ht)//销毁
{
	free(ht->_tables);
	ht->_tables = NULL;
	ht->_size = 0;
	ht->N = 0;
}
