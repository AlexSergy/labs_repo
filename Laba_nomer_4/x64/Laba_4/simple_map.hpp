// САМОДЕЛЬНАЯ СТРУКТУРА MAP
#pragma once
#include"HashSet.hpp"
#include<stdexcept>

using namespace std;

template<typename K, typename V>
class simple_map {
public:
	HashSet<K, V> hashset;
	

	void insert(const K& key, const V& value) {
		if (hashset.contains(key)) {
			V& newValue = getValue(key);
			newValue += value;
			return;
		}
		else {
			Pair<K, V> pair(key, value);
			hashset.add(pair);
		}
	}

	bool contains(const K& key) {
		return hashset.contains(key);
	}
	int count() { return hashset.count(); }

	// Я забыл про то, что у меня была эта функция, прошу прощения:)
	void remove(const K& key) { hashset.remove(key); }
	/*
	void merge(Pair<K, V>* arr, int left, int middle, int right) {
		int n1 = middle - left + 1;
		int n2 = right - middle;

		Pair<K, V>* L = new Pair<K, V>[n1];
		Pair<K, V>* R = new Pair<K, V>[n2];

		// копируем все в временные массивы
		for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; }
		for (int j = 0; j < n2; j++) { R[j] = arr[middle + 1 + j]; }

		// Сливаем временные массивы обратно
		int i = 0, j = 0, k = 0;
		while (i < n1 && j < n2) {
			if (L[i].value >= R[j].value) {
				arr[k] = L[i];
				i++;
			}
			else { 
				arr[k] = R[j];
				j++;
			}
			k++;
		}

		// Если остались элементы, копируем оставшееся
		while (i < n1) {
			arr[k] = L[i];
			i++;
			k++;
		}
		while (j < n2) {
			arr[k] = R[j];
			j++;
			k++;
		}

		delete[] L;
		delete[] R;
	}



	void mergeSort(Pair<K, V>* arr, int left, int right) {
		if (left < right) {
			int middle = left + (right - left) / 2;
			mergeSort(arr, left, middle);
			mergeSort(arr, middle + 1, right);
			merge(arr, left, middle, right);
		}
	}

	*/
	
	// Для четвертой лабы. Уменьшение населения некоторого региона.
	void remove_population(const K& key, const V& population) { 
		Pair<K, V> pair(key, V());
		hashset[hashset.hashFoo(key)].look_for_node(pair)->data.value -= population;
	}

	V& getValue(const K& key) { // Возвращает значения по ключу
		Pair<K, V> pair(key, V());
		if (hashset[hashset.hashFoo(key)].look_for_node(pair)) { return hashset[hashset.hashFoo(key)].look_for_node(pair)->data.value; }
		else { throw out_of_range("Ключ не найден"); }
	}

	void clear() { hashset.clear; }
};