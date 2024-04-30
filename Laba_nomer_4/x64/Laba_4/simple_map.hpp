// —јћќƒ≈Ћ№Ќјя —“–” “”–ј MAP
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

	// я забыл про то, что у мен€ была эта функци€, прошу прощени€:)
	void remove(const K& key) { hashset.remove(key); }
	
	
	// ƒл€ четвертой лабы. ”меньшение населени€ некоторого региона.
	void remove_population(const K& key, const V& population) {
		V& value = hashset.getValueForKey(key);
		value -= population;
	}

	V& getValue(const K& key) { return hashset.getValueForKey(key); }

	void clear() { hashset.clear; }
};