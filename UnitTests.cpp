#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "avl.h"
#include "Set.h"

using namespace PB_BST;

TEST_CASE("Operator Overloads")
{
	avl<int> test;
	avl<int> test2;

	for (int num :
	{15, 6, 30, 4, 10, 23, 50})
	{
		test.insert(num);
		test2.insert(num * 2 + 3);
	}

	SECTION("Test =operator")
	{
		test = test2;

		REQUIRE(*test.getroot() == 33);
		REQUIRE(*test.getroot()->left == 15);
		REQUIRE(*test.getroot()->left->left == 11);
		REQUIRE(*test.getroot()->left->right == 23);
		REQUIRE(*test.getroot()->right == 63);
		REQUIRE(*test.getroot()->right->right == 103);
		REQUIRE(*test.getroot()->right->left == 49);
	}

	SECTION("Test += operator")
	{
		test += test2;

		REQUIRE(*test.getroot() == 15);
		REQUIRE(*test.getroot()->left == 6);
		REQUIRE(*test.getroot()->left->left == 4);
		REQUIRE(*test.getroot()->left->right == 10);
		REQUIRE(*test.getroot()->left->right->right == 11);
		REQUIRE(*test.getroot()->right == 50);
		REQUIRE(*test.getroot()->right->left == 30);
		REQUIRE(*test.getroot()->right->left->left == 23);
		REQUIRE(*test.getroot()->right->left->right->left == 33);
		REQUIRE(*test.getroot()->right->left->right == 49);
		REQUIRE(*test.getroot()->right->right->left == 63);
		REQUIRE(*test.getroot()->right->right == 103);
		
	}
}

TEST_CASE("Test insert and balance") 
{

	avl<int> test;

	SECTION("Check empty tree")
	{
		REQUIRE(test.getHeight() == 0);
		REQUIRE(test.getNumberOfNodes() == 0);
	}

	SECTION("Test RotateRight on insert")
	{
		test.insert(90);
		test.insert(100);
		test.insert(80);
		test.insert(85);
		test.insert(70);
		test.insert(60); // left imbalance, should rebalance with rotate right
		REQUIRE(*test.getroot() == 80);
		REQUIRE(*test.getroot()->left == 70);
		REQUIRE(*test.getroot()->left->left == 60);
		REQUIRE(*test.getroot()->right == 90);
		REQUIRE(*test.getroot()->right->right == 100);
		REQUIRE(*test.getroot()->right->left == 85);
	}

	SECTION("Test RotateLeft on insert")
	{
		test.insert(60);
		test.insert(50);
		test.insert(70);
		test.insert(65);
		test.insert(80);
		test.insert(90); // right imbalance, should rebalance with rotate left

		REQUIRE(*test.getroot() == 70);
		REQUIRE(*test.getroot()->left == 60);
		REQUIRE(*test.getroot()->left->left == 50);
		REQUIRE(*test.getroot()->left->right == 65);
		REQUIRE(*test.getroot()->right == 80);
		REQUIRE(*test.getroot()->right->right == 90);
	}

	SECTION("Test RotateRightLeft on insert")
	{
		test.insert(60);
		test.insert(50);
		test.insert(80);
		test.insert(90);
		test.insert(70);
		test.insert(75); // right left imbalance, should rotate right then left

		REQUIRE(*test.getroot() == 70);
		REQUIRE(*test.getroot()->left == 60);
		REQUIRE(*test.getroot()->left->left == 50);
		REQUIRE(*test.getroot()->right == 80);
		REQUIRE(*test.getroot()->right->right == 90);
		REQUIRE(*test.getroot()->right->left == 75);
	}

	SECTION("Test RotateLeftRight on insert")
	{
		test.insert(60);
		test.insert(80);
		test.insert(30);
		test.insert(20);
		test.insert(35);
		test.insert(40);// left right imbalance, should rotate left then right

		REQUIRE(*test.getroot() == 35);
		REQUIRE(*test.getroot()->left == 30);
		REQUIRE(*test.getroot()->left->left == 20);
		REQUIRE(*test.getroot()->right == 60);
		REQUIRE(*test.getroot()->right->right == 80);
		REQUIRE(*test.getroot()->right->left == 40);
	}

	SECTION("Test large tree")
	{
		for (int num : 
		{50, 40, 60, 70, 75, 45, 90, 30, 35,
			25, 6, 55, 80, 73, 71}) 
		{
			test.insert(num);
		}
		REQUIRE(*test.getroot() == 50);
		REQUIRE(*test.getroot()->left == 30);
		REQUIRE(*test.getroot()->right == 70);
		REQUIRE(*test.getroot()->left->left == 25);
		REQUIRE(*test.getroot()->left->right == 40);
		REQUIRE(*test.getroot()->right->left == 60);
		REQUIRE(*test.getroot()->right->right == 80);
		REQUIRE(*test.getroot()->left->right->left == 35);
		REQUIRE(*test.getroot()->left->right->right == 45);
		REQUIRE(*test.getroot()->right->left->left == 55);
		REQUIRE(*test.getroot()->right->right->left == 73);
		REQUIRE(*test.getroot()->right->right->right == 90);
	}
}

