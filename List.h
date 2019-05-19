#pragma once
#include "binomialHeap.h"
class List
{
private:
	struct Node
	{
		BinomialHeap* heap;
		Node* prev;
		Node* next;

		Node(BinomialHeap* heap)
			:heap(heap), next(nullptr), prev(nullptr)
		{}
	};

	Node* head_;
	Node* tail_;

public:
	List();

	void PushBack(BinomialHeap* heap);
	BinomialHeap** Find(int group);

	~List();
};

