#include"Flow.hpp"
#include"Info.hpp"
#include"Student.hpp"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void printMenu() {
	cout << "\n\t�������� � ������� ���������\n";
	cout << "1 - �������� ��������.\n";
	cout << "2 - ������� ��������.\n";
	cout << "3 - ������������� ������ ��������.\n";
	cout << "4 - ������� ���������� � ��������.\n";
	cout << "5 - ������� ������ ���� ��������� ������.\n";
	cout << "6 - ������� ���������� ��������� ������.\n";
	cout << "\n\t�������� � ��������\n";
	cout << "7 - ������� ������ �� ������.\n";
	cout << "8 - ������������� ����� ������.\n";
	cout << "9 - ������� ������ ��������� ��������� ������.\n";
	cout << "10 - ������� ������ �� ���������������� �������� �����.\n";
	cout << "11 - ������� ������ � ������������ ������� ������ (� ���������� �������).\n";
	cout << "\n\t���� ����� ������\n";
	cout << "12 - ������� ������ � ������ �� �����.\n";
	cout << "13 - ��������� ������ � ������ � ����.\n";
	cout << "����� ������ ������ - ��������� ���������.\n";
	cout << "--------------------------------------------------------------------\n";
}

void Student_output(int count, Student* array) {
	for (int i = 0; i < count; i++) {
		cout << "���: " << array[i].data.key << " | ";
		cout << " �������: " << array[i].data.value.phoneNumber << " | ";
		cout << " ������: " << array[i].data.value.groupNumber << " | ";
		cout << " ������: "; for (int j = 0; j < 5; j++) { cout << " " << array[i].data.value.arr[j] << " "; } cout << " | ";
		cout << " ���������: " << array[i].data.value.scholarship << " ������.\n";
	}
}

void merge(Pair_for_sort* arr, int left, int middle, int right) {
	int n1 = middle - left + 1;
	int n2 = right - middle;

	Pair_for_sort* L = new Pair_for_sort[n1];
	Pair_for_sort* R = new Pair_for_sort[n2];

	// �������� ��� � ��������� �������
	for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; }
	for (int j = 0; j < n2; j++) { R[j] = arr[middle + 1 + j]; }

	// ������� ��������� ������� �������
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i].grade >= R[j].grade) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// ���� �������� ��������, �������� ����������
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

	delete[] L;
	delete[] R;
}

void mergeSort(Pair_for_sort* arr, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergeSort(arr, left, middle);
		mergeSort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}