TEST_CASE("Test deleting and balance")
{
		avl<int> test;

		SECTION("Test no child delete")
		{
			test.insert(60);
			test.insert(70);
			test.insert(50);
			test.insert(75);

			test.popFirstOf(75);

			REQUIRE(*test.getroot() == 60);
			REQUIRE(*test.getroot()->right == 70);
			REQUIRE(*test.getroot()->left == 50);
			REQUIRE_THROWS_WITH(test.popFirstOf(75), "Value not found");
		}

		SECTION("Test deletion on right with left, left imbalance")
		{
			test.insert(60);
			test.insert(70);
			test.insert(50);
			test.insert(75);
			test.insert(55);
			test.insert(40);
			test.insert(45);

			test.popFirstOf(75);

			REQUIRE(*test.getroot() == 50);
			REQUIRE(*test.getroot()->left == 40);
			REQUIRE(*test.getroot()->left->right == 45);
			REQUIRE(*test.getroot()->right == 60);
			REQUIRE(*test.getroot()->right->right == 70);
			REQUIRE(*test.getroot()->right->left == 55);
			REQUIRE_THROWS_WITH(test.popFirstOf(75), "Value not found");
		}

		SECTION("Test deletion on right with left imbalance")
		{
			for (int num :
			{50, 30, 70, 20, 85, 40, 65, 25, 80, 60, 95, 100})
			{
				test.insert(num);
			}
			test.popFirstOf(20);

			REQUIRE(*test.getroot() == 70);
			REQUIRE(*test.getroot()->left == 50);
			REQUIRE(*test.getroot()->right == 85);
			REQUIRE(*test.getroot()->right->right == 95);
			REQUIRE(*test.getroot()->right->right->right == 100);
			REQUIRE(*test.getroot()->right->left == 80);
			REQUIRE(*test.getroot()->left->right == 65);
			REQUIRE(*test.getroot()->left->right->left == 60);
			REQUIRE(*test.getroot()->left->left == 30);
			REQUIRE(*test.getroot()->left->left->left == 25);
			REQUIRE(*test.getroot()->left->left->right == 40);
			REQUIRE_THROWS_WITH(test.popFirstOf(20), "Value not found");
		}

		SECTION("Test deletion with multiple rotation")
		{
			for (int num :
			{50, 30, 60, 25, 80, 45, 55, 46, 58, 70, 90, 75})
			{
				test.insert(num);
			}
			
			test.popFirstOf(25);

			REQUIRE(*test.getroot() == 60);
			REQUIRE(*test.getroot()->left == 50);
			REQUIRE(*test.getroot()->right == 80);
			REQUIRE(*test.getroot()->right->right == 90);
			REQUIRE(*test.getroot()->right->left->right == 75);
			REQUIRE(*test.getroot()->right->left == 70);
			REQUIRE(*test.getroot()->left->right == 55);
			REQUIRE(*test.getroot()->left->right->right == 58);
			REQUIRE(*test.getroot()->left->left == 45);
			REQUIRE(*test.getroot()->left->left->left == 30);
			REQUIRE(*test.getroot()->left->left->right == 48);
		
		}
	
}
	
TEST_CASE("Set testing")
{
		Set<int> stest;
		Set<int> stest2;
		
		for (int num :
		{10, 11, 8, 5, 9, 3, 6})
		{
			stest.insert(num);
			stest.insert(num - 2);
		}
		
		SECTION("Test isMember")
		{
			REQUIRE(stest.isMember(9) == true);
			REQUIRE(stest.isMember(1) == false);
		}

		SECTION("Test Remove")
		{
			stest.remove(9);
			REQUIRE(stest.isMember(9) == false);
		}

		SECTION("Test union")
		{
			stest.union_set(stest2);

			for (int num : {10, 8, 11, 9, 8, 6, 5, 3, 9, 7, 3, 1, 6, 4})
			{
				REQUIRE(stest.isMember(num) == true);
			}
			
		}

		/*SECTION("Test intersection");
		{
			Set<int> stest3;
			stest3 = stest.intersection(test2);

			for (int num : {8, 6, 3})
				REQUIRE(stest3.isMember(num));
		}*/
}




