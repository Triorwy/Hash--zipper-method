#include"Hashtable.h"

void Test()
{
	HashTable ht;
	HashTableInit(&ht);
	HashTableInsert(&ht, 37, 0);
	HashTableInsert(&ht, 25, 0);
	HashTableInsert(&ht, 14, 0);
	HashTableInsert(&ht, 36, 0);
	HashTableInsert(&ht, 49, 0);
	HashTableInsert(&ht, 68, 0);
	HashTableInsert(&ht, 57, 0);
	HashTableInsert(&ht, 11, 0);
	HashTableInsert(&ht, 90, 0);
	HashTableInsert(&ht, 64, 0);
	HashTableInsert(&ht, 63, 0);
	HashTableInsert(&ht, 28, 0);
	HashTableInsert(&ht, 67, 0);

	HashtablePrint(&ht);
	HashTableRemove(&ht, 37);
	HashTableRemove(&ht, 57);
	HashTableRemove(&ht, 14);
	HashTableRemove(&ht, 25);
	HashtablePrint(&ht);

	printf("37?%d\n", HashTableFind(&ht, 37)->_key);
	printf("25?%d\n", HashTableFind(&ht, 25)->_key);
	printf("14?%d\n", HashTableFind(&ht, 14)->_key);
	printf("36?%d\n", HashTableFind(&ht, 36)->_key);
	printf("3?%p\n", HashTableFind(&ht, 3));


}

int main()
{
	Test();
	system("pause");
	return 0;
}
