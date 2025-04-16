
#include "mlist.h"
#include <gtest.h>

TEST(Node, can_create_node)
{
	ASSERT_NO_THROW(Node<int> node(10, nullptr));
}

TEST(Node, can_get_value)
{
	Node<int> node(10, nullptr);
	EXPECT_EQ(node.value, 10);
}

TEST(Node, can_get_next)
{
	Node<int> node(10, nullptr);
	EXPECT_EQ(node.next, nullptr);
}

TEST(mlist, can_create_list)
{
	Node<int>* node = new Node<int>(10, nullptr);
	ASSERT_NO_THROW(mlist<int> list(node));
}

TEST(mlist, can_create_list_)
{
	ASSERT_NO_THROW(mlist<int> list());
}

TEST(mlist, can_create_empty_list)
{
	mlist<int> list;
	EXPECT_EQ(list.begin(), list.end());
}

TEST(mlist, can_push_front)
{
	mlist<int> list;
	list.push_front(8);
	EXPECT_EQ(*list.begin(), 8);
}

TEST(mlist, can_pop_front)
{
	Node<int>* node = new Node<int>(10, nullptr);
	mlist<int> list(node);
	list.push_front(8);
	list.pop_front();
	EXPECT_EQ(*list.begin(), 10);
}

TEST(mlist, can_erase)
{
	Node<int>* node = new Node<int>(10, nullptr);
	mlist<int> list(node);
	list.push_front(8);
	mlist<int>::iterator it = list.begin();
	list.erase(it.get_ptr());
	EXPECT_EQ(*list.begin(), 8);
}


TEST(mlist, can_push_back)
{
	mlist<int> list;
	list.push_back(8);
	list.push_back(7);
	list.push_back(6);
	mlist<int>::iterator it = list.begin();
	mlist<int>::iterator it1 = list.begin();
	++it;
	EXPECT_EQ((*it), 7);
	++it;
	EXPECT_EQ((*it), 6);
	list.push_back(*it1);
	++it;
	EXPECT_EQ((*it), 8);
}

TEST(mlist, can_get_last)
{
	mlist<int> list;
	list.push_back(8);
	list.push_back(6);
	list.push_back(7);
	EXPECT_EQ(list.get_last()->value, 7);
}

TEST(mlist, can_return_begin)
{
	Node<int>* node = new Node<int>(10, nullptr);
	mlist<int> list(node);
	list.push_back(8);
	EXPECT_EQ(*list.begin(), 10);
}

TEST(mlist, can_return_end)
{
	Node<int>* node = new Node<int>(10, nullptr);
	mlist<int> list(node);
	list.push_back(8);
	EXPECT_EQ(list.end(), nullptr);
}