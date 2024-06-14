#pragma once
#include"List.hpp"
#include<memory>
#include<sstream> 

using namespace std;

class HashSet {
private:
	
	const int size = 26;
	unique_ptr<List<string>[]> arr;
	
	int hash(const string& value) {
		ostringstream oss;
		oss << value;
		string valueStr = oss.str();
		unsigned int h = 0;
		for (char c : valueStr) { h = (h * 31 + c) % size; }
		return h;
	}
	
public:
	HashSet() : arr(make_unique<List<string>[]>(size)) {}

	void add(const string& value) { arr[hash(value)].add(value); }

	void remove(const string& value) { arr[hash(value)].remove(value); }

	bool contains(const string& value) { return arr[hash(value)].contains(value); }

	int count() {
		int common_count = 0;
		for (int i = 0; i < size; i++) { common_count += arr[i].size(); }
		return common_count;
	}

	void clear() { for (int i = 0; i < size; i++) { arr[i].clear(); } }

	string* ToArray() {
		int cnt = count();
		string* result = new string[cnt];
		int idx = 0;
		if (cnt != 0) {
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < arr[i].size(); j++)
					result[idx++] = arr[i].element(j);
			}
		}
		else { return nullptr; }
		return result;
	}
};