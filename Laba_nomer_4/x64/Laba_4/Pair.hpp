#pragma once

template<typename K, typename V, typename = std::enable_if_t<std::is_arithmetic<V>::value>>
/*������������ ��������� ������ ��� �������������� ����� V, ���� ��� ����� ������ �����,
	��, � ������ ���������� ����� ����������*/
struct Pair {
	K key;
	V value;

	Pair() = default;
	Pair(const K& key, const V& value) : key(key), value(value) {}
	// ���� ��� �� ������������ ���������, ���������� ������� �� ����
	bool operator<=(const Pair<K, V>& other) const { return value <= other.value; }
	bool operator>=(const Pair<K, V>& other) const { return value >= other.value; }
	bool operator==(const Pair<K, V>& other) const { return key == other.key; }
};
