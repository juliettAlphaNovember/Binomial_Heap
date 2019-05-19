#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
//#include <iostream>
#include "hashMap.h"


int main()
{
	int numberOfOperations;
	char command;
	int group;
	hashmap* map = new hashmap();
	BinomialHeap** tmp = nullptr;
	BinomialHeap** tmp2 = nullptr;
	
	//std::cin >> numberOfOperations;
	scanf("%i", &numberOfOperations);

	for (int i = 0; i < numberOfOperations; i++)
	{
		//std::cin >> command;
		scanf(" %c", &command);
		switch (command)
		{
		//add
		case 'a':
		{
			int value;
			//std::cin >> group;
			//std::cin >> value;
			scanf("%i", &group);
			scanf("%i", &value);
			if (map->findHeap(group) == nullptr)
			{
				map->insert(group);
			}
			tmp = map->findHeap(group);
			insert(*tmp, value);
			break;
		}
		//extract
		case 'e':
			//std::cin >> group;
			scanf("%i", &group);
			tmp = map->findHeap(group);
			if (tmp == nullptr)
			{
				//std::cout << "na\n";
				printf("na\n");
			}
			else
			{
				extractMax(*tmp, Extract::PRINT);
			}
			break;
		//print
		case 'p':
			//std::cin >> group;
			scanf("%i", &group);
			tmp = map->findHeap(group);
			if (tmp != nullptr)
			{
				printAll(*tmp);
			}
			break;
		//merge
		case 'm':
			int group2;

			//std::cin >> group;
			//std::cin >> group2;
			scanf("%i", &group);
			scanf("%i", &group2);
			if (map->findHeap(group) == nullptr)
			{
				map->insert(group);
			}
			if (map->findHeap(group2) == nullptr)
			{
				map->insert(group2);
			}
			tmp = map->findHeap(group);
			tmp2 = map->findHeap(group2);
			*tmp = unionHeaps(*tmp, *tmp2);
			break;
		//increase
		case 'i':
			//std::cin >> group;
			scanf("%i", &group);
			tmp = map->findHeap(group);
			if (tmp == nullptr)
			{
				//std::cout << "na\n";
				printf("na\n");
			}
			else
			{
				int oldValue;
				int newValue;
				//std::cin >> oldValue;
				//std::cin >> newValue;
				scanf("%i", &oldValue);
				scanf("%i", &newValue);
				increaseKey(*tmp, oldValue, newValue);
			}
			break;
		}
	}
    return 0;
}

