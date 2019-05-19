#include "binomialHeap.h"
#include "List.h"
#include "hashMap.h"
#define MAPSIZE 1000

hashmap::hashmap()
{
	map = new List*[MAPSIZE];
	for (int i = 0; i < MAPSIZE; i++)
	{
		map[i] = new List;
	}
}

int hashmap::hashFunc(int group)
{
	return (group % 1171) % MAPSIZE;
}

void hashmap::insert(int group)
{
	int hash = hashFunc(group);
	BinomialHeap* tmp = new BinomialHeap(group);
	map[hash]->PushBack(tmp);
}

BinomialHeap** hashmap::findHeap(int group)
{
	int hash = hashFunc(group);
	return map[hash]->Find(group);
}

hashmap::~hashmap()
{
	for (int i = 0; i < MAPSIZE; i++)
	{
		delete map[i];
	}
}


