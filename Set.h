#ifndef SET_H
#define SET_H


namespace PB_BST
{
	//--------------------------------------------------------------------
	// AVL Tree
	//   Class: set<T>: protected avl<T>
	//   REQUIRES Type T be able convert from int & have < & == defined
	//
	//   File: Set.h
	//   Title: set template Class -- inherits from avl<T>
	//   Description: This file contains the class definition for Set
	//
	//   Programmer:  Tabitha Roemish
	// 
	//   Date:  June 2017
	//   Version: 1.0
	// 
	// Environment: // Hardware: Intel core i5
	//  Software: Windows 10
	//   Compiles under Microsoft Visual Studio 2015 
	// 
	//   class set<T>:
	//
	//     Methods:	
	//       non-inline:
	//			Set() : avl();
	//			~set() {};
	//			bool remove(T);
	//			bool isMember();
	//			Set<T> union_set(Set<T>);
	//			Set<T> intersection(Set<T>);
	//			void print(ostream& sout);
	//			bool insert(T & t);
	//
	//   History Log:  
	//	   June 4, 2017 TR completed version 1.1
	//------------------------------------------------------------------- 
	template<class T>
	class Set : protected avl<T>
	{
	public:
		Set() : avl() {};
		~Set() { bst<T>::delTree(); };
		bool insert(const T& d) {return avl<T>::insert(d);};
		bool remove(const T& d);
		bool isMember(const T& d);
		void print(ostream& out)const { bst<T>::print(out); }
		void printXlevel(ostream& out) const { bst<T>::printXlevel(out); }
		Set<T> union_set(Set<T> set);
		Set<T> intersection(Set<T> set, node<T> * ptr);
		/*Set<T> intersection(Set<T> set) {
			reset(matches); return intersection(set, avl<T>::root);
		};
		static Set<T> matches;*/
	private:
		void reset(Set<T> set) { set.~Set(); };
		

	};
//------------------------------------------------------------------------
//set<T> definitions
//------------------------------------------------------------------------

//--------------------------------------------------
// Function: bool remove(const T& d)
//
// Description: removes T from set
// 
// Programmer: Tabitha Roemish
//
// Date: 6/4/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: T - item to remove
//
// Returns: bool - true if removed, false if not
//
// History Log:
//    6/4/2017 TR completed version 1.0
//--------------------------------------------------
	template<class T>
	bool Set<T>::remove(const T& d)
	{
		try
		{
			popFirstOf(d);
		}
		catch (invalid_argument e)
		{
			return false;
		}
		return true;
	}

	
//--------------------------------------------------
// Function: bool Set<T>::isMember(const T& d)
//
// Description: checks if d is in set
// 
// Programmer: Tabitha Roemish
//
// Date: 6/4/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: T d - item to find
//
// Returns: bool - true if found, false if not
//
// History Log:
//    6/4/2017 TR completed version 1.0
//--------------------------------------------------
	template<class T>
	bool Set<T>::isMember(const T& d)
	{
		node<T>* found = nullptr;
		findFirstOf(d, root, found);
		if (found != nullptr)
			return true;
		else
			return false;
	}

//--------------------------------------------------
// Function: Set<T> Set<T>::union_set(Set<T>)
//
// Description: adds two sets together
// 
// Programmer: Tabitha Roemish
//
// Date: 6/4/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: Set<T> set to add to the other set
//
// Returns: Set<T> - mega tree. 
//
// History Log:
//    6/4/2017 TR completed version 1.0
//--------------------------------------------------
	template<class T>
	Set<T> Set<T>::union_set(Set<T> set)
	{
		addTree(set.root);
		return *this;
	}

//--------------------------------------------------
// Function: Set<T> Set<T>::union_set(Set<T>)
//
// Description: checks if 
// 
// Programmer: Tabitha Roemish
//
// Date: 6/4/2017 
//
// Version: 1.0 
//
// Environment: // Hardware: Intel core i5
//  Software: Windows 10
//   Compiles under Microsoft Visual Studio 2015 
//
// Parameters: 
//
// Returns: Set<T>
//
// History Log:
//    6/4/2017 TR completed version 1.0
//---------------------------------------------------
	template<class T>
	Set<T> Set<T>::intersection(Set<T> set, node<T> * ptr)
	{
		
		if (isMember(ptr->value()))
			matches.insert(ptr->value());
		else if (ptr != nullptr)
		{
			intersection(set, ptr->left);
			intersection(set, ptr->right);
		}
			
		return matches;

	}


	
}



#endif