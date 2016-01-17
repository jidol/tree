//============================================================================
// Name        : tree.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <time.h>
#include "binarynode.h"
#include "binarysearchtree.h"
#include <stdlib.h>


void binaryTreeTest ()
{
	srand (time(NULL));

	int insertCount = rand() % 100;
	binarynode<int>* output = 0;
	std::vector<int> storage;
	for(int i=0; i < insertCount; ++i)
	{
		int value = rand() % 10000;
		if(0 == output) {
			output = new binarynode<int>(value);
		}
		else
		{
			output->insert(value);
		}
		storage.push_back(value);
	}
	int found = 0;
	for(std::vector<int>::iterator itr = storage.begin(); itr < storage.end(); ++itr)
	{
		binarynode<int>* aNode = output->findNodeByValue(*itr);
		if(0 != aNode && aNode->getValue() != *itr)
		{
			std::cout << "Find failure for " << *itr << std::endl;
		}
		else
		{
			found += 1;
		}
		if(0 == aNode)
		{
			std::cout << "No node found" << std::endl;
		}
	}
	std::cout << "Height = " << output->getHeight() << std::endl;
	std::cout << "Height Left = " << output->getLeft()->getHeight() << std::endl;
	std::cout << "Height Right= " << output->getRight()->getHeight() << std::endl;
	std::cout << "Insert count = " << insertCount << std::endl;
	std::cout << "Number found = " << found << std::endl;
}

void binarySearchTreeTest ()
{
	srand (time(NULL));

	int insertCount = rand() % 100;
	binarysearchtree<int>* output = 0;
	std::vector<int> storage;
	for(int i=0; i < insertCount; ++i)
	{
		int value = rand() % 10000;
		if(0 == output) {
			output = new binarysearchtree<int>(value);
		}
		else
		{
			output->insert(value);
		}
		storage.push_back(value);
	}
	int found = 0;
	for(std::vector<int>::iterator itr = storage.begin(); itr < storage.end(); ++itr)
	{
		binarynode<int>* aNode = output->findNodeByValue(*itr);
		if(0 != aNode && aNode->getValue() != *itr)
		{
			std::cout << "Find failure for " << *itr << std::endl;
		}
		else
		{
			found += 1;
		}
		if(0 == aNode)
		{
			std::cout << "No node found" << std::endl;
		}
	}
	std::cout << "Height = " << output->getHeight() << std::endl;
	std::cout << "Height Left = " << output->getLeft()->getHeight() << std::endl;
	std::cout << "Height Right= " << output->getRight()->getHeight() << std::endl;


	std::cout << "Insert count = " << insertCount << std::endl;
	std::cout << "Number found = " << found << std::endl;
}

int main()
{
	std::cout << "Binary Tree" << std::endl;
	binaryTreeTest();
	std::cout << "Binary Search Tree" << std::endl;
	binarySearchTreeTest();
	return 0;
}