int main() {
	setlocale(LC_ALL, "ru");
	Flow Flow;
	Student new_student;
	int choice;
	string number, group;

	printMenu();

	do {
		cout << "������� �������: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			// ���������� ���� ������ � ���������
			cout << "������� ��� ��������: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');getline(cin, new_student.data.key);
			cout << "������� ����� ������ (�� ��� ���� ����� ������ �������� � ������): "; cin >> new_student.data.value.groupNumber;
			cout << "������� ���� ������ ��������: "; for (int i = 0; i < 5; i++) { cout << i << ") "; cin >> new_student.data.value.arr[i]; }
			cout << "������� ��������� ��������: "; cin >> new_student.data.value.scholarship;
			cout << "������� ���������� ����� �������� (�� ���� � ������� ���������������� ��������): "; cin >> new_student.data.value.phoneNumber;
			Flow.add(new_student.data.value.groupNumber, new_student);
			cout << "������� ������� ������ � �����.\n";
			new_student.clear();
			break;
		}
		case 2: {
			cout << "������� ������ ��������: ";
			cin >> group;
			cout << "������� ����� �������� ���������� ��������: ";
			cin >> number;
			Flow.remove(number, group);
			cout << "������� ������� ������.\n";
			break;
		}
		case 3: {
			cout << "������� ������ ��������: ";
			cin >> group;
			cout << "������� ����� �������� �������������� ��������: ";
			cin >> number;
			cout << "\t���� ����������� ���������� � ��������\n";
			cout << "(���� ������ ������ ��������� �������� �� ����� ������ � ������,\n ������ �������� ����� ������, � ������� ������ ������)\n";
			cout << "������� ����������� ����� ������: "; cin >> new_student.data.value.groupNumber;
			cout << "������� ����������� ������ ��������:\n"; for (int i = 0; i < 5; i++) { cout << i << ") "; cin >> new_student.data.value.arr[i]; }
			cout << "������� ����������� ��������� ��������: "; cin >> new_student.data.value.scholarship;
			cout << "������� ����������� ���������� ����� �������� (�� ���� � ������� ���������������� ��������): "; cin >> new_student.data.value.phoneNumber;
			if (new_student.data.value.groupNumber == group) {
				Flow.updateStudent(new_student, number, group); 
				cout << "������ ������� ��������.\n";
			}
			else {
				Flow.add(new_student.data.value.groupNumber, new_student);
				Flow.remove(number, group);
				cout << "����������� ������� ������� ���������.\n";
			}
			new_student.clear();
			break;
		}
		case 4: {
			cout << "������� ������ ��������: ";
			cin >> group;
			cout << "������� ����� �������� ���������������� ��������: ";
			cin >> number;
			Student* student_info = Flow.arr[Flow.hashFoo(group)].look_for_node_without_access(Student(Pair(group, number)));
			cout << "���: " << student_info->data.key;
			cout << " ������: "; for (int i = 0; i < 5; i++) { cout << " " << student_info->data.value.arr[i] << " "; };
			cout << " ���������: " << student_info->data.value.scholarship << " ������.\n";
			break;
		}
		case 5: {
			Student* array = Flow.toArray();
			Student_output(static_cast<int>(Flow.element_count), array);
			break;
		}
		case 6: {
			cout << "����� ���������� ���������: " << Flow.count() << endl; break;
		}
		case 7: {
			cout << "������� ����� ��������� ������: ";
			cin >> group;
			Flow.arr[Flow.hashFoo(group)].clear();
			cout << "������ ������� �������.\n";
			break;
		}
		case 8: {
			string newGroup;
			cout << "������� ����� ������������� ������: ";
			cin >> group;
			cout << "������� ����� ����� ������: ";
			cin >> newGroup;
			Flow.arr[Flow.hashFoo(group)].groupNumber = newGroup;
			cout << "����� ������ ������� ��������������.\n";
			break;
		}
		case 9: {
			cout << "������� ����� ������������ ������: ";
			cin >> group;
			Student* array = Flow.toArray(group);
			Student_output(Flow.arr[Flow.hashFoo(group)].common_count, array);
			break;
		}
		case 10: { 
			int group_cnt = Flow.get_count_of_groups();
			Pair_for_sort* group_grades = Flow.arrayOfAverageGrades();
			mergeSort(group_grades, 0, group_cnt - 1);
			for (int i = 0; i < group_cnt; i++) 
			{ cout << "������: " << group_grades[i].group << ", ������� ����: " << group_grades[i].grade << endl; } 
			delete[] group_grades;
			break;
		}
		case 11: { 
			int group_cnt = Flow.get_count_of_groups();
			Pair_for_sort* group_grades = Flow.arrayOfAverageGrades();
			mergeSort(group_grades, 0, group_cnt - 1);
			cout << "������ � ���������� ������ " << group_grades[0].group << ", �� ��� ���������� " << group_grades[0].grade << ".\n"; 
			delete[] group_grades;
			break; 
		}
		case 12: {
			string filename;
			cout << "������� ��� ����� txt � ����������: ";
			cin >> filename;
			ifstream inFile(filename);
			if (!inFile.is_open()) { cerr << "�� ������� ������� ���� ��� ������.\n"; }
			else {
				string line;
				Flow.clear();
				while (getline(inFile, line)) {
					istringstream iss(line);
					string token;
					getline(iss, token, ':'); // ������� ���
					getline(iss, new_student.data.key, '|'); 
					new_student.data.key.erase(0, 1); // �������� ������� � ������ �����
					getline(iss, token, ':'); // ������� ��������
					iss >> new_student.data.value.phoneNumber;
					getline(iss, token, ':');
					iss >> new_student.data.value.groupNumber;
					getline(iss, token, ':');
					for (int i = 0; i < 5; i++) { iss >> new_student.data.value.arr[i]; }
					getline(iss, token, ':');
					iss >> new_student.data.value.scholarship;
					getline(iss, token);
					Flow.add(new_student.data.value.groupNumber, new_student);
				}
				inFile.close();
			}
			break;
		}
		case 13: {
			ofstream outFile("students_data.txt");
			if (!outFile.is_open()) { cerr << "�� ������� ������� ����\n"; break; }
			Student* array = Flow.toArray();
			for (int i = 0; i < Flow.element_count; i++) {
				outFile << "���: " << array[i].data.key << " | ";
				outFile << "�������: " << array[i].data.value.phoneNumber << " | ";
				outFile << "������: " << array[i].data.value.groupNumber << " | ";
				outFile << "������: ";
				for (int j = 0; j < 5; j++) { outFile << array[i].data.value.arr[j] << " "; }
				outFile << "| ���������: " << array[i].data.value.scholarship << " ������.n";
				outFile.close();
				delete[] array;
			}
			break;
		}
		}
		
	} while (choice != 13);
	return 0;
}