#pragma once

#include <iostream>
using namespace std;

template<typename T>
class Node {
public:
	T value = T();
	Node <T>* next;
	Node(const T& new_value, Node <T>* next_node) {
		value = new_value;
		next = next_node;
	}
};

template<typename T>
class mlist {
protected:
	Node <T>* first;
	int size;
public:
	mlist() {
		first = nullptr;
		size = 0;
	}
	mlist(Node<T>* _first) {
		first = _first;
		size = 1;
	}
	~mlist()
	{
		while (first != nullptr)
		{
			Node<T>* temp = first;
			first = first->next;
			delete temp;
		}
		size = 0;
	}
	mlist(const mlist<T>& _list)
	{
		first = nullptr;
		size = 0;
		for (iterator it = _list.begin(); it != _list.end(); ++it)
			push_back(*it);
	}

	mlist<T>& operator=(const mlist<T>& _list)
	{
		if (this != &_list)
		{
			while (first != nullptr)
			{
				Node<T>* temp = first;
				first = first->next;
				delete temp;
			}
			size = 0;
			for (iterator it = _list.begin(); it != _list.end(); ++it)
				push_back(*it);
		}
		return *this;
	}

	void push_front(T elem) {
		Node <T>* new_node = new Node<T>(elem, first);
		this->first = new_node;
		size++;
	}
	void pop_front() {
		Node <T>* temp = first;
		if (first == nullptr)
			throw logic_error("list is already empty");
		first = temp->next;
		delete temp;
		size--;
	}

	void insert(T elem, Node<T>* p) {
		if (p == nullptr)
			push_front(elem);
		else {
			Node <T>* new_node = new Node<T>(elem, p->next);
			p->next = new_node;
			size++;
		}
	}

	void erase(Node<T>* p) {
		if (p == nullptr)
			pop_front();
		else {
			Node<T>* temp = p->next;
			if (temp != nullptr) {
				p->next = temp->next;
				delete temp;
				size--;
			}
		}
	}

	void push_back(T elem) {
		Node<T>* last_node = this->get_last();
		insert(elem, last_node);
	}

	Node<T>* get_last() {
		if (first == nullptr)
			return nullptr;
		Node <T>* temp = first;
		while (temp->next != nullptr)
			temp = temp->next;
		return temp;
	}



	class iterator {
		Node <T>* ptr;
	public:

		iterator(Node <T>* p) {
			ptr = p;
		}
		iterator(const iterator& iter) {
			ptr = iter.ptr;
		}
		iterator(const Node<T>* node) : ptr(const_cast<Node<T>*>(node)) {}

		iterator(nullptr_t p) {
			ptr = nullptr;
		}
		bool operator==(const iterator& iter) {
			return (this->ptr == iter.ptr);
		}
		bool operator!=(const iterator& iter) {
			return !(*this == iter);
		}
		const bool operator==(const iterator& it) const
		{
			return this->ptr == it.ptr;
		}
		const bool operator!=(const iterator& it) const
		{
			return this->ptr != it.ptr;
		}
		iterator& operator++() {
			ptr = ptr->next;
			return *this;
		}
		iterator operator++(int) {
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		T& operator*() {
			return ptr->value;
		}
		const T& operator*() const {
			if (ptr == nullptr)
				throw logic_error("error");
			return ptr->value;
		}
		Node<T>* get_ptr() const noexcept { return ptr; }
	};

	iterator begin() noexcept {
		return iterator(first);
	}
	iterator end() noexcept {
		return iterator(nullptr);
	}

	const iterator begin() const noexcept
	{
		return iterator(first);
	}
	const iterator end() const noexcept
	{
		return iterator(nullptr);
	}
};