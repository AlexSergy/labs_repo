
struct Node { // создаем структуру узла
	int data; // элемент, в котором храним значение
	Node* next; // ссылка на след. узел

	Node(int value) : data(value), next(nullptr) {} // ≈сли инициализируетс€ нода с значением, значение присваиваем в data
};



class List {
public:
	Node* head = nullptr; // первый, головной элемент
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

	void insert(int num, int value) { // ??
		if (num < 0 || num > common_count || (head == nullptr && num > 0)) {
			return;
		}
		Node* newNode = new Node(value);
		Node* currentNode = head;

		if (num == common_count && common_count != 0) { // —лучай, когда мы добавл€ем элемент в конец списка
			for (int i = 0; i < num-1; i++) { currentNode = currentNode->next; }
			currentNode->next = newNode;
			newNode->next = head;
		}

		else if (num == 0) { // ≈сли присваиваем на первое место
			if (head == nullptr) { 
				head = newNode;
			}
			else {
				while (currentNode->next != head) { currentNode = currentNode->next; }
				currentNode->next = newNode;
				newNode->next = head;
				head = newNode;
			}
		}
		else {
			for (int i = 0; i < num-1; i++) { currentNode = currentNode->next; }
			newNode->next = currentNode->next;
			currentNode->next = newNode;
		}

		common_count++;
	}

	void removeAt(int num) {
		if (num < 0 || num >= common_count || (head == nullptr && num > 0)) { return; }
		int cur = 0;
		Node* beforeDel = head;
		
		if (head == nullptr) { return; }

		if (num == 0) {
			if (common_count == 1) {
				head->next = nullptr;
				delete head;
				head = beforeDel = nullptr;
				common_count--;
				return;
			}
			else {
				while (beforeDel->next != head) { beforeDel = beforeDel->next; }
				head = head->next;
				beforeDel->next->next = nullptr;
				delete beforeDel->next;
				beforeDel->next = head;
				common_count--;
				return;
			}
		}

		
		while (cur != num - 1) {
			beforeDel = beforeDel->next;
			cur++;
		}

		Node* crutch = beforeDel->next->next;
		beforeDel->next->next = nullptr;
		delete beforeDel->next;
		beforeDel->next = crutch;
		common_count--;
	}

	int elementAt(int num) {
		int current = 0;
		Node* currentNode = head;
		while (current != num) {
			currentNode = currentNode->next;
			current++;
		}
		if (currentNode != nullptr) { return currentNode->data; }
		else { return -1; }
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

		Node* current = head;
		do {
			Node* nextNode = current->next;
			delete current;
			current = nextNode;
		} while (current != head);

		head = nullptr;
		common_count = 0;
	}
};