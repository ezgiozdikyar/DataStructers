/**
* @author: Ezgi OZDIKYAR
* @date: December,2020
*/
#include "ThreadedBST.h"
#include<iostream>
using namespace std;
///-----------------------------------------------
/// Erases all nodes in the tree
/// 
void ThreadedBST::eraseTreeNodes(BSTNode* node)
{
    BSTNode* curr = this->min();
    while (curr)
    {
        BSTNode* n = this->next(curr);
        delete curr;
        curr = n;
    }
} //end-eraseTreeNodes

///-----------------------------------------------
/// Adds a given key to the BST
/// 
void ThreadedBST::add(int key)
{
    if (root == NULL)
    {
        root = new BSTNode(key);
        root->left = root->right = NULL;
        return;
    }
    BSTNode* tempNode = root;
    BSTNode* parent = NULL;
    while (tempNode)
    {
        parent = tempNode;
        if (key == tempNode->key)
            return;
        if (key > tempNode->key)
        {
            if (tempNode->rightLinkType == CHILD)
                tempNode = tempNode->right;
            else
                break;           
        }
        else
        {
            if (tempNode->leftLinkType == CHILD)
                tempNode = tempNode->left;
            else
                break;
        }
    }
    BSTNode* newNode = new BSTNode(key);
    newNode->leftLinkType = THREAD;
    newNode->rightLinkType = THREAD;
    if (key < parent->key)
    {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->leftLinkType = CHILD;
        parent->left = newNode;
    }
    else
    {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rightLinkType = CHILD;
        parent->right = newNode;
    }
} // end-add

///-----------------------------------------------
/// Removes a given key from the BST (if it exists)
/// 
void ThreadedBST::remove(int key)
{
    BSTNode* parent = NULL, * child = root;    
    while (child != NULL) 
    {
        if (key == child->key)
            break;
       
        parent = child;
        if (key < child->key) 
        {
            if (child->leftLinkType == CHILD)
                child = child->left;
            else
                break;
        }
        else
        {
            if (child->rightLinkType == CHILD)
                child = child->right;
            else
                break;
        }
    }
    BSTNode* current = child;
    if (child->rightLinkType == CHILD && child->leftLinkType == CHILD)
    {
        parent = child; 
        current = child->left;   
        while (current->rightLinkType==CHILD)
        {
            parent = current;
            current = current->right;
        }
        child->key = current->key;        
    }
    BSTNode* max = NULL;
    BSTNode* min = NULL;
    if (parent->key >= current->key) 
    {
        if (current->rightLinkType == THREAD && current->leftLinkType == THREAD)
        {
            parent->left = current->left;
            parent->leftLinkType = THREAD;
        }
        else if (current->rightLinkType == THREAD)
        {
            max = current->left;
            while (max->rightLinkType == CHILD)
            {
                max = max->right;
            }
            max->right = parent;
            parent->left = current->left;
        }
        else 
        {
            min = current->right;
            while (min->leftLinkType == CHILD) 
            {
                min = min->left;
            }
            min->left = current->left;
            parent->left = current->right;
        }
        delete current;
    }
    else 
    {
        if (current->rightLinkType == THREAD && current->leftLinkType == THREAD)
        {
            parent->right = current->right;
            parent->rightLinkType = THREAD;
        }
        else if (current->rightLinkType==THREAD) 
        {
            max = current->left;
            while (max->rightLinkType == CHILD) 
            {
                max = max->right;
            }
            max->right = current->right;
            parent->right = current->left;
        }
        else 
        {
            min = current->right;
            while (min->leftLinkType == CHILD)
            {
                min = min->left;
            }
            min->left = parent;
            parent->right = current->right;
        }
        delete current;
    }
} // end-remove

///-----------------------------------------------
/// Searches a given key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::find(int key)
{
    BSTNode* temp = root;
    while (temp)
    {
        if (key == temp->key)
            return temp;
        if (key < temp->key)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return NULL;
} // end-find

///-----------------------------------------------
/// Returns the minimum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::min()
{
    if (root == NULL)
        return NULL;
    BSTNode* temp = root;
    while (temp->left)
        temp = temp->left;

    return temp;
} // end-min

///-----------------------------------------------
/// Returns the maximum key in the ThreadedBST
/// Return a pointer to the node that holds the key
/// If the key is not found, return NULL
/// 
BSTNode* ThreadedBST::max()
{
    if (root == NULL)
        return NULL;
    BSTNode* temp = root;
    while (temp->right)
        temp = temp->right;

    return temp;
} // end-max

///-----------------------------------------------
/// Given a valid pointer to a node in ThreadedBST,
/// returns a pointer to the node that contains the inorder predecessor
/// If the inorder predecessor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::previous(BSTNode* node)
{
    if (node == NULL)
        return NULL;
    if (node->leftLinkType == THREAD)
        return node->left;
    else
    {
        node = node->left;
        while (node->rightLinkType == CHILD)
            node = node->right;
    }
    return node;
}

///-----------------------------------------------
/// Given a valid pointer to a node in the ThreadedBST,
/// returns a pointer to the node that contains the inorder successor
/// If the inorder successor does not exist, returns NULL
/// 
BSTNode* ThreadedBST::next(BSTNode* node)
{
    if (node == NULL)
        return NULL;
    if (node->rightLinkType == THREAD)
        return node->right;
    else
    {
        node = node->right;
        while (node->leftLinkType == CHILD)
            node = node->left;      
    }
    return node;
} // end-next

