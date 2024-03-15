#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// Создание стека 
struct Node {
	float data;
	Node* next;
};

const int max_size = 100;

struct Stack {
	int arr[max_size];
	int top;

	Stack() {
		top = -1; // инициализация вершины стека
	}

	void push(int val) {
		if (top >= max_size - 1) {
			std::cout << "переполнение стека!\n";
			return;
		}
		arr[++top] = val;
		std::cout << val << " элемент вошел в стек\n";
	}

	void pop() {
		if (top < 0) {
			std::cout << "переполнение стека\n";
			return;
		}
		int val = arr[top--];
		std::cout << val << " взят с стека\n";
	}

	int peek() {
		if (top < 0) {
			std::cout << "стек пуст \n";
			return -1;
		}
		return arr[top];
	}
};

// Функция добавления числа в стек
void push_to_stack(Node*& top, float value) {
	Node* newNode = new Node; // создание нового узла
	newNode->data = value; // запись значения в новый узел
	newNode->next = top; // указатель на текущий верхний элемент
	top = newNode; // обновление верхнего элемента стека
}

// функция вывода числа из стека
float get_and_pop(Node*& top) {
	if (top) {
		float value = top->data;
		Node* temp = top;  // сохраняется указатель на верхний элемент
		top = top->next;   // обновляется верхний элемент на следующий
		delete temp;       // удаляется старый верхний элемент
		return value;
	}
	return 0;  // Возвращаем 0, если стек пуст
}

// функция урпощенного вывода чисел из стека
void NOTdetailed_push(Node*& top) {
	float input;
	while (true) {
		cin >> input;
		if (input != 0) {
			push_to_stack(top, input);
		}
		else { break; }
	}
}

// Функция удаления стека
void delete_stack(Node*& top) {
	while (top) {
		Node* temp = top;
		top = top->next;
		delete temp;
	}
}

// функция вывода стека в файл
void write_to_file(Node*& top) {
	ofstream output_file;
	output_file.open("report.txt"); // Создаем файл output.txt
	float value;
	if (output_file.is_open()) {
		value = get_and_pop(top);
		while (true) {
			if (value > 0) {
				output_file << value << endl;
			}
			if (value == 0) { break; }
		}
		output_file.close();
		cout << "Числа успешно введены в файл retport.txt!" << endl;
	}
	else {
		cerr << "Ошибка создания файла!" << endl;
		exit;
	}
}

// Детальный ввод чисел в стек
void detailed_push(Node*& top) {
	int choice, num = 0;
	float input = 1;
	string input_file;
	cout << "Выберите 0, если вводите числа с консоли \nили любое другое число, если вводите с файла: ";
	cin >> choice;
	switch (choice) {
	case 0:
		cout << "Вводите числа (0 - окончание ввода)" << endl;
		while (true) {
			num += 1;
			cout << "Элемент " << num << ")";
			cin >> input;
			if (input != 0) {
				push_to_stack(top, input);
			}
			else { break; }
		}
		cout << "\nЧисла успешно введены!\n" << endl;
		break;
	default:
		cout << "Введите название файла: ";
		cin >> input_file;
		ifstream inputFile(input_file);
		if (!inputFile.is_open()) {
			cerr << "Ошибка вывода файла!" << endl;
			break;
		}

		while (inputFile >> input) {
			if (input != 0) {
				push_to_stack(top, input);
			}
			else { break; }
		}
		
		cout << "\nЧисла с файла успешно введены!\n" << endl;
		inputFile.close();
		break;
	}
		
}




int main(int argc, char* argv[]) {

	/*  
		В стандарте C++, сигнатура main должна соответствовать
		одной из двух стандартных форм:
		1)int main()
		2)int main(int argc, char* argv[])
		В нашем случае мы передаем аргумент в функцию,
		поэтому берем второй вариант
		argc - отвечает за кол-во аргументов,
		включая название программы.
		argv - массив аргументов
	*/


	bool interface = true;
	if (argc > 1) { interface = (strcmp(argv[1], "true") == 0); }
	setlocale(LC_ALL, "ru");
	Node* top = nullptr;
	int choice_of_man = 0, num = 0, fileorstream = 0;

	if (interface) {
		detailed_push(top);

		cout << "\n=========================================\n\n";

		cout << "Введите 0 для вывода чисел в файле, любое другое число для вывода в консоль: ";
		cin >> fileorstream;
		switch (fileorstream) {
		case 0:
			write_to_file(top);
		default:
			cout << "Введите 0 для подробного вывода, \nлюбое другое число для урпощенного: ";
			cin >> choice_of_man;
			switch (choice_of_man) {
			case 0:
				cout << "\nЭлементы с конца:\n";
				while (true) {
					float value = get_and_pop(top);
					if (value == 0) { break; }
					if (value > 0) {
						num += 1;
						cout << "Элемент " << num << ")" << value << endl;
					}
				}
				break;
			default:
				while (true) {
					float value = get_and_pop(top);
					if (value == 0) {
						break;  // выход из цикла, если стек пуст
					}
					if (value > 0) {
						cout << value << endl;
					}
				}
			}
		}
	}
	else {
		NOTdetailed_push(top);
		while (true) {
			float value = get_and_pop(top);
			if (value == 0) {
				break;
			}
			if (value > 0) {
				cout << value << endl;
			}
		}
	}


	delete_stack(top);
	return 0;
}

