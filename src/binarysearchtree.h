#include "binarynode.h"

#ifndef BSNODE_H_
#define BSNODE_H_


template <class T>
class binarysearchtree : public binarynode<T>
{
public:
	binarysearchtree(T value);

	binarynode<T>* insert(T value);
	binarynode<T>* findNodeByValue(T value);


protected:
	binarysearchtree<T>* insertLeft(T value);
	binarysearchtree<T>* insertRight(T value);
};

template <class T>
binarysearchtree<T>::binarysearchtree(T value): binarynode<T>(value)
{
}


template <class T>
binarysearchtree<T>* binarysearchtree<T>::insertLeft(T value)
{
	if(0 == this->myLeft)
	{
		this->myLeft = new binarysearchtree<T>(value);
	}
	else
	{
		this->myLeft->insert(value);
	}
	return this;

}

template <class T>
binarysearchtree<T>* binarysearchtree<T>::insertRight(T value)
{
	if(0 == this->myRight)
	{
		this->myRight = new binarysearchtree<T>(value);
	}
	else
	{
		this->myRight->insert(value);
	}

	return this;

}

template <class T>
binarynode<T>* binarysearchtree<T>::insert(T value)
{
	if(this->myValue == value)
	{
		return this;
	}
	else if(this->myValue < value)
	{
		return insertRight(value);
	}
	else
	{
		return insertLeft(value);
	}
	return 0;
}

template <class T>
binarynode<T>* binarysearchtree<T>::findNodeByValue(T value)
{
	if(value == this->myValue)
	{
		return this;
	}
	else
	{
		if(value < this->myValue && 0 != this->myLeft)
		{
			return this->myLeft->findNodeByValue(value);
		}
		else if(value > this->myValue && 0 != this->myRight)
		{
			return this->myRight->findNodeByValue(value);
		}

		return 0;
	}
}
#endif /* BSNODE_H_ */
