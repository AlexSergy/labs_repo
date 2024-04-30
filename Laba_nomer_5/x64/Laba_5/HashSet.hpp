#pragma once
#include"List.hpp"
#include<memory>
#include<sstream> // Чтобы любой тип мог преобразовываться в str.

using namespace std;

class HashSet {
private:
	
	const int size = 26;
	unique_ptr<List<string>[]> arr;
	

	// по умолчанию преобразовываем все возможные данные в str
	// затем от них берем hash
	int hashFoo(const string& value) {
		ostringstream oss;
		oss << value;
		string valueStr = oss.str();
		int hash = 0;
		for (char c : valueStr) {	hash = (hash * 31 + c) % size; }
		return hash;
	}
	
public:
	HashSet() : arr(make_unique<List<string>[]>(size)) {}

	void add(const string& value) { arr[hashFoo(value)].add(value); }

	void remove(const string& value) { arr[hashFoo(value)].del_element(value); }

	bool contains(const string& value) { return arr[hashFoo(value)].look_for(value); }

	int count() {
		int common_count = 0;
		for (int i = 0; i < size; i++) { common_count += arr[i].count(); }
		return common_count;
	}

	void clear() { for (int i = 0; i < size; i++) arr[i].clear(); }

	string* ToArray() {
		string* set_of_strings = new string[count()];
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i].count() > 0) {
				for (int n = 0; n < arr[i].count(); n++) { set_of_strings[index++] = arr[i].elementAt(n); }
			}
		}
		return set_of_strings;
	}
};