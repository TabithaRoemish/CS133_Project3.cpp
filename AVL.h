#ifndef AVL_H
#define AVL_H
//--------------------------------------------------------------------
// An AVL tree class
// Compiled under MS Visual C++.Net 2005
// by Paul Bladek
// May, 2008
//--------------------------------------------------------------------

#include "bst.h"
using namespace std;


namespace PB_BST
{
	//--------------------------------------------------------------------
	// AVL Tree
	//   Class: avl<T>: public bst<T>
	//   REQUIRES Type T be able convert from int & have < & == defined
	//
	//   File: avl.h
	//   Title: avl template Class -- inherits from bst<T>
	//   Description: This file contains the class definition for avl
	//
	//   Programmer:  Paul Bladek
	// 
	//   Date:  May 2008
	//   Version: 1.1
	// 
	//   Environment: Hardware: IBM Pentium 
	//   Software: Windows XP or .Net Framework for execution;
	//
	//   Compiles under Microsoft Visual C++.Net 2005
	// 
	//   class avl<T>:
	//
	//
	//     Methods:
	// 
	//       inline: 
	//			avl() -- default constructor
	//			avl(const avl<T>& t) -- copy constructor (deep copy)
	//			avl<T>& operator+=(const T d) -- adds an element to the tree
	//			avl<T> operator+(const T d) -- adds an element to the tree
	//			void insert(T d) -- adds an element to the tree
	//			~avl() -- destructor	
	//
	//       non-inline:
	//			avl<T>& operator=(const avl<T>& t) -- deep copy
	//			avl<T>& operator+=(const avl<T>& t) -- adds an element to the tree
	//			void insert(T d, node<T>* &cur) -- adds an element to the tree
	//			
	//		protected:
	//			node<T>* rotateRight(node<T> *nodeN) -- balances tree	
	//			node<T>* rotateLeft(node<T> *nodeN) -- balances tree
	//			node<T>* rotateRightLeft(node<T> *nodeN) -- balances tree
	//			node<T>* rotateLeftRight(node<T> *nodeN) -- balances tree
	//			node<T>* rebalance(node<T> *&nodeN) -- balances tree
	//			void avl<T>:addTree(const node<T>* np)
	//			int getHeightDifference(const node<T> *const nodeN)const
	//				-- returns the height difference between the left & right subtrees 
	//
	//
	//   History Log: 
	//     May 20, 2008, PB  completed version 1.0 
	//	   June 4, 2017 TR completed version 1.1
	//------------------------------------------------------------------- 
	
