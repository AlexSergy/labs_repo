#pragma once

template <typename T>
struct Node {
	T data;
	Node* prev;
	Node* next;

	Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};