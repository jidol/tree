/*
 * avltree.h
 *
 *  Created on: Jan 16, 2016
 *      Author: jidol
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include "binarysearchtree.h"

template <class T>
class avltree: public binarysearchtree<T>
{
public:
	avltree(T value);
	virtual ~avltree();

	virtual binarynode<T>* createElement(T value);

	int bFactor();

	inline short height() { return myAVLHeight; }

	virtual binarynode<T>* insert(T value);

	inline short nodeHeight(avltree<T>* node) { return node != 0 ? node->height() : 0;}

	inline void setLeft(avltree<T>* newLeft) { this->myLeft = newLeft; }
	inline void setRight(avltree<T>* newRight) { this->myRight = newRight; }

	void fixheight();

protected:

	avltree<T>* balance();

	avltree<T>* rotateRight();

	avltree<T>* rotateLeft();

	short myAVLHeight;

private:
	avltree<T>* rightAVL();
	avltree<T>* leftAVL();
};

template <class T>
avltree<T>::avltree(T value): binarysearchtree<T>(value),
myAVLHeight(0)
{
}

template <class T>
avltree<T>::~avltree()
{
	binarysearchtree<T>::~binarysearchtree();
}

template <class T>
binarynode<T>* avltree<T>::insert(T value)
{
    if( value < this->myValue )
    {
    	this->myLeft = leftAVL() ? leftAVL()->insert(value) : createElement(value);
    }
    else
    {
    	this->myRight = rightAVL() ? rightAVL()->insert(value) : createElement(value);
    }
    return this->balance();
}


template <class T>
void avltree<T>::fixheight()
{
    short leftHeight = nodeHeight(leftAVL());
    short rightHeight = nodeHeight(rightAVL());
    myAVLHeight = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

template <class T>
avltree<T>* avltree<T>::rotateRight()
{
	avltree<T>* oldLeft = leftAVL();
	this->myLeft = oldLeft->getRight();
	oldLeft->setRight(this);
	this->fixheight();
	oldLeft->fixheight();
	return oldLeft;
}

template <class T>
avltree<T>* avltree<T>::rotateLeft()
{
	avltree<T>* oldRight = rightAVL();
	this->myRight = oldRight->getLeft();
	oldRight->setLeft(this);
	this->fixheight();
	oldRight->fixheight();
	return oldRight;
}
template <class T>
avltree<T>* avltree<T>::balance()
{
    fixheight();
	if( bFactor()==2 )
	{
		if( rightAVL() != 0 && rightAVL()->bFactor() < 0 )
		{
			this->myRight = rightAVL()->rotateRight();
		}
		return this->rotateLeft();
	}
	if( bFactor()==-2 )
	{
		if( leftAVL() != 0 && leftAVL()->bFactor() > 0  )
		{
			this->myLeft = leftAVL()->rotateLeft();
		}
		return this->rotateRight();
	}
	return this;
}
template <class T>
avltree<T>* avltree<T>::rightAVL()
{
	return reinterpret_cast<avltree<T>*>(this->myRight);
}

template <class T>
avltree<T>* avltree<T>::leftAVL()
{
	return reinterpret_cast<avltree<T>*>(this->myLeft);
}

template <class T>
binarynode<T>* avltree<T>::createElement(T value)
{ return new avltree<T>(value); }

template <class T>
int avltree<T>::bFactor()
{
	return nodeHeight(rightAVL()) - nodeHeight(leftAVL());
}

#endif /* AVLTREE_H_ */
