#pragma once


#include<string>
#include<stdexcept>
#include"Node.hpp"

using namespace std;



template <typename T>
class List {
public:
    Node<T>* head;
    Node<T>* tail;
    int common_count;
    Node<T>* prevNode = nullptr;
    int prevNum = -1;

    List() : head(nullptr), tail(nullptr), common_count(0) {}

    // Блок кода с дополнительными функциями
    // --------------------------------------------------------------------------------

    Node<T>* go_to(int num) {
        Node<T>* start = head;
        int steps = num;
        int distance_head = num;
        int distance_tail = common_count - num - 1;
        int distance_prev = prevNode ? abs(prevNum - num) : INT_MAX; // индекса нет => инт макс
        // если нет prevNode, то любой другой путь быстрее, чем distance_prev

        // ищем ближайшую точку и кол-во шагов до точки
        if (distance_head <= distance_tail && distance_head <= distance_prev) {
            start = head;
            steps = num;
        }
        else if (distance_tail < distance_head && distance_tail < distance_prev) {
            start = tail;
            steps = distance_tail;
        }
        else {
            start = prevNode;
            steps = prevNum < num ? num - prevNum : prevNum - num;
        }

        if (prevNum > num) { while (steps-- > 0) { start = start->prev; } }
        else { while (steps-- > 0) { start = start->next; } }

        return start;
    }

    void remove(Node<T>* del) {
        if (del->prev) del->prev->next = del->next;
        if (del->next) del->next->prev = del->prev;
        prevNode = prevNode == del && prevNode->next ? prevNode->next : nullptr;
        delete del;
        common_count--;
        if (common_count == 0) {
            tail = nullptr;
            head = nullptr;
        }
    }

    // Основные функции по List
    // --------------------------------------------------------------------------------------

    void add(const T& data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        common_count++;
    }

    void insert(int num, const T& data) {
        if (num < 0 || num > common_count) { throw out_of_range("Out of range!"); }
        Node<T>* newNode = new Node<T>(data);
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
            Node<T>* beforeIns = go_to(num - 1);
            newNode->next = beforeIns->next;
            beforeIns->next = newNode;
            newNode->prev = beforeIns;
            newNode->next->prev = newNode;
            prevNode = beforeIns;
            prevNum = num-1; // В случае, если планируем много раз вставлять элементы
        }
        common_count++;
    }


    void removeAt(int num) {
        if (num < 0 || num >= common_count) { return; }
        Node<T>* del = go_to(num);
        prevNum = prevNode ? prevNum > num ? prevNum-- : prevNum : -1;
        if (num == 0) { head = head->next; }
        if (num == common_count - 1) { tail = tail->prev; }
        remove(del);
    }

    T& elementAt(int num) {
        if (num < 0 || num >= common_count) { throw out_of_range("Index out of range"); }
        Node<T>* element = go_to(num);
        prevNode = element;
        prevNum = num;
        return element->data;
    }
            
    int count() const { return common_count; }

    void clear() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        common_count = 0;
    }

    // Блок кода для хэш-таблицы, которая для simple_map
    // ---------------------------------------------------------------------------------------


    void del_element(const T value) {
        if (head == nullptr) return;
        Node<T>* del = head;
        while (del) {
            if (del->data == value) {
                if (del == head) {
                    head = head->next;
                    if (del->next) {
                        del->next->prev = nullptr;
                        del->next = nullptr;
                    }
                }
                else {
                    del->prev->next = del->next;
                    if (del->next)  del->next->prev = del->prev;
                }
                delete del;
                common_count--;
                break;
            }
            del = del->next;
        }
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

    Node<T>* look_for_node(const T value) {
        Node<T>* cur = head;
        while (cur) {
            if (cur->data == value) { return cur; }
            cur = cur->next;
        }
        return nullptr;
    }
    
};



