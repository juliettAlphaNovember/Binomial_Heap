#pragma once

enum Extract
{
	PRINT,
	CLEAR
};

struct Node
{
	int key, degree;
	Node *child, *sibling, *parent;

	Node(int key) : child( nullptr ), sibling( nullptr ), parent( nullptr ), degree( 0 ), key( key )
	{}
};

struct BinomialHeap
{
	Node *head;
	int group;

	BinomialHeap(int group) : head( nullptr ), group( group )
	{}

	BinomialHeap() : head( nullptr ), group( 0 )
	{}
};

Node* Merge(BinomialHeap* &H1, BinomialHeap* &H2);
void binomialLink(Node* &newSon, Node* &newParent);
BinomialHeap* unionHeaps(BinomialHeap* &H1, BinomialHeap* &H2);
void insert(BinomialHeap* &heap, int key);
Node* reverseList(Node* &head);
int extractMax(BinomialHeap* &heap, Extract action);
void clear(BinomialHeap* &heap);
Node* findNode(Node* &head, int key);
void swapKeys(Node* &first, Node* &second);
void increaseKey(BinomialHeap* &heap, int oldKey, int newKey);
void printAll(BinomialHeap* &heap);