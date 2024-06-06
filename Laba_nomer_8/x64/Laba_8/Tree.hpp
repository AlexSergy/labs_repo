#pragma once
#include<algorithm>

using namespace std;


struct Node {
	int value, h = 1;
	Node* l = nullptr, * r = nullptr, * p = nullptr;
	Node(int x, Node* p = nullptr) : value(x), l(nullptr), r(nullptr), p(p), h(1) {}
};

struct Tree {
public:
	enum Order { Prefix, Infix, Postfix, LevelsUpLeft, LevelsUpRight, LevelsDownLeft, LevelsDownRight };
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

	Node* minNode(Node* node) {
		while (node->l) node = node->l;
		return node;
	}

	void delNode(Node* del, Node*& p) {
		if ((del->r == nullptr) + (del->l == nullptr) == 1) {
			Node* temp = del->l ? del->l : del->r;
			if (p) {
				if (p->l == del) p->l = temp;
				else p->r = temp;
			}
			else root = temp;
			if (temp) temp->p = p;
		}
		else if (del->l != nullptr && del->r != nullptr) {
			Node* min = minNode(del->r);
			Node* minP = min->p;
			if (minP == del) {
				min->l = del->l;
				del->l->p = min;
				min->p = p;
			}
			else {
				minP->l = min->r;
				if (min->r) min->r->p = minP;
				min->r = del->r; min->l = del->l; min->p = p;
			}
			if (del->l) del->l->p = min;
			if (del->r) del->r->p = min;
			if (p) {
				if (p->l == del) p->l = min;
				else { p->r = min; }
			}
			else root = min;
		}
		else {
			if (p) {
				if (p->l == del) p->l = nullptr;
				else p->r = nullptr;
			}
			else root = nullptr;
		}
		del->l = del->r = del->p = nullptr;
		delete del;
		size--;
	}

	void clear_(Node*& node) {
		if (node) {
			clear_(node->l);
			clear_(node->r);
			delete node;
			node = nullptr;
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

	int sizeTree(Node* n) { return n ? sizeTree(n->l) + sizeTree(n->r) + 1 : 0; }


	void rotate(Node* n, bool left) {
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
	}

	Node* findAndRotate(Node*& n, int v, bool left) {
		if (!n) return nullptr;
		if (n && n->value == v) return rotate(n, left), n;
		if (v < n->value) return findAndRotate(n->l, v, left);
		else return findAndRotate(n->r, v, left);
	}

	int height(Node* n) { return n ? max(n->l ? n->l->h : 0, n->r ? n->r->h : 0) + 1 : 0; }
	int getBalanceFactor(Node* n) { return (n->l ? n->l->h : 0) - (n->r ? n->r->h : 0); }


	void balance(Node*& n) {
		if (!n) return;
		n->h = height(n);
		int bf = getBalanceFactor(n);
		if (bf > 1) {
			if (getBalanceFactor(n->l) >= 0) rotate(n, false);
			else {
				rotate(n->l, true);
				rotate(n, false);
			}
		}
		else if (bf < -1) {
			if (getBalanceFactor(n->r) <= 0) rotate(n, true);
			else {
				rotate(n->r, false);
				rotate(n, true);
			}
		}
		balance(n->l);
		balance(n->r);
	}

	// ÍÎÂÛÅ È ÈÇÌÅÍÅÍÍÛÅ ÔÓÍÊÖÈÈ ÄËß ÂÎÑÜÌÎÉ ËÀÁÛ (ïîìå÷åíû *)
	//*
	void traverseLevel(Node* n, int*& arr, int& i, int curL, int targetL) {
		if (!n) return;
		if (curL == targetL) { arr[i++] = n->value; }
		else {
			traverseLevel(n->l, arr, i, curL + 1, targetL);
			traverseLevel(n->r, arr, i, curL + 1, targetL);
		}
	}

	void reverseIn(int h, int*& arr, int* levelCount) {
		int start = 0, end = 0;
		for (int l = 0; l < h; l++) {
			end = levelCount[l];
			reverse(arr + start, arr + end);
			start = end;
		}
	};

	void levelOrderTraversal(Node* r, int*& arr, Order o) {
		int i = 0, h = height(r);
		int* levelCount = new int[h]();
		for (int l = 0; l < h; l++) {
			traverseLevel(r, arr, i, 0, l);
			levelCount[l] = i;
		}
		if (o == LevelsDownLeft || o == LevelsUpRight) {
			reverseIn(h, arr, levelCount);
			if (o == LevelsDownLeft) reverse(arr, arr + i);
		}
		if (o == LevelsDownRight) { reverse(arr, arr + i); }
		delete[] levelCount;
	}

	int* To_Array(Order o = Infix) {
		int i = 0;
		int* arr = new int[size];
		(o >= 3) ? levelOrderTraversal(root, arr, o) : traverse(root, arr, i, o);
		return arr;
	}

	// çäåñü áûë public

	~Tree() { clear(); }
	

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
			balance(node);
		}
	}

	void remove(int v) {
		Node* parent = nullptr;
		Node*& node = findNode(v, parent);
		if (node) { delNode(node, parent); }
		balance(node);
	}

	void clear() {
		clear_(root);
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
	void Balance() { if (root) { while (abs(height(root->l) - height(root->r)) > 1) { balance(root); } } }
	int* ToArray(Order o) { return To_Array(o); }
	int* ToArray() { return To_Array(Infix); }
};