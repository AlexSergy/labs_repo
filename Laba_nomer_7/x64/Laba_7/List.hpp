#pragma once
#include<string>
#include<stdexcept>

template <typename T>
class List {
public:

    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };


    Node* head;
    Node* tail;
    int common_count;
    Node* prevNode = nullptr;
    int prevNum = -1;

    List() : head(nullptr), tail(nullptr), common_count(0) {}

    Node* go_to(int num) {
        if (!head) { throw out_of_range("Empty list"); }
        if (num == -1) { return tail; }
        if (common_count != 0) num %= common_count;
        Node* start = head;
        int steps = num;
        int distance_flag = flag ? num - num_flag : INT_MAX;

        if (distance_flag >= 0 && distance_flag < steps) {
            start = flag;
            steps = distance_flag;
        }
        while (steps-- > 0) { start = start->next; }
        flag = start;
        num_flag = num;
        return start;
    }

    void remove(Node* del) {
        head = head == del ? head->next; head;
        tail = tail == del ? tail->prev; tail;
        prevNode = prevNode == del ? prevNode->prev ? prevNode->prev : prevNode->next ? prevNode->next : nullptr : nullptr : prevNode;
        prevNum = temp == prevNode ? prevNum : temp->next == prevNode ? --prevNum : ++prevNum;
        if (del->next) { del->next->prev = del->prev ? del->prev : nullptr; }
        if (del->prev) { del->prev->next = del->next ? del->next : nullptr; }
        Node* temp = prevNode;
        delete del;
        common_count--;
    }

    bool look_for(const T value) {
        if (!head) return false;
        Node<T>* cur = head;
        while (cur) {
            if (cur->data == value) { return true; }
            cur = cur->next;
        }
        return false;
    }

    void add(int value) {
        Node* newNode = Node(value);
        if (!head) { head = newNode; }
        else { tail->next = newNode; newNode->prev = tail; }
        tail = newNode;
        common_count++;
    }

    void insert(int num, const T& data) {
        if (num < 0 || num > common_count) { throw; }
        Node* newNode = new Node(data);
        if (num == 0) {
            newNode->next = head;
            if (head != nullptr) { head->prev = newNode; }
            else { tail = newNode; }
            head = newNode;
        }
        else if (num == common_count) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            Node* beforeIns = go_to(num - 1);
            newNode->next = beforeIns->next;
            beforeIns->next = newNode;
            newNode->prev = beforeIns;
            newNode->next->prev = newNode;
            prevNode = beforeIns;
            prevNum = num - 1; // В случае, если планируем много раз вставлять элементы
        }
        common_count++;
    }


    void removeAt(int num) {
        if (num < 0 || num >= common_count) { return; }
        Node* del = go_to(num);
        prevNum = prevNode ? prevNum > num ? prevNum-- : prevNum : -1;
        if (num == 0) { head = head->next; }
        if (num == common_count - 1) { tail = tail->prev; }
        remove(del);
    }

    T& elementAt(int num) {
        if (num < 0 || num >= common_count) { throw; }
        Node* element = go_to(num);
        prevNode = element;
        prevNum = num;
        return element->data;
    }

    int count() const { return common_count; }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        common_count = 0;
    }

};