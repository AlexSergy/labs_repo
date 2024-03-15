#include<iostream>
#include<fstream>
#include<string>

using namespace std;

// �������� ����� 
struct Node {
	float data;
	Node* next;
};

const int max_size = 100;

struct Stack {
	int arr[max_size];
	int top;

	Stack() {
		top = -1; // ������������� ������� �����
	}

	void push(int val) {
		if (top >= max_size - 1) {
			std::cout << "������������ �����!\n";
			return;
		}
		arr[++top] = val;
		std::cout << val << " ������� ����� � ����\n";
	}

	void pop() {
		if (top < 0) {
			std::cout << "������������ �����\n";
			return;
		}
		int val = arr[top--];
		std::cout << val << " ���� � �����\n";
	}

	int peek() {
		if (top < 0) {
			std::cout << "���� ���� \n";
			return -1;
		}
		return arr[top];
	}
};

// ������� ���������� ����� � ����
void push_to_stack(Node*& top, float value) {
	Node* newNode = new Node; // �������� ������ ����
	newNode->data = value; // ������ �������� � ����� ����
	newNode->next = top; // ��������� �� ������� ������� �������
	top = newNode; // ���������� �������� �������� �����
}

// ������� ������ ����� �� �����
float get_and_pop(Node*& top) {
	if (top) {
		float value = top->data;
		Node* temp = top;  // ����������� ��������� �� ������� �������
		top = top->next;   // ����������� ������� ������� �� ���������
		delete temp;       // ��������� ������ ������� �������
		return value;
	}
	return 0;  // ���������� 0, ���� ���� ����
}

// ������� ����������� ������ ����� �� �����
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

// ������� �������� �����
void delete_stack(Node*& top) {
	while (top) {
		Node* temp = top;
		top = top->next;
		delete temp;
	}
}

// ������� ������ ����� � ����
void write_to_file(Node*& top) {
	ofstream output_file;
	output_file.open("report.txt"); // ������� ���� output.txt
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
		cout << "����� ������� ������� � ���� retport.txt!" << endl;
	}
	else {
		cerr << "������ �������� �����!" << endl;
		exit;
	}
}

// ��������� ���� ����� � ����
void detailed_push(Node*& top) {
	int choice, num = 0;
	float input = 1;
	string input_file;
	cout << "�������� 0, ���� ������� ����� � ������� \n��� ����� ������ �����, ���� ������� � �����: ";
	cin >> choice;
	switch (choice) {
	case 0:
		cout << "������� ����� (0 - ��������� �����)" << endl;
		while (true) {
			num += 1;
			cout << "������� " << num << ")";
			cin >> input;
			if (input != 0) {
				push_to_stack(top, input);
			}
			else { break; }
		}
		cout << "\n����� ������� �������!\n" << endl;
		break;
	default:
		cout << "������� �������� �����: ";
		cin >> input_file;
		ifstream inputFile(input_file);
		if (!inputFile.is_open()) {
			cerr << "������ ������ �����!" << endl;
			break;
		}

		while (inputFile >> input) {
			if (input != 0) {
				push_to_stack(top, input);
			}
			else { break; }
		}
		
		cout << "\n����� � ����� ������� �������!\n" << endl;
		inputFile.close();
		break;
	}
		
}




int main(int argc, char* argv[]) {

	/*  
		� ��������� C++, ��������� main ������ ���������������
		����� �� ���� ����������� ����:
		1)int main()
		2)int main(int argc, char* argv[])
		� ����� ������ �� �������� �������� � �������,
		������� ����� ������ �������
		argc - �������� �� ���-�� ����������,
		������� �������� ���������.
		argv - ������ ����������
	*/


	bool interface = true;
	if (argc > 1) { interface = (strcmp(argv[1], "true") == 0); }
	setlocale(LC_ALL, "ru");
	Node* top = nullptr;
	int choice_of_man = 0, num = 0, fileorstream = 0;

	if (interface) {
		detailed_push(top);

		cout << "\n=========================================\n\n";

		cout << "������� 0 ��� ������ ����� � �����, ����� ������ ����� ��� ������ � �������: ";
		cin >> fileorstream;
		switch (fileorstream) {
		case 0:
			write_to_file(top);
		default:
			cout << "������� 0 ��� ���������� ������, \n����� ������ ����� ��� �����������: ";
			cin >> choice_of_man;
			switch (choice_of_man) {
			case 0:
				cout << "\n�������� � �����:\n";
				while (true) {
					float value = get_and_pop(top);
					if (value == 0) { break; }
					if (value > 0) {
						num += 1;
						cout << "������� " << num << ")" << value << endl;
					}
				}
				break;
			default:
				while (true) {
					float value = get_and_pop(top);
					if (value == 0) {
						break;  // ����� �� �����, ���� ���� ����
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

