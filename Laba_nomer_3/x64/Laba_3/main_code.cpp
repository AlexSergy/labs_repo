#include<iostream>
#include<cstdlib>
#include"List.cpp"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	List L;
	int choice, value;

	cout << "\n�������� � ����������� ����������� �������\n";
	cout << "1 - ������ ���������� � ����� ������.\n2 - �������� ������� � i-�� �������.\n3 - ������� ������� � i-�� ��������.\n";
	cout << "4 - ������, ��� �� ������� ����� �� i-�� �����.\n5 - ������ ���������� ��������� � ������.\n6 - �������� ����� ���. ���������� '1'.\n7 - ������� ���. ��������.\n8 - ���������, ������� ��� ����������� ��������� �������.\n";
	cout << "9 - �������� ���������\n����� ������ ����� - �����\n" << endl;

	cout << "����������! ��� 2-4 ������� ���������� ���������� � 0!\n" << endl;


	while (true) {
		cout << "�������� �������: ";
		cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������� ��� ���������� � ����� ������ (��� ���������� ������� ����� ������������ �������� ��� �������� ��� ������)\n";
            while (true) {
                cout << "�������� - ";
                if (!(cin >> value)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� � ����.\n";
                    break;
                }
                L.add(value);
            }
            break;
        case 2:
            cout << "������� ������� ��� ������� ��������: ";
            int position;
            cin >> position;
            cout << "������� �������� ��������: ";
            cin >> value;
            L.insert(position, value);
            break;
        case 3:
            cout << "������� ������� �������� ��� ��������: ";
            cin >> position;
            L.removeAt(position);
            break;
        case 4:
            cout << "������� ������� �������� ��� ���������: ";
            cin >> position;
            cout << "������� � ������� " << position << ": " << L.elementAt(position) << "\n";
            break;
        case 5:
            cout << "���������� ��������� � ������: " << L.count() << "\n";
            break;
        case 6:
            L.insertBeforeNegative();
            cout << "�������� ������� 1 ����� �������������� ���������� ���������\n";
            break;
        case 7:
            L.removeNegative();
            cout << "�������� ������������� ��������� ���������\n";
            break;
        case 8:
            cout << "������� �������� ��� �������� ���������: ";
            cin >> value;
            cout << "���������� ��������� " << value << ": " << L.count(value) << "\n";
            break;
        case 9:
            L.clear();
            cout << "������ ������\n";
            break;
        default:
            L.clear();
            exit(0);
        }
	}
}