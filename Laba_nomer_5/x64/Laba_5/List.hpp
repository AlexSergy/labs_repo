#pragma once
// Добавлены фукнции look_for и del_element


#include<string>
#include<stdexcept>

using namespace std;


template <typename T>
class List {
public:

    struct Node {
        T data;
        Node* prev;
        Node* next;

        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    int common_count;
    Node* prevNode = nullptr;
    int prevNum = -1;

    List() : head(nullptr), tail(nullptr), common_count(0) {}

    void add(const T& data) {
        // Проверка на то, существует ли уже элемент, если да
        // то просто выходим из функции
            Node* current = head;
        while (current != nullptr) {
            if (current->data == data) {
                return; // Если элемент существует, прекращаем добавление.
            }
            current = current->next;
        }


        Node* newNode = new Node(data);
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
            Node* current = head;
            for (int i = 0; i < num - 1; i++) { current = current->next; }
            newNode->next = current->next;
            current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
        }
        common_count++;
    }

    void removeAt(int num) {
        if (num < 0 || num >= common_count) { return; }
        Node* node = head;
        for (int i = 0; i < num; i++) { node = node->next; }
        if (node == head) {
            head = head->next;
            if (head) { head->prev = nullptr; }
            else tail = nullptr;
        }
        else if (node == tail) {
            tail = node->prev;
            tail->next = nullptr;
        }
        else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        delete node;
        common_count--;
    }

    T& elementAt(int num) {
        if (num < 0 || num >= common_count) { throw out_of_range("Index out of range"); }
        if (head == nullptr) { throw logic_error("Empty list"); }

        Node* start = head;
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

        // обновляем прошлые значения
        prevNode = start;
        prevNum = num;

        return start->data;
    }

    int count() const { return common_count; }

    void clear() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        common_count = 0;
    }


    void del_element(const T value) {
        if (head == nullptr) return;
        Node* del = head;
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
        Node* cur = head;
        while (cur) {
            if (cur->data == value) { return true; }
            cur = cur->next;
        }
        return false;
    }
};



