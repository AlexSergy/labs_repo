#pragma once

struct Node {
	int value;
	Node* left, * right, * parent;
	Node(int v, Node* parent = nullptr) : value(v), left(nullptr), right(nullptr), parent(parent) {};
};

class Tree {
private:
	enum Order { Prefix, Infix, Postfix };
	Node* root = nullptr;
	int size = 0;

	Node*& findNode(int v, Node*& parent) {
		parent = nullptr;
		Node** cur = &root;
		while (*cur && (*cur)->value != v) {
			parent = *cur;
			cur = v < (*cur)->value ? &(*cur)->left : &(*cur)->right;
		}
		return *cur;
	}

	Node* minNode(Node* node) {
		while (node->left) node = node->left;
		return node;
	}

	void delNode(Node* del, Node* parent) {
		if (!del->left + !del->right == 1) {
			Node* temp = !del->left ? del->right : del->left;
			if (parent) {
				if (parent->left == del) parent->left = temp;
				else parent->right = temp;
			}
			else { root = temp; }
		}
		else if (del->left && del->right) {
			Node* min = minNode(del->right);
			Node* minParent = min->parent;
			if (minParent != del) {
				minParent->left = min->right;
				if (min->right) min->right->parent = minParent;
			}
			else {
				minParent->right = min->right;
				if (min->right) min->right->parent = min->parent;
			}
			min->left = del->left;
			min->right = del->right;
			if (del->left) del->left->parent = min;
			if (del->right) del->right->parent = min;
			if (parent) {
				if (parent->left == del) parent->left = min;
				else parent->right = min;
			}
			else { root = min; }
			min->parent = parent;
		}
		else {
			if (parent) {
				if (parent->left == del) { parent->left = nullptr; }
				else parent->right = nullptr;
			}
			else root = nullptr;
		}
		delete del;
		size--;
	}

	void clear(Node* node) {
		if (node) {
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	void traverse(Node*& n, int*& arr, int& i, Order o) {
		if (!n) return;
		if (o == Prefix) { arr[i++] = n->value; }
		traverse(n->left, arr, i, o);
		if (o == Infix) { arr[i++] = n->value; }
		traverse(n->right, arr, i, o);
		if (o == Postfix) { arr[i++] = n->value; }
	}

	int* To_Array(Order o = Infix) {
		int i = 0;
		int* arr = new int[size];
		traverse(root, arr, i, o);
		return arr;
	}

public:
	~Tree() { clear(root); }

	void add(int v) {
		Node* parent = nullptr;
		Node*& node = findNode(v, parent);
		if (!node) {
			node = new Node(v, parent);
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

	int* ToArray() { return To_Array(Infix); }
};