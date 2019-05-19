#pragma once
#include "List.h"
#include "binomialHeap.h"
#include "hashMap.h"

#define MAPSIZE 1000

class hashmap
{
public:
	List** map;

	hashmap();
	void insert(int group);
	BinomialHeap** findHeap(int group);
	int hashFunc(int group);
	~hashmap();
};