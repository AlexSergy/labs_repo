#include<iostream>
#include<cstdlib> // ��� exit()
using namespace std;

struct Node { // ������� ��������� ����
	int data; // �������, � ������� ������ ��������
	Node* next; // ������ �� ����. ����

	Node(int value) : data(value), next(nullptr) {} // ���� ���������������� ���� � ���������, �������� ����������� � data
	//~Node() { if (next != nullptr) { delete next; } }
};


class Queue {
public:
	Node* first; // ������ ��������� �������
	Node* last; // ��������� ��������� �������

	Queue() : first(nullptr), last(nullptr) {} // �� ��������� ������� � ���������� �������� ����������� nullptr

	~Queue() { clear(); } // ����������, ����������� ��� ������ delete Queue, ���� ������������� ��� �����-���� ��������� ���������

	void queue(int value) { // ������� ����� ����������
		Node* newNode = new Node(value);

		if (last == nullptr) { first = last = newNode; } // ���� ��������� ���, �� ����������� ����� ���������� ����� ������ ����
		else {
			last->next = newNode;
			last = newNode;
		}

	}

	int unqueue() { // ������� ������� ��������
		if (first == nullptr) { // ���� ������ ����, ������� -1 (��� ������)
			return -1;
		}

		Node* out_node = first;
		int value = out_node->data;
		first = out_node->next;
		if (first == nullptr) {
			last = nullptr;
		}

		delete out_node;
		return value;
	}

	int count() {
		int count = 0;
		Node* current = first;

		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	void insertBeforeNegative() {
		Node* current = first;
		Node* previus = nullptr;

		while (current != nullptr) {
			if (current->data < 0) {
				Node* newNode = new Node(1);

				if (current == first) {
					newNode->next = current;
					first = newNode;
				}
				else {
					newNode->next = current;
					previus->next = newNode;
				}
			}

			previus = current;
			current = current->next;
		}
	}


	void removeNegative() {
		Node* current = first;
		Node* prev = nullptr;

		while (current != nullptr) {
			if (current->data < 0) {
				if (current == first) {
					first = current->next;
					Node* temp = current;
					current = current->next;
					delete temp;
				}
				else {
					prev->next = current->next;
					Node* temp = current;
					current = current->next;
					delete temp;
				}
			}
			else {
				prev = current;
				current = current->next;
			}
		}

		if (first == nullptr) {
			last = nullptr;
		}
	}

	int count(int value) {
		int count = 0;
		Node* current = first;
		while (current != nullptr) {
			if (current->data == value) { count++; }
			current = current->next;
		}
		return count;
	}

	void clear() {
		Node* current = first;
		first = last = nullptr;
		delete current;
	}
};


int main() {
	setlocale(LC_ALL, "ru");
	Queue Q;
	int choice, value;

	cout << "\n�������� � ��������\n";
	cout << "1 - ������ ����������\n2 - ������ '���������' ����������\n3 - ��������� ����� ������\n";
	cout << "4 - �������� ����� ������ ���. ������ '1'\n5 - ������ ��� ������������� �����\n6 - ����� ���������� ��������� ������������ ����������\n7 - ��������� �������\n8 - �����\n";


	while (true) {
		cout << "�������� ������� (1-8): ";
		cin >> choice;
		switch (choice) {
		case 1:
			while (true) {
				cout << "������� ���� ���������� (����� ��������� �������, ������� 0): ";
				cin >> value;
				if (value == 0) { break; }
				Q.queue(value);
			}
			break;
		case 2:
			value = Q.unqueue();
			if (value != -1) { cout << "����������� ����������: " << value << endl; }
			else { cout << "������� �����.\n"; }
			break;
		case 3:
			cout << "����� �������: " << Q.count() << endl;
			break;
		case 4:
			Q.insertBeforeNegative();
			cout << "�������� ������ �������!\n";
			break;
		case 5:
			Q.removeNegative();
			cout << "���. ����� ������� �������\n";
			break;
		case 6:
			cout << "�������, ����� ����� �� ������ ���������: ";
			cin >> value;
			cout << "����� " << value << " ����������� " << Q.count(value) << " ���(�).\n";
			break;
		case 7:
			Q.clear();
			cout << "������� �������.\n";
			break;
		case 8:
			Q.clear();
			exit(0);
		default:
			cout << "������. ������� ���������� ��������." << endl;
		}
	}
}