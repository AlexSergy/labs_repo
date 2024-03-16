
struct Node { // создаем структуру узла
	int data; // элемент, в котором храним значение
	Node* next; // ссылка на след. узел

	Node(int value) : data(value), next(nullptr) {} // ≈сли инициализируетс€ нода с значением, значение присваиваем в data
};



class List {
public:
	Node* head; // первый, головной элемент
	int common_count = 0;

	void add(int value) {
		Node* newNode = new Node(value);
		if (head == nullptr) {
			head = newNode;
			newNode->next = head;
			common_count++;
		}
		else {
			Node* current = head;
			while (current->next != head) {
				current = current->next;
			}
			current->next = newNode;
			newNode->next = head;
			common_count++;
		}
	}

	void insert(int num, int value) {
		int current = 0;
		Node* currentNode = head;
		while (current != num) {
			currentNode = currentNode->next;
			current++;
		}
		currentNode->data = value;
	}

	void removeAt(int num) {
		if (num < 0 || num >= common_count || (head == nullptr && num > 0)) {
			return; // просто выходим из метода из-за ошибки
		}
		int current = 0;
		Node* currentNode = head;

		while (((current != num - 1) - (num == 0)) != 0) {
			currentNode = currentNode->next;
			current++;
		}
		Node* delNode = currentNode->next;
		currentNode->next = currentNode->next->next;
		delNode->next = nullptr;
		delete delNode;
		common_count--;
	}

	int elementAt(int num) {
		int current = 0;
		Node* currentNode = head;
		while (current != num) {
			currentNode = currentNode->next;
			current++;
		}
		return currentNode->data;
	}

	int count() { return common_count; }

	void insertBeforeNegative() {
		Node* currentNode = head;
		do {
			if (currentNode->next->data < 0) {
				Node* newNode = new Node(1);
				newNode->next = currentNode->next;
				currentNode->next = newNode;
				currentNode = currentNode->next->next;
				common_count++;
			}
			else { currentNode = currentNode->next; }
		} while (currentNode->next != head->next);
	}

	void removeNegative() {
		Node* currentNode = head;
		do {
			if (currentNode->next->data < 0) {
				Node* delNode = currentNode->next;
				currentNode->next = currentNode->next->next;
				currentNode = currentNode->next;
				delNode->next = nullptr;
				delete delNode;
				common_count--;
			}
			else { currentNode = currentNode->next; }
		} while (currentNode->next != head->next);
	}

	int count(int value) {
		int count = 0;
		Node* current = head;
		if (head != nullptr) {
			do { if (current->data == value) { count++; }
				current = current->next;
			} while (current != head);
		}
		return count;
	}

	void clear() {
		if (head == nullptr) {
			return; // —писок уже пуст, ничего не нужно делать
		}

		Node* current = head->next;
		head->next = nullptr;
		head = nullptr;
		common_count = 0;

		while (current != nullptr) {
			Node* temp = current->next;
			delete current;
			current = temp;
		}
	}
};