#pragma once
#include <iostream>

template<class T>
class Node {
public:
	T data;
	Node<T>* next;
};

template<class T>
class List {
public:
	Node<T>* head;
	Node<T>* last;
	int n;

	List() {
		head = NULL;
		last = NULL;
		n = 0;
	}

	~List() {
		if (head != NULL) {
			Node<T>* current = head;
			while (current != last) {
				current = current->next;
				delete head;
				head = current;
			}
			delete head;
			n = 0;
		}
	}

	List(const List& list) {
		head = NULL;
		last = NULL;
		Node<T>* current = list.head;
		for (int i = 0; i < list.n; i++) {
			push_back(current->data);
			current = current->next;
		}
		n = list.n;
	}

	T GetFirst() { return head->data; }

	T GetLast() { return last->data; }

	void push_front(T d) {
		Node<T>* nn = new Node<T>;
		nn->data = d;
		nn->next = head;
		head = nn;
		n++;
		if (last == NULL) last = head;
		else last->next = head;
	}

	void push_back(T d) {
		if (last == NULL) push_front(d);
		else {
			Node<T>* nn = new Node<T>;
			nn->data = d;
			nn->next = NULL;
			last->next = nn;
			last = nn;
			last->next = head;
			n++;
		}
	}

	void pop_front() {
		if ((*this).IsEmpty()) throw std::logic_error("List is empty");
		Node<T>* tmp = head;
		head = tmp->next;
		delete tmp;
		last->next = head;
		n--;
		if (head == NULL) last = NULL;
	}

	void pop_back() {
		if ((*this).IsEmpty()) throw std::logic_error("List is empty");
		if (head != last) {
			Node<T>* current = head;
			while (current->next != last)
				current = current->next;
			std::swap(current, last);
			delete current;
			last->next = head;
			n--;
		}
		else pop_front();
	}

	void PrintList() {
		Node<T>* current = head;
		for (int i = 0; i < n; i++) {
			std::cout << current->data << ' ';
			current = current->next;
		}
	}

	bool IsEmpty() {
		return head == NULL;
	}
};

class Polinom;
class Monom {
public:
	int deg;
	int km;
	Monom(int k = 0, int d = -1);
	Monom(const Monom& m);
	int dx();
	int dy();
	int dz();
	bool RightDeg(Monom m);
	Monom operator+(Monom m);
	Monom operator*(Monom m);
	Polinom operator*(Polinom p);
	bool operator==(Monom m) const;
	bool operator!=(Monom m) const;
	friend std::ostream& operator<<(std::ostream& os, const Monom& m);
};

class Polinom : public List<Monom> {
public:
	Polinom();
	Polinom(const Polinom& p);
	Polinom operator+(const Polinom& p);
	Polinom operator*(const Polinom& p);
	Polinom operator=(const Polinom& p);
	bool operator==(Polinom p) const;
	friend std::ostream& operator<<(std::ostream& os, const Polinom& p);
};


std::ostream& operator<<(std::ostream& os, Monom& m)
{
	os << m.km << ' '<<m.deg;
	return os;
}

std::ostream& operator<<(std::ostream& os, const Polinom& p)
{
	Node<Monom>* c = p.head;
	for (int i = 0; i < p.n; i++) {
		os << "+" << c->data;
		c = c->next;
	}
	return os;
}

Monom::Monom(int k, int d) { deg = d; km = k; }
Monom::Monom(const Monom& m) { deg = m.deg; km = m.km; }
int Monom::dx() { return deg / 100; }
int Monom::dy() { return (deg / 10) % 10; }
int Monom::dz() { return deg % 10; }

bool Monom::RightDeg(Monom m) {
	if ((((*this).dx() + m.dx()) <= 9) && (((*this).dy() + m.dy()) <= 9) && (((*this).dz() + m.dz()) <= 9))
		return 1;
	else return 0;
}

Monom Monom::operator+(Monom m) {
	if (deg != m.deg) throw std::logic_error("Different degrees");
	else {
		Monom nm(km + m.km, deg);
		return nm;
	}
}

Monom Monom::operator*(Monom m) {
	if ((*this).RightDeg(m) == 0) throw std::logic_error("Too much degrees");
	Monom nm(km * m.km, deg + m.deg);
	return nm;
}

Polinom Monom::operator*(Polinom p) {
	Polinom np;
	Node<Monom>* c = p.head->next;
	for (int i = 1; i < p.n; i++) {
		np.push_back((*this) * (c->data));
		c = c->next;
	}
	return np;
}

bool Monom::operator==(Monom m)  const {
	if (km == m.km && deg == m.deg) return 1;
	else return 0;
}

bool Monom::operator!=(Monom m)  const {
	return !((*this) == m);
}

Polinom::Polinom() {
	Monom m(0, -1);
	(*this).push_back(m);
}

Polinom::Polinom(const Polinom& p) : List<Monom>(p) {}

Polinom Polinom::operator+(const Polinom& p) {
	Polinom np;
	if (n == 1) return p;
	if (p.n == 1) return *this;
	Node<Monom>* c1 = head->next;
	Node<Monom>* c2 = p.head->next;
	int k1 = 1, k2 = 1;
	while ((k1 < n) && (k2 < p.n))
		if (c1->data.deg < c2->data.deg) {
			np.push_back(c1->data);
			c1 = c1->next;
			k1++;
		}
		else {
			if (c1->data.deg > c2->data.deg) {
				np.push_back(c2->data);
				c2 = c2->next;
				k2++;
			}
			if (c1->data.deg == c2->data.deg) {
				if ((c1->data + c2->data).km != 0) np.push_back(c1->data + c2->data);
				c1 = c1->next;
				c2 = c2->next;
				k1++;
				k2++;
			}
		}
	if (c1 == head)
		while (c2 != p.head) {
			np.push_back(c2->data);
			c2 = c2->next;
		}
	if (c2 == p.head)
		while (c1 != head) {
			np.push_back(c1->data);
			c1 = c1->next;
		}
	return np;
}

Polinom Polinom::operator*(const Polinom& p) {
	Polinom np;
	Node<Monom>* c = p.head->next;
	for (int i = 0; i < p.n - 1; i++) {
		np = np + (c->data) * (*this);
		c = c->next;
	}
	return np;
}

Polinom Polinom::operator=(const Polinom& p) {
	Polinom np(p);
	std::swap(this->head, np.head);
	std::swap(this->last, np.last);
	std::swap(this->n, np.n);
	return *this;
}

bool Polinom::operator==(Polinom p) const {
	Node<Monom>* c1 = head;
	Node<Monom>* c2 = p.head;
	while ((c1 != last) && (c2 != p.last)) {
		if (c1->data != c2->data) return 0;
		c1 = c1->next;
		c2 = c2->next;
	}
	if ((c1 != last) || (c2 != p.last)) return 0;
	return 1;
}