// Binary Search Tree ADT: to use as data structure for Team database
// The structure is used mainly for storing data in ordered list by name and city
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Keano Zamora, So Yeon Wang

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryTree.h"
#include <iostream>
template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode, int key);

	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success, int key);

	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);

	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);

	// search for target node
	void _findSmallest(BinaryNode<ItemType>* treePtr, ItemType & target) const;
	void _findLargest(BinaryNode<ItemType>* nodePtr, ItemType & target) const;
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target, int key, void visit(ItemType &), bool& success) const;

public:
	// insert a node at the correct location
    bool insert(const ItemType & newEntry, int key);
	// remove a node if found
	bool remove(const ItemType & anEntry, int key);
	// find a target node
	bool getEntry(const ItemType& anEntry, ItemType & returnedItem, int key, void visit(ItemType &)) const;
	bool findSmallest(ItemType & result);
	bool findLargest (ItemType & result);

};


///////////////////////// public function definitions ///////////////////////////

//**************************************************
// insert: insert data into a BST
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry, int key)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
	this->rootPtr = _insert(this->rootPtr, newNodePtr, key);
	return true;
}

//**************************************************
// remove: remove data from a BST
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target, int key)
{
	bool isSuccessful = false;
	this->rootPtr = _remove(this->rootPtr, target, isSuccessful, key);
	if (isSuccessful)
		this->count--;
	return isSuccessful;
}

//**************************************************
// searchKey: Search a BST for a given target: if found, returns true and passes back
// data, otherwise returns false.
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem, int key, void visit(ItemType &)) const
{
    bool success = false;
	BinaryNode<ItemType>* nodePtr = findNode(this->rootPtr, anEntry, key, visit, success);
	if (success == true && key == 2)
	{
		return success;
	}
	if (success != true && key == 2)
		return false;
	if (nodePtr) {
		returnedItem = nodePtr->getItem();
		success = true;
	}
	return success;

}

//**************************************************
// findSmallest: find the smallest number of student ID
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::findSmallest(ItemType & result)
{
    _findSmallest(this->rootPtr, result);
    return true;
}

//**************************************************
// findLargest: find the largest number of student ID
//**************************************************
template<class ItemType>
bool BinarySearchTree<ItemType>::findLargest(ItemType & result)
{
    _findLargest(this->rootPtr, result);
    return true;
}

//**************************************************
// findSmallest: find the smallest number of student ID
//**************************************************
template<class ItemType>
void BinarySearchTree<ItemType>::_findSmallest(BinaryNode<ItemType>* nodePtr, ItemType & target) const
{
    if (nodePtr)
    {
        target = nodePtr->getItem();
        _findSmallest(nodePtr->getLeftPtr(), target);
    }
}

//**************************************************
// findLargest: find the largest number of student ID
//**************************************************
template<class ItemType>
void BinarySearchTree<ItemType>::_findLargest(BinaryNode<ItemType>* nodePtr, ItemType & target) const
{
    if (nodePtr)
    {
        target = nodePtr->getItem();
        _findLargest(nodePtr->getRightPtr(), target);
    }
}


//////////////////////////// private functions ////////////////////////////////////////////
//**************************************************
// _insert: insert data into a BST
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr, int key)
{

    BinaryNode<ItemType> *pWalk;
    BinaryNode<ItemType> *parent = NULL;

    if (!nodePtr)
    {
        nodePtr = newNodePtr;
        return nodePtr;
    }

    if (key == 1)
    {
        pWalk = nodePtr;
        while( pWalk )
        {
            parent = pWalk;
            if( (*newNodePtr->getItem()) < (*pWalk->getItem()) )
                pWalk = pWalk->getLeftPtr();
            else
                pWalk = pWalk->getRightPtr();
        }

        // insert the new node
        if( (*newNodePtr->getItem()) < (*parent->getItem()) ) // no left child
             parent->setLeftPtr(newNodePtr);
        else
             parent->setRightPtr(newNodePtr);
    }
    else if (key == 2)
    {
        pWalk = nodePtr;
        while( pWalk )
        {
            parent = pWalk;
            if( (*newNodePtr->getItem()) <= (*pWalk->getItem()) )
                pWalk = pWalk->getLeftPtr();
            else
                pWalk = pWalk->getRightPtr();
        }

        // insert the new node
        if( (*newNodePtr->getItem()) <= (*parent->getItem()) ) // no left child
             parent->setLeftPtr(newNodePtr);
        else
             parent->setRightPtr(newNodePtr);
    }

//    count++;
    return nodePtr;

}

//**************************************************
// _remove: remove data from a BST
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
	const ItemType target, bool & success, int key)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
	if (key == 1) {
		if ((*nodePtr->getItem()) > *target)
			nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, key));
		else if ((*nodePtr->getItem()) < *target)
			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, key));
		else if ((*nodePtr->getItem()) == *target)
		{
			nodePtr = deleteNode(nodePtr);
			success = true;
		}
		return nodePtr;
	}
	if (key == 2)
	{
		if ((*nodePtr->getItem()) >= *target)
			nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success, key));
		else if ((*nodePtr->getItem()) <= *target)
			nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success, key));
		else if ((*nodePtr->getItem()) != *target)
		{
			nodePtr = deleteNode(nodePtr);
			success = true;
		}
        return nodePtr;
	}
    return nodePtr;
}
//**************************************************
// removeLeftmostNode: remove data on left from BST
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
	const ItemType & target, int key, void visit(ItemType &), bool& success) const
{
	BinaryNode<ItemType>* findPtr = nodePtr;
	if (findPtr == NULL)
		return findPtr;
	if (key == 1)
	{
		if (*(findPtr->getItem()) == *target)
			return findPtr;
		if (*(findPtr->getItem()) > *target)
			findPtr = findNode(findPtr->getLeftPtr(), target, key, visit, success);
		else
			findPtr = findNode(findPtr->getRightPtr(), target, key, visit, success);

	}
	if (key != 1)
	{
		ItemType item = nodePtr->getItem();
		if (*target % *item) {
			visit(item);
			success = true;
		}
		findNode(nodePtr->getLeftPtr(), target, key, visit, success);
		findNode(nodePtr->getRightPtr(), target, key, visit, success);
	}
	return findPtr;
}

//**************************************************
// deleteNode: traverses the binary tree in postorder and deletes every node
//**************************************************
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}
#endif
