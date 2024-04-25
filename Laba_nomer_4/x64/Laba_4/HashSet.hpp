#pragma once
#include"List.hpp"
#include"Node.hpp"
#include"Pair.hpp"
#include<memory>
#include<sstream> // „тобы любой тип мог преобразовыватьс€ в str.


using namespace std;


template<typename K, typename V>
class HashSet {
public:
	size_t size;
	List<Pair<K, V>>*  arr;
	float load_factor;
	size_t element_count;
	
	List<Pair<K, V>>& operator[](int index) { 
		if (index > size) { throw out_of_range("ќшибка индекса."); } // Ќа вс€кий случай
		return arr[index];
	}

	HashSet(size_t initial_size = 25) : size(initial_size), load_factor(0.75), element_count(0) {
		arr = new List<Pair<K, V>>[size];
	}
	~HashSet() {
		clear();
		delete[] arr;
	}

	// по умолчанию преобразовываем все возможные данные в str
	// затем от них берем hash
	int hashFoo(const K& key) {
		ostringstream oss;
		oss << key; // полагаем, что дл€ T определен operator<<
		string valueStr = oss.str();
		int hash = 0;
		for (char c : valueStr) { hash = (hash * 31 + c); }
		return hash % size;
	}
	
	void resize() {
		size_t new_size = size * 2;
		List<Pair<K, V>>* new_arr = new List<Pair<K, V>>[new_size];
		size_t old_size = size;
		size = new_size;
		for (size_t i = 0; i < old_size; i++) {
			for (Node<Pair<K, V>>* node = arr[i].head; node != nullptr; node = node->next) {
				new_arr[hashFoo(node->data.key)].add(node->data);
			}
		}
		delete[] arr;
		arr = new_arr;
	}


	void add(const Pair<K, V>& pair) {
		size_t index = hashFoo(pair.key);
		if (!arr[index].look_for(pair)) {
			arr[index].add(pair);
			element_count++;
			if (static_cast<float>(element_count) / size >= load_factor) { resize(); }
		}
	}


	void remove(const K& key) { 
		Pair<K, V> pair(key, V());
		if (arr[hashFoo(pair.key)].look_for(pair)) {
			arr[hashFoo(pair.key)].del_element(pair);
			element_count--;
		}
	}

	bool contains(const K& key) {
		Pair<K, V> pair(key, V());
		return arr[hashFoo(pair.key)].look_for(pair);
	}

	int count() { return static_cast<int>(element_count); }

	void clear() { 
		for (size_t i = 0; i < size; i++) { arr[i].clear(); }
		element_count = 0;
	}

	Pair<K, V>* toArray() {
		Pair<K, V>* set_of_strings = new Pair<K, V>[count()];
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i].count() > 0) {
				for (int n = 0; n < arr[i].count(); n++) { set_of_strings[index++] = arr[i].elementAt(n); }
			}
		}
		return set_of_strings;
	}
};