#pragma once
#include<stdexcept>
#include"Student.hpp"
using namespace std;


class Group {
public:
    string groupNumber;
    Student* head;
    Student* tail;
    int common_count = 0;
    Student* prevNode = nullptr;
    int prevNum = -1;


    Group& operator=(const Group& other) {
        if (this == &other) { return *this; }
        clear();
        groupNumber = other.groupNumber;
        common_count = other.common_count;
        prevNum = other.prevNum;
        Student* current = other.head;
        while (current != nullptr) {
            add(*current); 
            current = current->next;
        }
        prevNode = other.prevNode;
        prevNum = other.prevNum;
        return *this;
    }
    

    Group(string gN) : groupNumber(gN), head(nullptr), tail(nullptr), common_count(0) {}
    Group() : groupNumber("0"), head(nullptr), tail(nullptr), common_count(0) {}
    

    // Блок кода с дополнительными функциями
    // --------------------------------------------------------------------------------

    Student* forward(Student* start, int steps) {
        if (!start) return nullptr;
        while (steps-- && start->next) start = start->next;
        return start;
    }

    Student* backward(Student* start, int steps) {
        if (!start) return nullptr;
        while (steps-- && start->prev) start = start->prev;
        return start;
    }

    Student* go_to(int index) {
        if (!head) return nullptr;  
        Student* start = head; 
        int steps = 0;
        int forward_distance = index;
        int backward_distance = common_count - index - 1;
        int prev_distance = (prevNode) ? abs(prevNum - index) : INT_MAX; 

        if (forward_distance <= min(backward_distance, prev_distance)) {
            start = head;
            steps = forward_distance;
            prevNode = forward(start, steps);
        }
        else if (backward_distance < min(forward_distance, prev_distance)) {
            start = tail;  
            steps = backward_distance;
            prevNode = backward(start, steps);
        }
        else {
            start = prevNode;
            steps = abs(prevNum - index);
            prevNode = forward(start, steps);
        }
        prevNum = index;
        return prevNode;
    }

    void updateGroup(string newGroup) {
        Student* cur = head;
        while (cur) {
            cur->data.value.groupNumber = newGroup;
            cur = cur->next;
        }
    }

    void remove(Student* del) {
        Student* cur = head; int x = 0;
        while (cur && !(cur->data == del->data)) {
            cur = cur->next;
            x++;
        }
        if (!cur) return;
        if (cur->next) cur->next->prev = cur->prev;
        if (cur->prev) cur->prev->next = cur->next;
        head = cur == head ? head->next : head;
        if (head) head->prev = nullptr;
        if (cur == prevNode) {
            prevNode = (cur->next) ? cur->next : cur->prev;
            prevNum = (prevNode == cur->next) ? x : --x;
        }
        else { prevNum = (x < prevNum) ? --prevNum : prevNum; }
        delete cur;
        common_count--;
        if (common_count == 0) { zeroing(); }
    }

    // Основные функции по List
    // --------------------------------------------------------------------------------------

    void add(const Student& student) {
        Student* newNode = new Student(student);
        Student* cur = head;
        if (head == nullptr) {
            groupNumber = newNode->data.value.groupNumber;
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

    void insert(int num, const Student& data) {
        if (num < 0 || num > common_count) { throw out_of_range("Out of range!"); }
        Student* newNode = new Student(data);
        if (num == 0) {
            newNode->next = head;
            if (head != nullptr) { head->prev = newNode; }
            else { tail = newNode; }
            head = newNode;
            groupNumber = newNode->data.value.groupNumber;
        }
        else if (num == common_count) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        else {
            Student* beforeIns = go_to(num - 1);
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
        Student* del = go_to(num);
        prevNum = prevNode ? prevNum > num ? prevNum-- : prevNum : -1;
        if (num == 0) { head = head->next; }
        if (num == common_count - 1) { tail = tail->prev; }
        remove(del);
    }

    Pair& elementAt(int num) {
        if (num < 0 || num >= common_count) { throw out_of_range("Index out of range"); }
        Student* element = go_to(num);
        prevNode = element;
        prevNum = num;
        return element->data;
    }

    int count() const { return common_count; }

    void zeroing() {
        head = nullptr; tail = nullptr; prevNode = nullptr;
        groupNumber = "0";
        common_count = 0;
        prevNum = -1;
    }

    void clear() {
        Student* cur = head;
        while (cur) {
            Student* next = cur->next;
            cur->next = cur->prev = nullptr;
            delete cur;
            cur = next;
        }
        zeroing();
    }

    // ---------------------------------------------------------------------------------------


    void del_element(const Student value) {
        if (head == nullptr) return;
        Student* del = head;
        while (del) {
            if (del->data == value.data) {
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
                if (!common_count) { 
                    head = tail = prevNode = nullptr;
                    groupNumber = "0";
                    common_count = 0;
                    prevNum = -1;
                }
                break;
            }
            del = del->next;
        }
    }

    bool look_for(const Student& value) {
        if (!head) return false;
        Student* cur = head;
        while (cur) {
            if (cur->data == value.data) { return true; }
            cur = cur->next;
        }
        return false;
    }

    Student& look_for_node(const Student& value) {
        Student* cur = head;
        while (cur) {
            if (cur->data == value.data) { return *cur; }
            cur = cur->next;
        }
        throw out_of_range("Node not found");
    }


    Student* look_for_node_without_access(const Student& value) {
        Student* cur = head;
        while (cur) {
            if (cur->data == value.data) { return cur; }
            cur = cur->next;
        }
        throw out_of_range("Node not found");
    }

    float updateAverageScore() {
        float sumOfAverScore = 0;
        Student* cur = head;
        while (cur != nullptr) {
            sumOfAverScore += cur->data.value.average_grade();
            cur = cur->next;
        }
        return (sumOfAverScore / common_count);
    }
};



