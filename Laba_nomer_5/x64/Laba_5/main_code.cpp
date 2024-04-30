#include<iostream>
#include"HashSet.hpp"
#include<string>
#include<limits> // ��� ��������� ������������� �����

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    HashSet hashSet;
    int choice;
    string value;

    cout << "\n�������� � ���-��������\n";
    cout << "1 - �������� ����� � ���-�������.\n";
    cout << "2 - ������� ����� �� ���-�������.\n";
    cout << "3 - ���������, ���������� �� ����� � ���-�������.\n";
    cout << "4 - ������ ���������� ���� � ���-�������.\n";
    cout << "5 - �������� ���-�������.\n";
    cout << "6 - ������� ��� ����� �� ���-�������.\n";
    cout << "����� ������ ����� - �����\n" << endl;

    while (true) {
        cout << "�������� �������: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������������ ����, ���������� ��� ���.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "������� ����� ��� ����������: ";
            cin >> value;
            hashSet.add(value);
            break;
        case 2:
            cout << "������� ����� ��� ��������: ";
            cin >> value;
            hashSet.remove(value);
            break;
        case 3:
            cout << "������� ����� ��� ��������: ";
            cin >> value;
            if (hashSet.contains(value)) {
                cout << "����� �������.\n";
            }
            else {
                cout << "����� �� �������.\n";
            }
            break;
        case 4:
            cout << "���������� ����: " << hashSet.count() << "\n";
            break;
        case 5:
            hashSet.clear();
            cout << "������� �������.\n";
            break;
        case 6: {
            int count = hashSet.count();
            auto wordsArr = hashSet.ToArray();
            cout << "����� � ���-�������: ";
            for (int i = 0; i < count; ++i) {
                cout << wordsArr[i] << (i < count - 1 ? ", " : ".");
            }
            cout << "\n";
            delete[] wordsArr; // ������� ������ ����� �������������
            break;
        }
        default:
            cout << "����� �� ���������.\n";
            return 0;
        }
    }
}
