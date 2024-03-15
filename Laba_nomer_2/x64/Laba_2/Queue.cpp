
struct Node { // ������� ��������� ����
	int data; // �������, � ������� ������ ��������
	Node* next; // ������ �� ����. ����

	Node(int value) : data(value), next(nullptr) {} // ���� ���������������� ���� � ���������, �������� ����������� � data
};


class Queue {
public:
	Node* first; // ������ ��������� �������
	Node* last; // ��������� ��������� �������

	Queue() : first(nullptr), last(nullptr) {} // �� ��������� ������� � ���������� �������� ����������� nullptr

	~Queue() { clear(); } // ����������, ����������� ��� ������ delete Queue, ���� ������������� ��� �����-���� ��������� ���������
	// �� � ������ ���������� �� �� ����������, �������� ��, ��� � main ����� ���������������� ������ ������������ �����, � �� �������� ������
	
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
		if (first == nullptr) { // ���� ��������� � ����� �������, �� ����������� � ����� nullptr
			last = nullptr;
		}

		delete out_node;
		return value;
	}

	int count() { // ������� ��������� ���������� ����� � ������
		int count = 0;
		Node* current = first;

		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	void insertBeforeNegative() { // ������� ����������� "1" ����� �������������� �������
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
				}
				else {
					prev->next = current->next;
				}
				current->next = nullptr; // �������� next ����� ���������
				Node* temp = current;
				current = first;
				delete temp;
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

	int count(int value) { // ������� �������� ���������� ����� � ������
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
		while (current != nullptr) {
			Node* temp = current->next;
			current->next = nullptr; 
			delete current;
			current = temp;
		}
	}
};