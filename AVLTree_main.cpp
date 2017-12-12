////-----------------------------------------------------
//// File: AVLTree_main.cpp
//// 
//// Functions: main
////-----------------------------------------------------
//
//#include "AVL.h"
//#include "BST.h"
//#include "Set.h"
//#include <iostream>
//#include <cstdlib>
//
//using namespace std;
//using namespace PB_BST;
//
////--------------------------------------------------
//// Function: main() 
////
//// Title: AVL Tree
////
//// Description: 
////  Using an AVL Tree
////
//// Programmer: Tabitha Roemish
////
//// Date: 5/25/2017 
////
//// Version: 1.0 
////
//// Environment: // Hardware: Intel core i5
////   Software: Windows 10
////   Compiles under Microsoft Visual Studio 2015
////
//// Output:  Tree display
////
//// Parameters: void 
////
//// Returns: EXIT_SUCCESS 
////
//// History Log:
////   5/25/2017 TR completed version 1.0
////--------------------------------------------------
//
//int main(void)
//{
//
//	try
//	{
//		bst<int> bstTest;
//		bst<int> bstTest2;
//		avl<int> avlTest;
//		avl<int> avlTest2;
//		avl<int> avlTest3;
//		
//		int c;
//		
//		cout << "enter some numbers, followed by x to stop.\n";
//		while(std::cin >> c)
//		{
//			bstTest.insert(c);
//			avlTest.insert(c);
//			avlTest2.insert(c);
//			avlTest3.insert(c * 2 + 3);
//		} 
//	
//		bstTest.printXlevel(cout);
//		bstTest2 = bstTest;
//		cout << "printing bstTest2 = bstTest: bstTest2" << endl;
//		bstTest2.printXlevel(cout);
//
//		cout << "output avlTest" << endl;
//		avlTest.printXlevel(cout);
//
//		avlTest2 = avlTest;
//		cout << "output avlTest2 = avlTest: avlTest2" << endl;
//		avlTest2.printXlevel(cout);
//
//		avlTest2.print(cout);
//		avlTest2 += avlTest3;
//		cout << "output avlTest2 += avlTest3: " << endl;
//		avlTest2.printXlevel(cout);
//		
//		avl<int> ctest;
//		
//		int ctestList[] = { 50, 30, 70, 20, 85, 40, 65, 25, 80, 60, 95, 100 };
//		for (int i = 0; i < 12; i++)
//			ctest.insert(ctestList[i]);
//		
//		cout << "Here is a pre-populated tree" << endl;
//		ctest.printXlevel(cout);
//
//		ctest.popFirstOf(50);
//		cout << "Here is your tree with 50 deleted:"  << endl;
//		ctest.printXlevel(cout);
//		
//		/*avl<int> large;
//		int list[] = { 50, 30, 60, 25, 80, 45, 55, 46, 58, 70, 90, 75 };
//		for(int i = 0; i < 12; i++)
//			large.insert(list[i]);
//
//		cout << "Here is a pre-poplated large list: " << endl;
//		large.printXlevel(cout);
//		cout << endl;
//		cout << "Here is large with 25 deleted: " << endl;
//		large.popFirstOf(25);
//		large.printXlevel(cout);
//		cout << endl;*/
//
//		cout << "Here is a pre-popluated Set: " << endl;
//		Set<int> tester;
//		tester.insert(3);
//		tester.insert(1);
//		tester.insert(4);
//		tester.print(cout);
//		
//
//	}
//	catch (invalid_argument e)
//	{
//		cout << "Exception: " << e.what() << endl;
//		cout << "press \"Enter\" to continue" << endl;
//		cin.get(); // keep window open
//		return EXIT_FAILURE;
//	}
//	catch (bad_alloc e)
//	{
//		cout << "Exception: " << e.what() << endl;
//		cout << "press \"Enter\" to continue" << endl;
//		cin.get(); // keep window open
//		return EXIT_FAILURE;
//	}
//	catch (exception e)
//	{
//		cout << "Exception: " << e.what() << endl;
//		cout << "press \"Enter\" to continue" << endl;
//		cin.get(); // keep window open
//		return EXIT_FAILURE;
//	}
//	
//	cout << "press \"Enter\" to continue" << endl;
//	cin.clear();
//	cin.get();
//	cin.get();
//	cin.get(); // keep window open
//	
//	return EXIT_SUCCESS;
//}