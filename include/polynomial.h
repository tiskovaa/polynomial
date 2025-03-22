#pragma once

#include "mlist.h"
#include <string>
#include <iostream>

using namespace std;
int MAX_DEG = 9;

class Monom {
public:
	int degree;
	double k;

	Monom(int deg = 0, double _k = 0) {
		degree = deg;
		k = _k;
		if (degree > 999)
			throw invalid_argument("Monom constructor: degree is out of range");
	}
	int x_deg() const noexcept {
		return degree / 100;
	}
	int y_deg() const noexcept {
		return (degree / 10) % 10;
	}
	int z_deg() const noexcept {
		return (degree % 10);
	}
	bool is_deg_correct() const noexcept {
		return ((x_deg() <= MAX_DEG) && (y_deg() <= MAX_DEG) && (z_deg() <= MAX_DEG));
	}
	double get_k()  const noexcept {
		return k;
	}

	Monom operator+(const Monom& m) {
		Monom res;
		if (degree == m.degree) {
			res.k = k + m.k;
			res.degree = degree;
		}
		else throw domain_error("error+");
		return res;
	}
	Monom operator-(const Monom& m) {
		Monom res;
		if (degree == m.degree) {
			res.k = k - m.k;
			res.degree = degree;
		}
		else throw domain_error("error-");
		return res;
	}
	Monom operator*(const Monom& m) {
		Monom res;
		if (x_deg() + m.x_deg() <= MAX_DEG && y_deg() + m.y_deg() <= MAX_DEG && z_deg() + m.x_deg() <= MAX_DEG) {
			res.k = k * m.k;
			res.degree = degree + m.degree;
		}
		else throw domain_error("error*");
		return res;
	}
	Monom operator*(const double scal) {
		Monom res;
		if (is_deg_correct()) {
			res.k = k * scal;
			res.degree = degree;
		}
		else throw domain_error("error*sc");
		return res;
	}
	bool operator==(const Monom& other) const {
		return (degree == other.degree) && (k == other.k);
	}
	bool operator!=(const Monom& other) const {
		return !(*this == other);
	}
};

class Polynom : public mlist<Monom> {

public:
	Polynom() : mlist<Monom>() {}

	Polynom(const Polynom& other) : mlist<Monom>(other) {}

	Polynom operator+ (const Polynom& p) {
		Polynom res;
		mlist::iterator it1 = begin();
		mlist::iterator it2 = p.begin();
		Node<Monom>* lastNode = nullptr;

		while (it1 != end() && it2 != p.end()) {
			if ((*it1).degree == (*it2).degree) {
				res.insert(*it1 + *it2, lastNode);
				++it1;
				++it2;
				if (lastNode == nullptr) {
					lastNode = res.begin().get_ptr();
				}
				else {
					lastNode = lastNode->next;
				}
			}
			else if ((*it1).degree < (*it2).degree) {
				res.insert(*it1, lastNode);
				++it1;
				if (lastNode == nullptr) {
					lastNode = res.begin().get_ptr();
				}
				else {
					lastNode = lastNode->next;
				}
			}
			else {
				res.insert(*it2, lastNode);
				++it2;
				if (lastNode == nullptr) {
					lastNode = res.begin().get_ptr();
				}
				else {
					lastNode = lastNode->next;
				}
			}
		}
		while (it1 != end()) {
			res.insert(*it1, lastNode);
			++it1;
			if (lastNode == nullptr) {
				lastNode = res.begin().get_ptr();
			}
			else {
				lastNode = lastNode->next;
			}
		}

		while (it2 != p.end()) {
			res.insert(*it2, lastNode);
			++it2;
			if (lastNode == nullptr) {
				lastNode = res.begin().get_ptr();
			}
			else {
				lastNode = lastNode->next;
			}
		}
		return res;
	}
	Polynom operator* (const Polynom& p) {
		Polynom res;
		iterator it1 = this->begin();
		Node<Monom>* lastNode = nullptr;
		while (it1 != this->end())
		{
			iterator it2 = p.begin();
			Polynom temp;
			while (it2 != p.end()) {
				temp.insert((*it1) * (*it2), lastNode);
				++it2;
				if (lastNode == nullptr) {
					lastNode = res.begin().get_ptr();
				}
				else {
					lastNode = lastNode->next;
				}
			}
			++it1;
			res = res + temp;
		}
		return res;
	}
	Polynom operator* (const double scal) {
		Polynom res;
		Node<Monom>* lastNode = nullptr;
		for (iterator it = this->begin(); it != this->end(); ++it)
		{
			res.insert((*it) * scal, lastNode);
			if (lastNode == nullptr) {
				lastNode = res.begin().get_ptr();
			}
			else {
				lastNode = lastNode->next;
			}
		}
		return res;
	}
};