#include<iostream>
#include<cstdlib> // для exit()
using namespace std;

struct Node { // создаем структуру узла
	int data; // элемент, в котором храним значение
	Node* next; // ссылка на след. узел

	Node(int value) : data(value), next(nullptr) {} // Если инициализируется нода с значением, значение присваиваем в data
	//~Node() { if (next != nullptr) { delete next; } }
};


class Queue {
public:
	Node* first; // первый введенный элемент
	Node* last; // последний введенный элемент

	Queue() : first(nullptr), last(nullptr) {} // по умолчанию первому и последнему элементу присваиваем nullptr

	~Queue() { clear(); } // деструктор, применяется при вызове delete Queue, либо автоматически при какой-либо остановке программы

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

	cout << "\nОперации с очередью\n";
	cout << "1 - Ввести переменные\n2 - Изъять 'старейшую' переменную\n3 - Посчитать длину списка\n";
	cout << "4 - Вставить перед каждым отр. числом '1'\n5 - Убрать все отрицательные числа\n6 - Найти количество вхождений определенной переменной\n7 - Отчистить очередь\n8 - Выйти\n";


	while (true) {
		cout << "Выберите команду (1-8): ";
		cin >> choice;
		switch (choice) {
		case 1:
			while (true) {
				cout << "Введите свою переменную (чтобы перестать вводить, введите 0): ";
				cin >> value;
				if (value == 0) { break; }
				Q.queue(value);
			}
			break;
		case 2:
			value = Q.unqueue();
			if (value != -1) { cout << "Извлеченная переменная: " << value << endl; }
			else { cout << "Очередь пуста.\n"; }
			break;
		case 3:
			cout << "Длина очереди: " << Q.count() << endl;
			break;
		case 4:
			Q.insertBeforeNegative();
			cout << "Операция прошла успешно!\n";
			break;
		case 5:
			Q.removeNegative();
			cout << "Отр. числа успешно удалены\n";
			break;
		case 6:
			cout << "Введите, какое число вы хотите посчитать: ";
			cin >> value;
			cout << "Число " << value << " встречается " << Q.count(value) << " раз(а).\n";
			break;
		case 7:
			Q.clear();
			cout << "Очередь очищена.\n";
			break;
		case 8:
			Q.clear();
			exit(0);
		default:
			cout << "Ошибка. Введите корректное значение." << endl;
		}
	}
}