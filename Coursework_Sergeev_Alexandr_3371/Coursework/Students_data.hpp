#pragma once
#include"Info.hpp"
using namespace std;

//template<typename K, typename V,typename = std::enable_if_t<std::is_arithmetic<V>::value>> 
/*Ограничиваем операторы только для арифметических типов V, если для любых других типов,
	то, в случае надобности можно доработать*/
struct Pair {
	string key;
	Info value;

	Pair() : key(), value() {}
	Pair(const string& key, const Info& value) : key(key), value(value) {}
	Pair(const string& group, const string& number) : key(""), value(group, number) {}
	Pair(const string& key, const string& groupNumber, const Array<5>& arr, double scholarship, const string& phoneNumber) : key(key), value(groupNumber, arr, scholarship, phoneNumber) {}
	// Also just in case ↑
	Pair& operator=(const Pair& other) {
		key = other.key;
		value = other.value;
		return *this;
	}
	bool operator==(const Pair& other) const { return value.phoneNumber == other.value.phoneNumber; } // сравнивает телефоны для поиска
	bool operator<(const Pair& other) const { return key < other.key; } // оператор < будет сравнивает ФИО по алфавитному порядку
	// Возможно сравнение здесь и нужно
	// если тип не поддерживает сравнение, компилятор сообщит об этом
};