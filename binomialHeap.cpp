//#include <iostream>
#include <cstdio>
#include "binomialHeap.h"

Node* Merge(BinomialHeap *& H1, BinomialHeap *& H2)
{
	Node *head = nullptr;
	Node *tail = nullptr;

	Node *a = H1->head;
	Node *b = H2->head;

	if (a->degree < b->degree)
	{
		head = a;
		a = a->sibling;
	}
	else
	{
		head = b;
		b = b->sibling;
	}

	tail = head;

	while (a != nullptr && b != nullptr)
	{
		if (a->degree < b->degree)
		{
			tail->sibling = a;
			a = a->sibling;
		}
		else
		{
			tail->sibling = b;
			b = b->sibling;
		}

		tail = tail->sibling;
	}

	if (a != nullptr)
	{
		tail->sibling = a;
	}
	else if (b != nullptr)
	{
		tail->sibling = b;
	}
	else
	{
		tail->sibling = nullptr;
	}

	return head;
}

void binomialLink(Node* &newSon, Node* &newParent)
{
	newSon->parent = newParent;
	newSon->sibling = newParent->child;
	newParent->child = newSon;
	newParent->degree += 1;
}


BinomialHeap* unionHeaps(BinomialHeap *& H1, BinomialHeap *& H2)
{
	BinomialHeap *H = new BinomialHeap(H1->group);
	if (H1->head == nullptr && H2->head == nullptr)
	{
		return H1;
	}
	else if (H1->head == nullptr)
	{
		H->head = H2->head;
	}
	else if (H2->head == nullptr)
	{
		H->head = H1->head;
	}
	else
	{
		H->head = Merge(H1, H2);
	}
	H2->head = nullptr;
	H1->head = nullptr;

	if (H->head == nullptr)
	{
		return H;
	}

	Node* previousX = nullptr;
	Node* x = H->head;
	Node* nextX = x->sibling;

	while (nextX != nullptr)
	{
		// Przypadek 1 - stopieñ nextX jest wiêkszy od stopnia x - przechodzimy dalej
		// Przypadek 2 - x jest pierwszym z trzech korzeni o takich samych stopniach - przechodzimy dalej
		if (x->degree != nextX->degree || (nextX->sibling != nullptr && x->degree == nextX->sibling->degree))
		{
			previousX = x;
			x = nextX;
		}
		else
		{
			// Przypadek 3 - x jest pierwszym z dwóch korzeni o takich samych stopniach oraz x->key >= nextX->key
			if (x->key >= nextX->key)
			{
				x->sibling = nextX->sibling;
				binomialLink(nextX, x);
			}
			else
			{
				// Przypadek 4 - x jest pierwszym z dwóch korzeni o takich samych stopniach oraz x->key < nextX->key
				if (previousX == nullptr)
				{
					H->head = nextX;
				}
				else
				{
					previousX->sibling = nextX;
				}

				binomialLink(x, nextX);
				x = nextX;
			}
		}
		nextX = x->sibling;
	}
	return H;
}

void insert(BinomialHeap *& heap, int key)
{
	BinomialHeap *H = new BinomialHeap();
	Node *tmp = new Node(key);
	if (heap->head == nullptr)
	{
		heap->head = tmp;
	}
	else
	{
		H->head = tmp;
		heap = unionHeaps(heap, H);
	}
}

// odwraca liste, przy okazji nulluj¹c rodziców
Node* reverseList(Node* &head)
{
	Node* prev = nullptr;
	Node* next = nullptr;
	Node* current = head;
	if (!current)
	{
		return current;
	}
	current->parent = nullptr;
	while (current->sibling)
	{
		next = current->sibling;
		current->sibling = prev;
		prev = current;
		current = next;
		current->parent = nullptr;
	}
	current->sibling = prev;
	return current;
}


int extractMax(BinomialHeap *& heap, Extract action)
{
	Node* max = heap->head;
	Node* prevMax = nullptr;
	Node* current = heap->head;
	int maxValue = -1;

	while (current != nullptr)
	{
		if (current->sibling != nullptr && current->sibling->key > max->key)
		{
			prevMax = current;
			max = current->sibling;
		}
		current = current->sibling;
	}
	if (max == nullptr)
	{
		if (action == Extract::PRINT)
		{
			//std::cout << "na" << '\n';
			printf("na\n");
		}
		return -1;
	}
	else
	{
		if (action == Extract::PRINT)
		{
			//std::cout << max->key << '\n';
			printf("%i\n", max->key);
		}
		maxValue = max->key;
	}

	if (prevMax != nullptr)
	{
		prevMax->sibling = max->sibling;
	}
	else
	{
		heap->head = max->sibling;
	}

	if (max->child == nullptr)
	{
		heap->head = max->sibling;
		max->sibling = nullptr;
		max = nullptr;
		delete max;
		return maxValue;
	}


	BinomialHeap *H = new BinomialHeap();
	H->head = reverseList(max->child);

	if (prevMax == nullptr && max->sibling == nullptr)
	{
		int tmpGroup = heap->group;
		heap->head = H->head;
		heap->group = tmpGroup;
	}
	else
	{
		heap = unionHeaps(heap, H);
	}
	max = nullptr;
	delete max;
	delete H;
	return maxValue;
}

void clear(BinomialHeap *& heap)
{
	while (heap->head != nullptr)
	{
		extractMax(heap, Extract::CLEAR);
	}
	delete heap;
}

Node* findNode(Node *&head, int key)
{
	Node* x = head;
	Node* found = nullptr;
	if (x->key == key)
	{
		return x;
	}
	if (x->sibling != nullptr && found == nullptr)
	{
		found = findNode(x->sibling, key);
	}
	if (x->child != nullptr && found == nullptr && key < x->key)
	{
		found = findNode(x->child, key);
	}
	return found;
}

void swapKeys(Node* &first, Node* &second)
{
	int tmp = first->key;
	first->key = second->key;
	second->key = tmp;
}

void increaseKey(BinomialHeap* &heap, int oldKey, int newKey)
{
	Node* found = findNode(heap->head, oldKey);
	Node* y = nullptr;
	Node* z = nullptr;

	if (found == nullptr)
	{
		//std::cout << "na\n";
		printf("na\n");
		return;
	}
	else
	{
		if (newKey < oldKey)
		{
			Node* max = heap->head;
			Node* current = heap->head;
			int maxValue = -1;

			while (current != nullptr)
			{
				if (current != nullptr && current->key > max->key)
				{
					max = current;
				}
				current = current->sibling;
			}
			found->key = max->key + 1;
		}
		else 
		{
			found->key = newKey;
		}		
		y = found;
		z = y->parent;
		while (z != nullptr && y->key > z->key)
		{
			swapKeys(y, z);
			y = z;
			z = y->parent;
		}
		if (newKey < oldKey)
		{
			extractMax(heap, Extract::CLEAR);
			insert(heap, newKey);
		}
	}
}

void printAll(BinomialHeap *& heap)
{
	if (heap->head == nullptr)
	{
		//std::cout << "na" << '\n';
		return;
	}

	BinomialHeap *H = new BinomialHeap(heap->group);
	int maxValue;

	while (heap->head != nullptr)
	{
		maxValue = extractMax(heap, Extract::PRINT);
		if (maxValue > -1)
		{
			insert(H, maxValue);
		}
	}
	heap->head = H->head;
	delete H;
}
