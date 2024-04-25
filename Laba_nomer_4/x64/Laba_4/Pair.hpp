#pragma once

template<typename K, typename V, typename = std::enable_if_t<std::is_arithmetic<V>::value>>
/*Ограничиваем операторы только для арифметических типов V, если для любых других типов,
	то, в случае надобности можно доработать*/
struct Pair {
	K key;
	V value;

	Pair() = default;
	Pair(const K& key, const V& value) : key(key), value(value) {}
	// если тип не поддерживает сравнение, компилятор сообщит об этом
	bool operator<=(const Pair<K, V>& other) const { return value <= other.value; }
	bool operator>=(const Pair<K, V>& other) const { return value >= other.value; }
	bool operator==(const Pair<K, V>& other) const { return key == other.key; }
};