	template<class T>
	class avl : public bst<T>
	{
	public:
		avl() : bst() {}
		avl(const avl<T>& t) : bst(t) {}
		avl<T>& operator=(const avl<T>& t);
		avl<T>& operator+=(const avl<T>& t);
		avl<T>& operator+=(const T d) { insert(d); return *this; }
		avl<T> operator+(const T d)
		{
			avl<T> temp = *this; temp.insert(d); return temp;
		}
		bool insert(T d) { return insert(d, root); }
		bool insert(T d, node<T>* &cur);
		T popFirstOf(const T& d) { return popFirstOf(d, root); }
		T popFirstOf(const T& d, node<T>* np);
		~avl() { delTree(); }
	protected:
		node<T>* rotateRight(node<T> *nodeN);
		node<T>* rotateLeft(node<T> *nodeN);
		node<T>* rotateRightLeft(node<T> *nodeN);
		node<T>* rotateLeftRight(node<T> *nodeN);
		node<T>* rebalance(node<T> *&nodeN);
		void addTree(const node<T>* np);
		int getHeightDifference(const node<T> *const nodeN)const;
		node<T>* balanceAt(const T& d, node<T>* np);
	};

//---------------------------------------------------------------
// AVL Defintions:
//---------------------------------------------------------------
//--------------------------------------------------
// Function: avl<T>& operator=(const avl<T>& t)
//
// Description: assign one AVL Tree to another
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: const avl<T> reference to be assigned
//
// Returns: avl<T> object reference
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	avl<T>& avl<T>::operator=(const avl<T>& t)
	{
		if (this != &t)
		{
			if (!isempty())
				bst<T>::delTree();
			if (!t.isempty())
			{
				root = new node<T>(*(t.root));
			}
		}
		return *this;
	}
//--------------------------------------------------
// Function: void avl<T>:addTree(const node<T>* np)
//
// Description: overridded addtree function for +=
//	overload, to use avl insert that rebalances
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: const node<T>* np
//
// Returns: none
//
// History Log:
//   6/3/2017 TR completed version 1.0
//--------------------------------------------------	
	template <class T>
	void avl<T>::addTree(const node<T>* np)
	{
		if (np != nullptr)
		{
			addTree(np->left);
			addTree(np->right);
			insert(np->value(), root); //calls avl insert
		}
	}
//--------------------------------------------------
// Function: avl<T>& operator+=(const avl<T>& t)
//
// Description: assign one AVL Tree to another
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: const avl<T> reference to be assigned
//
// Returns: avl<T> object reference
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	avl<T>& avl<T>::operator+=(const avl<T>& t)
	{
		addTree(t.root);
		return *this;
	}

//--------------------------------------------------
// Function: bool avl<T>::insert(T d, node<T>* &cur)
//
// Description: inserts data at specific node
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: T d - value to insert, node<T>* &cur -place to insert
//
// Returns: bool - true if insert successful (not duplicate)
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	bool avl<T>::insert(T d, node<T>* &cur)
	{
		bool canInsert = true;
		if (cur == nullptr)
		{
			cur = new node<T>(d);
			if (isempty())
				root = cur;
		}
		else
		{
			if (d < cur->value())
				insert(d, cur->left);
			else if (d > cur->value())
				insert(d, cur->right);
			else
				canInsert = false;
			
			if (root != nullptr)
				root->setHeight();

			rebalance(cur); // avl rebalance done on parent node
		}
		return canInsert;
	}
//--------------------------------------------------
// Function: T avl<T>::popFirstOf(const T& d, node<T>* np)
//
// Description: overrides bst PopFirstof, pops  node with value
//  passed in, returns node value and rebalances when popped.
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.1
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: const T& d - delete value, node<T> *&nodeN-
//	 node to begin search. 
//
// Returns: returns value of popped node. 
//
// History Log:
//   5/25/2017 TR completed version 1.0
//	 6/4/2017 TR completed version 1.1
//--------------------------------------------------
	template <class T>
	T avl<T>::popFirstOf(const T& d, node<T>* np)
	{
		node<T>* matchptr = nullptr;
		findFirstOf(d, np, matchptr);
		if (*parentptr != nullptr)
		{
			if ((*parentptr)->value() == d)
				popNode((*parentptr));
		}
		root = balanceAt(d, root); // could not resolve nullptr and setHeight() issue
		if (matchptr == nullptr)
			throw invalid_argument("Value not found");
		return 0;

	}
//--------------------------------------------------
// Function: node<T>* avl<T>::balanceAt(const T& d, node<T>* np)
//
// Description: navigates to where value would be/ would have been
//   rebalances from there. I used this method because I ran into the 
//		assignment issue with popNode and cur not being set to null.
//		- this method does not account for multiple rotations. 
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: const T& d - delete value, node<T> *&nodeN-
//	 node to begin search. 
//
// Returns: returns value of new root.
//
// History Log:
//   6/4/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	node<T>* avl<T>::balanceAt(const T& d, node<T>* np)
	{
		node<T> * temp = nullptr;
		if(np !=nullptr)
		{
			if (d < np->value())
				balanceAt(d, np->left);
			else if (d > np->value())
				balanceAt(d, np->right);
			temp = rebalance(np);
		}
		return temp;
	}
//--------------------------------------------------
// Function: node<T>* rebalance(node<T> *&nodeN)
//
// Description: rebalance the AVL tree
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: node<T> *&nodeN - node to rebalance
//
// Returns: node<T>* returns node passed in
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	node<T>* avl<T>::rebalance(node<T> *&nodeN)
	{
		int balance = getHeightDifference(nodeN);

		if (balance > 1) // right heavy
			if (getHeightDifference(nodeN->right) > 0)
				nodeN = rotateLeft(nodeN); //right right
			else
				nodeN = rotateRightLeft(nodeN); //left right
		
		if (balance < -1) // left heavy
			if (getHeightDifference(nodeN->left) < 0)
				nodeN = rotateRight(nodeN); //left left
			else
				nodeN = rotateLeftRight(nodeN); //right left
		setHeight();
		return nodeN;
	}

//--------------------------------------------------
// Function: int avl<T>::getHeightDifference
//		(const node<T> *const nodeN)const
//
// Description: find height difference of left and right nodes
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: node<T>* const nodeN -node at which to check imbalance
//
// Returns: int height difference, if negative, left imbalance
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	int avl<T>::getHeightDifference(const node<T> *const nodeN)const
	{
		if (nodeN != nullptr)
		{
			int leftH = (nodeN->left != nullptr) ? nodeN->left->getHeight() : 0;
			int rightH = (nodeN->right != nullptr) ? nodeN->right->getHeight() : 0;

			return (rightH - leftH);
		}
		else
			return 0;
	}
//--------------------------------------------------
// Function: node<T>* rotateRight(node<T> *nodeN)
//
// Description: rotates tree to the right on nodeN's right
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015  
//
// Parameters: node<T> * nodeN - node with left imbalance
//
// Returns:
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	node<T>* avl<T>::rotateRight(node<T> *nodeN)
	{
		node<T> * pivot = nodeN->left;
		node<T> *child = pivot->right;

		pivot->right = nodeN;
		nodeN->left = child;

		return pivot;
	}

//--------------------------------------------------
// Function: node<T>* rotateLeft(node<T> *nodeN)
//
// Description: rotates tree left on NodeN's right node
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: node<T> *nodeN - node with imbalance on right
//
// Returns: node<T> * nodeN - returns itself
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	node<T>* avl<T>::rotateLeft(node<T> *nodeN)
	{
		node<T> * pivot = nodeN->right;
		node<T> *child = pivot->left;

		pivot->left = nodeN;
		nodeN->right = child;

		return pivot;
	}

//--------------------------------------------------
// Function: node<T>* rotateRightLeft(node<T> *nodeN)
//
// Description: rotates tree right on nodeN's right and 
	// rotates left on nodeN
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: node<T> *nodeN - node with imbalance
//
// Returns: nodeN -returns itself
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	node<T>* avl<T>::rotateRightLeft(node<T> *nodeN)
	{
		node<T> * pivot = rotateRight(nodeN->right);
		nodeN->right = pivot;
		pivot = rotateLeft(nodeN);

		return pivot;
	}

//--------------------------------------------------
// Function: node<T>* rotateLeftRight(node<T> *nodeN)
//
// Description: rotate left on nodeN's left and rotate
// right on nodeN
// 
// Programmer: Tabitha Roemish
//
// Date: 5/25/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015
//
// Parameters: node<T> *nodeN - node with imbalance
//
// Returns: node sent in
//
// History Log:
//   5/25/2017 TR completed version 1.0
//--------------------------------------------------
	template <class T>
	node<T>* avl<T>::rotateLeftRight(node<T> *nodeN)
	{
		node<T> * pivot = rotateLeft(nodeN->left);
		nodeN->left = pivot;
		pivot = rotateRight(nodeN);

		return pivot;
	}


}
#endif
