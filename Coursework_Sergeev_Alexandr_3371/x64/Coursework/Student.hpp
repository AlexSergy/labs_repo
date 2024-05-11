#pragma once
#include"Students_data.hpp"

struct Student {
	Pair data;
	Student* prev = nullptr;
	Student* next = nullptr;

	Student(const string& key, const string& groupNumber, const Array<5>& arr, double scholarship, const string& phoneNumber) : data(key, groupNumber, arr, scholarship, phoneNumber), prev(nullptr), next(nullptr) {}
	//Just in case ↑
	Student(const Pair& value) : data(value), prev(nullptr), next(nullptr) {}
	Student() : data(), prev(nullptr), next(nullptr) {}


	Student& operator=(const Student& other) {
		data.key = other.data.key;
		data.value.arr = other.data.value.arr;
		data.value.groupNumber = other.data.value.groupNumber;
		data.value.scholarship = other.data.value.scholarship;
		data.value.phoneNumber = other.data.value.phoneNumber;
		return *this;
	}
	bool operator==(const Student& other) const { return data == other.data; } // сравнивает телефоны для поиска
	void clear() {
		prev = next = nullptr;
		data = Pair();
	}
};