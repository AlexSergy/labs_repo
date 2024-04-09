#ifndef LIST_HPP
#define LIST_HPP

#include<string>
#include<stdexcept>

using namespace std;

struct City {
    string name;
    string region;
    int population;
};

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

    void add(const T& data) {
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


        Node* start = head;
        int distance_head = num;
        int distance_tail = common_count - num - 1;
        int distance_prev = prevNode ? abs(prevNum - num) : INT_MAX; // индекса нет => инт макс
        // если нет prevNode, то любой другой путь быстрее, чем distance_prev

        // ищем ближайшую точку
        if (distance_prev < distance_head && distance_prev < distance_tail) {
            start = prevNode;
            num = distance_prev;
            if (prevNum > num) { for (int i = prevNum; i > num; i--) { start = start->prev; } }
            else { for (int i = prevNum; i < num; i++) { start = start->next; } }
        }
        else if (distance_tail < distance_head) {
            start = tail;
            for (int i = common_count - 1; i > num; i--) { start = start->prev; } 
        }
        else { for (int i = 0; i < num; i++) { start = start->next; } }

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

    void removeCitiesByRegion(string name) {
        Node* cur = head;
        Node* prev = nullptr;

        while (cur != nullptr) {
            if (cur->data.region == name) {
                Node* del = cur;
                if (prev != nullptr) { prev->next = cur->next; }
                else {
                    head = cur->next;
                    if (head) { head->prev = nullptr; }
                } // если удаляем первый элемент
                if (cur->next == nullptr) { tail = prev; }
                else { cur->next->prev = prev; }
                cur = cur->next;
                delete del;
                common_count--;
            }
            else {
                prev = cur;
                cur = cur->next;
            }
        }
    }
};



#endif // LIST_HPP