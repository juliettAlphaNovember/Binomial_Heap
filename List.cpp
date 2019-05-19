#include "List.h"
//#include <iostream>
#include <cstdio>


List::List() : head_(nullptr), tail_(nullptr)
{}


void List::PushBack(BinomialHeap* heap)
{
	Node* new_node = new Node(heap);

	if (tail_ == nullptr)
	{
		head_ = tail_ = new_node;
	}
	else
	{
		tail_->next = new_node;
		new_node->prev = tail_;
		tail_ = new_node;
	}
}


BinomialHeap** List::Find(int group)
{
	Node* temp = head_;

	while (temp != nullptr) {
		if (temp->heap->group == group)
		{
			return &(temp->heap);
		}
		temp = temp->next;
	}
	return nullptr;
}



List::~List()
{
	Node* p;
	while (head_)
	{
		p = head_->next;
		clear(head_->heap);
		delete head_;
		head_ = p;
	}
}




