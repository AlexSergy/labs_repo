#pragma once
#include <stdexcept>
#include <algorithm>

using namespace std;

template <typename T>
class List {
public:
    struct Node {
        T data;
        Node* next = nullptr;
        Node* prev = nullptr;
        Node(T value) : data(value) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int count = 0;
    Node* prevNode = nullptr;
    int prevIndex = -1;

    Node* Forward(Node* start, int steps) {
        if (!start) return nullptr;
        while (steps-- && start->next) start = start->next;
        return start;
    }

    Node* Backward(Node* start, int steps) {
        if (!start) return nullptr;
        while (steps-- && start->prev) start = start->prev;
        return start;
    }

    Node* goToIndex(int index) {
        if (!head) return nullptr;

        Node* start = head;
        int steps = 0;

        int forwardDistance = index;
        int backwardDistance = count - index - 1;
        int prevDistance = (prevNode) ? abs(prevIndex - index) : INT_MAX;

        if (forwardDistance <= min(backwardDistance, prevDistance)) {
            start = head;
            steps = forwardDistance;
            prevNode = Forward(start, steps);
        }
        else if (backwardDistance < min(forwardDistance, prevDistance)) {
            start = tail;
            steps = backwardDistance;
            prevNode = Backward(start, steps);
        }
        else {
            start = prevNode;
            steps = abs(prevIndex - index);
            prevNode = Forward(start, steps);
        }
        prevIndex = index;
        return prevNode;
    }

//public:
    void add(T value) {
        Node* newNode = new Node(value);

        if (!head || !tail) {head = tail = newNode;}
        else {
            Node* current = head;
            while (current) {
                if (current->data == value) return; // Value already exists, return
                current = current->next;
            }
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void remove(const T& value) {
        Node* current = head;
        int index = 0;
        while (current && current->data != value) {
            current = current->next;
            index++;
        }
        if (!current) return;
        if (current->next) current->next->prev = current->prev;
        if (current->prev) current->prev->next = current->next;
        head = (current == head) ? head->next : head;
        if (head) head->prev = nullptr;
        tail = (current == tail) ? tail->prev : tail;
        if (tail) tail->next = nullptr;
        if (current == prevNode) {
            prevNode = (current->next) ? current->next : current->prev;
            prevIndex = (prevNode == current->next) ? index : --index;
        }
        else { prevIndex = (index < prevIndex) ? --prevIndex : prevIndex;}
        delete current;
        count--;
        if (count == 0) {
            head = tail = prevNode = nullptr;
            prevIndex = -1;
        }
    }

    T& element(int index) {
        Node* node = goToIndex(index);
        prevNode = node;
        prevIndex = index;
        if (node) return node->data;
        else throw std::out_of_range("Invalid index");
    }

    bool contains(const T& value) {
        Node* current = head;
        while (current) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    int size() { return count; }

    void clear() {
        Node* temp = head;
        while (head) {
            temp = head->next;
            delete head;
            head = temp;
        }
        head = tail = prevNode = nullptr;
        count = 0;
        prevIndex = -1;
    }
};