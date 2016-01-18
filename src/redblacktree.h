/*
 * redblacktree.h
 *
 *  Created on: Jan 17, 2016
 *      Author: jidol
 */

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include "binarysearchtree.h"

template <class T>
class redblacktree: public binarysearchtree<T> {
public:
	enum COLOR {BLACK, RED};

	redblacktree(T value);
	virtual ~redblacktree();

	inline int getColor() { return myColor; }
	inline void setColor(int color) { myColor = color; }

	virtual binarynode<T>* createElement(T value);
	inline readblacktree<T>* getLeftRbTree() { return reinterpret_cast<redblacktree<T>*>(this->myLeft); }
	inline readblacktree<T>* getRightRbTree() { return reinterpret_cast<redblacktree<T>*>(this->myRight); }


private:
	void rotateLeft(redblacktree<T>* tree, redblacktree<T>* node);
	void rotateRight(redblacktree<T>* tree, redblacktree<T>* node);


	void rootNodeCase(redblacktree<T>* tree, redblacktree<T>* node);
	void blackTopTest(redblacktree<T>* tree, redblacktree<T>* node);
	void redUncleCase(redblacktree<T>* tree, redblacktree<T>* node);
	void rotateCase(redblacktree<T>* tree, redblacktree<T>* node);
	void secondRotate(redblacktree<T>* tree, redblacktree<T>* node);



	int myColor;
};

template <class T>
redblacktree<T>::redblacktree(T value): binarysearchtree<T>(value),
myColor(COLOR::RED)
{
}


template <class T>
redblacktree<T>::~redblacktree()
{
	binarysearchtree<T>::~binarysearchtree();
}

template <class T>
binarynode<T>* redblacktree<T>::createElement(T value)
{ return new redblacktree<T>(value); }

template <class T>
void redblacktree<T>::rotateRight(redblacktree<T>* tree, redblacktree<T>* node)
{
	redblacktree<T>* oldLeft = node->getLeftRbTree();
	node->myLeft = oldLeft->getRight();
	node->getLeftRbTree()->setParent(node);
	node->setParent(oldLeft);
	oldLeft->setRight(node);
	node->setLeft(oldLeft);
}

template <class T>
void redblacktree<T>::rotateLeft(redblacktree<T>* tree, redblacktree<T>* node)
{
	avltree<T>* oldRight = rightAVL();
	this->myRight = oldRight->getLeft();
	oldRight->setLeft(this);
	this->fixheight();
	oldRight->fixheight();
	return oldRight;
}

template <class T>
binarynode<T>* redblacktree<T>::insert(T value)
{
	redblacktree<T>* tree = reinterpret_cast<redblacktree<T>*>(
			binarysearchtree<T>::insert(value));

	if(tree->getValue() == value)
	{
		tree->setColor(COLOR::BLACK);
	}
	else
	{
		redblacktree<T>* newNode = findNodeByValue(value);

		rootNodeCase(this, newNode);
	}

	return this;
}

template <class T>
void redblacktree<T>::rootNodeCase(redblacktree<T>* tree, redblacktree<T>* node)
{
	if(tree != 0 && node != 0)
	{
		if(node->getParent() == 0)
		{
			node-setColor(COLOR::BLACK);
		}
		blackTopTest(tree, node);
	}
}

template <class T>
void redblacktree<T>::blackTopTest(redblacktree<T>* tree, redblacktree<T>* node)
{
	if(node->getParent().getColor() != COLOR::BLACK )
	{
		redUncleCase(tree, node);
	}
}

template <class T>
void redblacktree<T>::redUncleCase(redblacktree<T>* tree, redblacktree<T>* node)
{
	redblacktree<T>* uncle = node->getUncle();
	if(0 != uncle && uncle->getColor() == COLOR::RED)
	{
		node->getParent().setColor(COLOR::BLACK);
		uncle->setColor(COLOR::BLACK);
		rootNodeCase(tree, node->getGrandparent());
	}
	else
	{
		rotateCase(tree,node);
	}
}

template <class T>
void redblacktree<T>::rotateCase(redblacktree<T>* tree, redblacktree<T>* node)
{
	redblacktree<T>* parent = node->getParent();
	redblacktree<T>* grandParent = parent != 0 ? node->getGrandParent() : 0;
	if(0 != parent && 0 != grandParent)
	{
		if (node == parent->getRight() && parent == grandParent->getLeft())
		{
			//rotate_left(tree, parent);
			node = node->getLeft();
		}
		else if (node == parent->getLeft() && parent ==  grandParent->getRight())
		{
			// rotate_left(tree, parent);
			node = node->getRight();
		}

		secondRotate(tree, node);
	}
}

template <class T>
void redblacktree<T>::secondRotate(redblacktree<T>* tree, redblacktree<T>* node)
{
	redblacktree<T>* parent = node->getParent();
	redblacktree<T>* grandParent = parent != 0 ? node->getGrandParent() : 0;
	if(0 != parent && 0 != grandParent)
	{
		parent->setColor(COLOR::BLACK);
		grandParent->setClor(COLOR::RED);
		 if (node == parent->getLeft() && parent == grandParent->getLeft())
		 {
			 // rotate_right(tree, grandparent);
		 }
		 else
		 {
			 // rotate_left(tree, grandparent);
		 }
	}
}

#endif /* REDBLACKTREE_H_ */
