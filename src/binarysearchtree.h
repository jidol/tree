#include "binarynode.h"

#ifndef BSNODE_H_
#define BSNODE_H_


template <class T>
class binarysearchtree : public binarynode<T>
{
public:
	binarysearchtree(T value);
	virtual ~binarysearchtree();

	virtual binarynode<T>* insert(T value);
	binarynode<T>* findNodeByValue(T value);
	virtual binarynode<T>* createElement(T value);
	inline binarysearchtree<T>* getParent() { return myParent; }
	inline void setParent(binarysearchtree<T>* parent) { myParent = parent; }
	inline binarysearchtree<T>* getGrandparent() { return myParent != 0 ? myParent->getParent() : 0; }
	binarysearchtree<T>* getUncle();


protected:
	binarysearchtree<T>* insertLeft(T value);
	binarysearchtree<T>* insertRight(T value);

	binarysearchtree<T>* myParent;
};

template <class T>
binarysearchtree<T>::binarysearchtree(T value): binarynode<T>(value),
myParent(0)
{
}

template <class T>
binarysearchtree<T>::~binarysearchtree()
{
	binarynode<T>::~binarynode();
}

template <class T>
binarynode<T>* binarysearchtree<T>::createElement(T value)
{ return new binarysearchtree(value); }


template <class T>
binarysearchtree<T>* binarysearchtree<T>::insertLeft(T value)
{
	if(0 == this->myLeft)
	{
		binarysearchtree<T>* newChild = createElement(value);
		newChild->setParent(this);
		this->myLeft = newChild;
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
		binarysearchtree<T>* newChild = createElement(value);
		newChild->setParent(this);
		this->myRight = newChild;
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
    if(this->myValue < value)
	{
		return insertRight(value);
	}
	else
	{
		return insertLeft(value);
	}
	return this;
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

template <class T>
binarysearchtree<T>* binarysearchtree<T>::getUncle()
{
	binarysearchtree<T>* uncle = 0;
	binarysearchtree<T>* parent = getParent();
	if(0 != parent)
	{
		bool leftChild = parent->getLeft() == this;

		uncle = leftChild ? parent->getRight() : parent->getLeft();
	}

	return uncle;
}
#endif /* BSNODE_H_ */
