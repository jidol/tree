/*
 * node.h
 *
 *  Created on: Jan 16, 2016
 *      Author: jidol
 */

#ifndef BNODE_H_
#define BNODE_H_
#include <sstream>


template <class T>
class binarynode
{
public:
	binarynode(T value);
	virtual ~binarynode();

	inline binarynode<T>* getLeft() { return myLeft; };
	inline binarynode<T>* getRight() { return myRight; };
	inline T getValue() { return myValue; };

	virtual binarynode<T>* insert(T value);

	virtual binarynode<T>* findNodeByValue(T value);

	int getHeight();

	std::string toString();

protected:
	T myValue;
	binarynode* myLeft;
	binarynode* myRight;

};

template <class T>
binarynode<T>::binarynode(T value):
myValue(value),
myLeft(0),
myRight(0)
{
}

template <class T>
binarynode<T>::~binarynode()
{
	if(0 != myLeft)
	{
		delete myLeft;
		myLeft = 0;
	}
	if(0 != myRight)
	{
		delete myRight;
		myRight = 0;
	}
}

template <class T>
binarynode<T>* binarynode<T>::insert(T value)
{
	// Only insert new values
	if(0 == findNodeByValue(value))
	{
		if(0 == myLeft)
		{
			myLeft = new binarynode<T>(value);
		}
		else if(0 == myRight)
		{
			myRight = new binarynode<T>(value);
		}
		else
		{
			int leftHeight = myLeft->getHeight();
			int rightHeight = myRight->getHeight();

			if(leftHeight < rightHeight)
			{
				myLeft = myLeft->insert(value);
			}
			else
			{
				myRight = myRight->insert(value);
			}
		}
	}
	return this;

}

template <class T>
int binarynode<T>::getHeight()
{
	int height = 1;

	if (0 != myLeft)
	{
		height += myLeft->getHeight();
	}
	if (0 != myRight)
	{
		height += myRight->getHeight();
	}

	return height;
}

template <class T>
binarynode<T>* binarynode<T>::findNodeByValue(T value)
{
	if(value == myValue)
	{
		return this;
	}
	else
	{
		binarynode<T>* result = 0 != myRight ? myRight->findNodeByValue(value) : 0;
		if (0 == result && 0 != myLeft)
		{
			result = myLeft->findNodeByValue(value);
		}

		return result;
	}
}

template <class T>
std::string binarynode<T>::toString()
{
	std::ostringstream out;

	out << "Value: " << myValue << std::endl;
	if(0 != myRight)
	{
		out << "Right Child:  " << std::endl;
		out << myRight->toString() << std::endl;
	}
	else
	{
		out << "Right Child: NULL" << std::endl;
	}
	if(0 != myLeft)
	{
		out << "Left Child:  " << std::endl;
		out << myLeft->toString() << std::endl;

	}
	else
	{
		out << "Left Child:  NULL" << std::endl;

	}

	return out.str();
}


#endif /* NODE_H_ */
