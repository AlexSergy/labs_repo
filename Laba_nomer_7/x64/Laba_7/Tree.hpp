#pragma once
#include<algorithm>

using namespace std;


struct Node {
	int value;
	Node* l, * r, * p;
	Node(int x, Node* p = nullptr) : value(x), l(nullptr), r(nullptr), p(p) {}
};

struct Tree {
public:
	enum Order { Prefix, Infix, Postfix };
	int size = 0;
	Node* root = nullptr;

	Node*& findNode(int v, Node*& p) {
		p = nullptr;
		Node** cur = &root;
		while (*cur && (*cur)->value != v) {
			p = *cur;
			cur = v < (*cur)->value ? &(*cur)->l : &(*cur)->r;
		}
		return *cur;
	}

	Node* minNode(Node*& node) {
		while (node->l) node = node->l;
		return node;
	}

	void delNode(Node*& del, Node*& p) {
		if (!del->l + !del->r == 1) {
			Node* temp = del->l ? del->l : del->r;
			if (p) {
				if (p->l = del) p->l = temp;
				else p->r = temp;
			}
			else root = temp;
			if (temp) temp->p = p;
		}
		else if (del->l && del->r) {
			Node* min = minNode(del->r);
			Node* minParent = min->p;
			if (minParent != del) {
				minParent->l = min->r;
				if (min->r) min->r->p = minParent;
			}
			else {
				minParent->r = min->r;
				if (min->r) min->r->p = min->p;
			}
			min->l = del->l;
			min->r = del->r;
			if (del->l) del->l->p = min;
			if (del->r) del->r->p = min;
			if (p) {
				if (p->l == del) p->l = min;
				else p->r = min;
			}
			else root = min;
			min->p = p;
		}
		else {
			if (p) {
				if (p->l == del) p->l = nullptr;
				else p->r = nullptr;
			}
			else root = nullptr;
		}
		delete del;
		size--;
	}

	void clear(Node*& node) {
		if (node) { 
			clear(node->l);
			clear(node->r);
			delete node;
		}
	}

	void traverse(Node*& n, int*& arr, int& i, Order o) {
		if (!n) return;
		if (o == Prefix) { arr[i++] = n->value; }
		traverse(n->l, arr, i, o);
		if (o == Infix) { arr[i++] = n->value; }
		traverse(n->r, arr, i, o);
		if (o == Postfix) { arr[i++] = n->value; }
	}

	void rotate(Node*& n, bool left) {
		if (!n) return;
		Node* x = left ? n->r : n->l;
		if (!x) return;
		x->p = n->p;
		if (n->p) {
			if (n->p->l == n) n->p->l = x;
			else if (n->p->r == n) n->p->r = x;
		}
		if (left) {
			n->r = x->l;
			if (x->l) x->l->p = n;
			x->l = n;
		}
		else {
			n->l = x->r;
			if (x->r) x->r->p = n;
			x->r = n;
		}
		n->p = x;
		if (!x->p) root = x;
		n = x;
	}

	Node* findAndRotate(Node*& n, int v, bool left) {
		if (!n) return nullptr;
		if (n && n->value == v) return rotate(n, left), n;
		if (v < n->value) return findAndRotate(n->l, v, left);
		else return findAndRotate(n->r, v, left);
	}

	int height(Node*& n) { return n ? 1 + max(height(n->l), height(n->r)) : 0; }

	Node* balance(Node*& n) {
		if (!n) return nullptr;
		int l = 1 + height(n->l);
		int r = 1 + height(n->r);
		if (abs(l - r) > 1) rotate(n, l > r);
		n->l = balance(n->l);
		n->r = balance(n->r);
		return n;
	}

	int* ToArray(Order o = Infix) {
		int i = 0;
		int* arr = new int[size];
		traverse(root, arr, i, o);
		return arr;
	}

	~Tree() { clear(root); }

	void add(int v) {
		Node* parent = nullptr;
		Node*& node = findNode(v, parent);
		if (!node) {
			node = new Node(v);
			node->p = parent;
			if (parent) {
				if (v < parent->value) parent->l = node;
				else parent->r = node;
			}
			else { root = node; }
			size++;
		}
	}

	void remove(int v) {
		Node* parent = nullptr;
		Node*& node = findNode(v, parent);
		if (node) { delNode(node, parent); }
	}

	void clear() {
		clear(root);
		root = nullptr;
		size = 0;
	}

	bool contains(int v) {
		Node* parent = nullptr;
		return findNode(v, parent) != nullptr;
	}

	int count() { return size; }

	void ToLeft(int v) { findAndRotate(root, v, true); }
	void ToRight(int v) { findAndRotate(root, v, false); }
	void Balance() { root = balance(root); }
	int* ToArray(Order o) { return ToArray(o); }
	int* ToArray() { return ToArray(Infix); }
};