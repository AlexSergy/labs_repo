// —¿ÃŒƒ≈À‹Õ¿ﬂ —“–” “”–¿ MAP
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
			hashset.getValueForKey(key) += value;
			return;
		}
		else {
			Pair<K, V> pair(key, value);
			hashset.add(pair);
		}
	}

	bool contains(const K& key) { return hashset.contains(key); }
	int count() { return hashset.count(); }
	void remove(const K& key) { hashset.remove(key); }
	void update_population(const K& key, const V& population) { hashset.getValueForKey(key) -= population; }
	void clear() { hashset.clear; }
};