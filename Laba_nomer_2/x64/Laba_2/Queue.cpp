
struct Node { // создаем структуру узла
	int data; // элемент, в котором храним значение
	Node* next; // ссылка на след. узел

	Node(int value) : data(value), next(nullptr) {} // Если инициализируется нода с значением, значение присваиваем в data
};


class Queue {
public:
	Node* first; // первый введенный элемент
	Node* last; // последний введенный элемент

	Queue() : first(nullptr), last(nullptr) {} // по умолчанию первому и последнему элементу присваиваем nullptr

	~Queue() { clear(); } // деструктор, применяется при вызове delete Queue, либо автоматически при какой-либо остановке программы
	// Но в данной реализации он не обязателен, учитывая то, что в main класс инициализируется внутри собственного стека, а не выделяет память
	
	void queue(int value) { // функция ввода переменной
		Node* newNode = new Node(value);

		if (last == nullptr) { first = last = newNode; } // если элементов нет, то присваиваем обоим указателям адрес первой ноды
		else {
			last->next = newNode;
			last = newNode;
		}

	}

	int unqueue() { // функция изьятия значения
		if (first == nullptr) { // если список пуст, выводим -1 (как ошибку)
			return -1;
		}

		Node* out_node = first;
		int value = out_node->data;
		first = out_node->next;
		if (first == nullptr) { // если находимся в конце очереди, то присваиваем к концу nullptr
			last = nullptr;
		}

		delete out_node;
		return value;
	}

	int count() { // Функция подстчета количества чисел в списке
		int count = 0;
		Node* current = first;

		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}

	void insertBeforeNegative() { // Функция подстановки "1" перед отрицательными числами
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
				current->next = nullptr; // Обнуляем next перед удалением
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

	int count(int value) { // Функция подсчета отдельного числа в списке
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