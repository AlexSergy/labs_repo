#pragma once
#include"List.hpp"
#include<memory>
#include<sstream> // Чтобы любой тип мог преобразовываться в str.

using namespace std;

template<typename S>
class HashSet {
private:
	
	const int size = 26;
	unique_ptr<List<S>[]> arr;
	

	// по умолчанию преобразовываем все возможные данные в str
	// затем от них берем hash
	int hashFoo(const S& value) {
		ostringstream oss;
		oss << value; // пологаем, что для T определен operator<<
		string valueStr = oss.str();
		int hash = 0;
		for (char c : valueStr) {	hash = (hash * 31 + c) % size; }
		return hash;
	}
	
public:
	HashSet() : arr(make_unique<List<S>[]>(size)) {}

	void add(const S& value) { arr[hashFoo(value)].add(value); }

	void remove(const S& value) { arr[hashFoo(value)].del_element(value); }

	bool contains(const S& value) { return arr[hashFoo(value)].look_for(value); }

	int count() {
		int common_count = 0;
		for (int i = 0; i < size; i++) { common_count += arr[i].count(); }
		return common_count;
	}

	void clear() { for (int i = 0; i < size; i++) arr[i].clear(); }

	S* toArray() {
		S* set_of_strings = new S[count()];
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i].count() > 0) {
				for (int n = 0; n < arr[i].count(); n++) { set_of_strings[index++] = arr[i].elementAt(n); }
			}
		}
		return set_of_strings;
	}
};