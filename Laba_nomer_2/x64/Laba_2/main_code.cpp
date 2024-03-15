#include<iostream>
#include<cstdlib> // ��� exit()
#include"Queue.cpp"
using namespace std;


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