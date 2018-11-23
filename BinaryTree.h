// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Keano Zamora

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "team.h"
#include "Queue.h"
#include <iostream>

using namespace std;

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree() {rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { if (rootPtr)  destroyTree(rootPtr); }

	// common functions for all binary trees
 	bool isEmpty() const	{return count == 0;}
	int size() const	    {return count;}
	void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    void indentList(void visit(ItemType &, int &)) const {int indent=0;_indentlist(visit, rootPtr, indent);}
	void breadthFirst(void visit(ItemType &));

	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData, int key) = 0;
	virtual bool remove(const ItemType & data, int key) = 0;
	virtual bool getEntry(const ItemType& anEntry, ItemType & returnedItem, int key, void visit(ItemType &)) const = 0;
	virtual bool findSmallest(ItemType & result) = 0;
	virtual bool findLargest (ItemType & result) = 0;

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
//    void _indentlist(void func(ItemType &, int &), BinaryNode<ItemType>* nodePtr, int &) const;
void _indentlist(void visit(ItemType &, int &), BinaryNode<ItemType>* nodePtr, int) const;
};

//////////////////////////////////////////////////////////////////////////

//**************************************************
// copyTree: copy from the tree rooted at nodePtr and returns a pointer to the copy
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;


    return newNodePtr;
}

//**************************************************
// destroyTree: destructor
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
    if (rootPtr)
    {
        destroyTree(rootPtr->getLeftPtr());
        destroyTree(rootPtr->getRightPtr());
        delete rootPtr;
    }
    return;
}

//**************************************************
// _preorder: print the elements of the BST in pre-order
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

//**************************************************
// _inorder: print the elements of the BST in in-order
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
        _inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

//**************************************************
// _postorder: print the elements of the BST in post-order
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
        _postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
        visit(item);
	}
}

//**************************************************
// breadthFirst: print the elements of the BST in breadth-first order
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::breadthFirst(void visit(ItemType &))
{

    Queue<BinaryNode<ItemType>*> queue;
    BinaryNode<ItemType>* nodePtr = rootPtr;
    BinaryNode<ItemType>* returnPtr;
    ItemType anItem;
    if(rootPtr)
        queue.enqueue(nodePtr);
    while (!queue.isEmpty())
    {
        queue.queueFront(nodePtr);
        queue.dequeue(returnPtr);
        anItem = returnPtr->getItem();
        visit(anItem);
        if (nodePtr->getLeftPtr() != NULL)
            queue.enqueue(nodePtr->getLeftPtr());
        if (nodePtr->getRightPtr() != NULL)
            queue.enqueue(nodePtr->getRightPtr());
    }

}

//**************************************************
// indentDisplay: print the elements of the BST as indented list
//**************************************************
template<class ItemType>
void BinaryTree<ItemType>::_indentlist(void visit(ItemType &, int &), BinaryNode<ItemType>* nodePtr, int indent) const
{
    if (nodePtr != 0)
	{
	    ItemType item = nodePtr->getItem();
		visit(item, indent);
        if (nodePtr->getRightPtr() != NULL)
            _indentlist(visit, nodePtr->getRightPtr(), indent+4);
		if (nodePtr->getLeftPtr() != NULL)
            _indentlist(visit, nodePtr->getLeftPtr(), indent+4);
	}
}

#endif

