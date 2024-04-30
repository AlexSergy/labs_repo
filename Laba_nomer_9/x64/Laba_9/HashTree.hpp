#pragma once
#include"Tree.hpp"
using namespace std;

class HashTree {
private:
	int size = 26;
	Tree* arr;
	
	int hashFoo(int value) {
		int index = 0;
		while (value != 0) {
			int digit = value % 10;
			index += digit;
			value /= 10;
		}
		return index % size;
	}
public:
	HashTree() { arr = new Tree[size]; }
	~HashTree() { delete[] arr; }

	void add(int value) { arr[hashFoo(value)].add(value); }
	void remove(int value) { arr[hashFoo(value)].remove(value); }
	void clear() { for (int i = 0; i < size; i++) { arr[i].clear(); } }
	bool contains(int value) { return arr[hashFoo(value)].contains(value); }
	int count() { return [&]() { int c = 0; for (int i = 0; i < size; ++i) c += arr[i].count(); return c; }();  }

	int* ToArray() {
		int* result = new int[count()];
		int index = 0;
		for (int i = 0; i < size; i++) {
			int* treeArray = arr[i].ToArray();
			for (int j = 0; j < arr[i].count(); j++) { result[index++] = treeArray[j]; }
			delete[] treeArray;
		}
		return result;
	}
};