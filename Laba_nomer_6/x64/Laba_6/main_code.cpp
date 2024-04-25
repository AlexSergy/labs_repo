#include<iostream>
#include"Tree.hpp"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	Tree Tree;
	int choice, value;


	cout << "\n�������� � �������� ������� ������.\n";
	cout << "1 - �������� ������� � ������.\n";
	cout << "2 - ������� ������� �� ������.\n";
	cout << "3 - ��������� ������� �������� � ������.\n";
	cout << "4 - �������� ���������� ��������� � ������.\n";
	cout << "5 - �������� ������.\n";
	cout << "����� ������ ����� - �����.\n";


	while (true) {
		cout << "������� ��������: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "������� �������� ��� ����������: ";
			cin >> value;
			Tree.add(value);
			break;
		case 2:
			cout << "������� �������� ��� ��������: ";
			cin >> value;
			Tree.remove(value);
			break;
		case 3:
			cout << "������� �������� ��� ������: ";
			cin >> value;
			if (Tree.contains(value)) { cout << "�������� ������� � ������.\n"; }
			else { cout << "�������� �� ������� � ������.\n"; }
			break;
		case 4:
			cout << "���-�� ��������� � ������: " << Tree.count() << "\n";
			break;
		case 5:
			Tree.clear();
			cout << "������ �������.\n";
			break;
		default: return 0;
		}
	}
	return 0;
}