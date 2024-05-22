#include"Flow.hpp"
#include"Info.hpp"
#include"Student.hpp"
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

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
	cout << "����������! ����� �������� ������� ������ � '+'!\n";
	cout << "--------------------------------------------------------------------\n";
}

template <typename G>
void merge(G* arr, int left, int middle, int right) {
	int n1 = middle - left + 1;
	int n2 = right - middle;

	G* L = new G[n1];
	G* R = new G[n2];

	// �������� ��� � ��������� �������
	for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; }
	for (int j = 0; j < n2; j++) { R[j] = arr[middle + 1 + j]; }

	// ������� ��������� ������� �������
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i].second >= R[j].second) {
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

template <typename G>
void mergeSort(G* arr, int left, int right) {
	if (left < right) {
		int middle = left + (right - left) / 2;
		mergeSort(arr, left, middle);
		mergeSort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}

string normalizeName(const string& name) {
	string normalized = name;
	transform(normalized.begin(), normalized.end(), normalized.begin(), ::tolower);
	normalized.erase(remove_if(normalized.begin(), normalized.end(), ::isspace), normalized.end());
	return normalized;
}

void rankAndPrintStudents(Flow& flow, const Student& inputStudent) {
	Group temp;
	Student* allStudents = flow.toArray();
	int count = flow.element_count;
	pair<int, int>* rankedIndexes = new pair<int, int>[count];

	for (int i = 0; i < count; i++) {
		int rank = 0;
		if (normalizeName(allStudents[i].data.key) == normalizeName(inputStudent.data.key)) { rank += 5; }
		if (allStudents[i].data.value.groupNumber == inputStudent.data.value.groupNumber) { rank += 2; }
		if (allStudents[i].data.value.arr == inputStudent.data.value.arr) { rank += 2; }
		if (allStudents[i].data.value.scholarship == inputStudent.data.value.scholarship) { rank += 2; }
		if (allStudents[i].data.value.phoneNumber == inputStudent.data.value.phoneNumber) { rank += 7; }
		if (rank > 1) {
			Student rankedStudent(allStudents[i]);
			temp.add(rankedStudent);
			rankedIndexes[temp.common_count - 1] = make_pair(temp.common_count - 1, rank);
		}
	}
	delete[] allStudents;

	// simple sorting tempGroup by descending compatibility rating
	mergeSort(rankedIndexes, 0, temp.common_count - 1);
	cout << "\n��� ��������, ���������� ��� ������� ������ � ������������� �������\n";

	for (int m = 0; m < temp.common_count; m++) {
		int index = rankedIndexes[m].first;
		Student* current = temp.go_to(index);
		if (current != nullptr) {
			cout << "���: " << current->data.key << ". ";
			cout << "������: " << current->data.value.groupNumber << ". ";
			cout << "������: ";
			for (int j = 0; j < 5; j++) {
				cout << current->data.value.arr[j] << " ";
			}
			cout << "���������: " << current->data.value.scholarship << ". ";
			cout << "�������: " << current->data.value.phoneNumber << ". ";
			cout << endl;
		}
		else {
			cerr << "������: ��������� �� ������ 'current' ����� nullptr." << endl;
			continue;
		}
	}

	temp.clear();
	delete[] rankedIndexes;
}


/*
Group temp;
	Student* allStudents = flow.toArray();
	int count = flow.element_count;
	pair<int, int>* rankedIndexes = new pair<int, int>[count];

	for (int i = 0; i < count; i++) {
		int rank = 0;
		if (normalizeName(allStudents[i].data.key) == normalizeName(inputStudent.data.key)) rank += 5;
		if (allStudents[i].data.value.groupNumber == inputStudent.data.value.groupNumber) rank += 2;
		if (allStudents[i].data.value.arr == inputStudent.data.value.arr) rank += 2;
		if (allStudents[i].data.value.scholarship == inputStudent.data.value.scholarship) rank += 2;
		if (allStudents[i].data.value.phoneNumber == inputStudent.data.value.phoneNumber) rank += 7;
		if (rank > 1) {
			Student rankedStudent(allStudents[i]);
			temp.add(rankedStudent);
			rankedIndexes[temp.common_count - 1] = make_pair(temp.common_count - 1, rank);
		}
	}
	delete[] allStudents;

	// simple sorting tempGroup by descending compatibility rating
	mergeSort(rankedIndexes, 0, temp.common_count-1);

	for (int m = 0; m < temp.common_count-1; m++) {
		int index = rankedIndexes[m].first;
		Student* current = temp.go_to(index);
		cout << "���: " << current->data.key << ". ";
		cout << "������: " << current->data.value.groupNumber << ". ";
		cout << "������: ";
		for (int j = 0; j < 5; j++) {
			cout << current->data.value.arr[j] << " ";
		}
		cout << "���������: " << current->data.value.scholarship << ". ";
		cout << "�������: " << current->data.value.phoneNumber << ". ";
		cout << endl;
	}

	temp.clear();
	delete[] rankedIndexes;
*/
void Student_output(int count, Student* array) {
	for (int i = 0; i < count; i++) {
		cout << "���: " << array[i].data.key << " | ";
		cout << " �������: " << array[i].data.value.phoneNumber << " | ";
		cout << " ������: " << array[i].data.value.groupNumber << " | ";
		cout << " ������: "; for (int j = 0; j < 5; j++) { cout << " " << array[i].data.value.arr[j] << " "; } cout << " | ";
		cout << " ���������: " << array[i].data.value.scholarship << " ������.\n";
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
		new_student.clear();

		switch (choice) {
		case 1: {
			// ���������� ���� ������ � ���������
			cout << "������� ��� ��������: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');getline(cin, new_student.data.key);
			cout << "������� ����� ������ (�� ��� ���� ����� ������ �������� � ������): "; cin >> new_student.data.value.groupNumber;
			cout << "������� ���� ������ ��������:\n"; for (int i = 0; i < 5; i++) { cout << i << ") "; cin >> new_student.data.value.arr[i]; }
			cout << "������� ��������� ��������: "; cin >> new_student.data.value.scholarship;
			cout << "������� ���������� ����� �������� (�� ���� � ������� ���������������� ��������): "; cin >> new_student.data.value.phoneNumber;
			Flow.add(new_student.data.value.groupNumber, new_student);
			cout << "������� ������� ������ � �����.\n";
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
			break;
		}
		case 4: {
			cout << "���� ��� �� �������� ������ � ����� �������� ��������, ������� 1, ����� ����� ������ �����: ";
			cin >> choice;
			if (choice == 1) {
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
			else {
				cout << "������� ����� ���������� � ��������, ������� ������������.\n";
				new_student.clear();
				cout << "������� ��� �������� (� ������ ����������, ������� '-'): ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');getline(cin, new_student.data.key);
				cout << "������� ����� ������ (� ������ ����������, ������� '0'): "; cin >> new_student.data.value.groupNumber;
				cout << "������� ���� ������ �������� (� ������ ����������, ������� ����� '0'): \n"; for (int i = 0; i < 5; i++) { cout << i << ") "; cin >> new_student.data.value.arr[i]; }
				cout << "������� ��������� �������� (� ������ ����������, ������� '-1'): "; cin >> new_student.data.value.scholarship;
				cout << "������� ���������� ����� �������� (� ������ ����������, ������� '-'): "; cin >> new_student.data.value.phoneNumber;
				rankAndPrintStudents(Flow, new_student);
				break;
			}
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
			Flow.element_count -= Flow.arr[Flow.hashFoo(group)].common_count;
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
			int oldindex = Flow.hashFoo(group), newindex = Flow.hashFoo(group);
			Flow.arr[oldindex].groupNumber = newGroup;
			Flow.arr[oldindex].updateGroup(newGroup);
			if (Flow.arr[newindex].head) Flow.resize();
			Flow.arr[oldindex] = Flow.arr[newindex];
			Flow.arr[oldindex].clear();
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
			{ cout << "������: " << group_grades[i].first << ", ������� ����: " << group_grades[i].second << endl; } 
			delete[] group_grades;
			break;
		}
		case 11: { 
			int group_cnt = Flow.get_count_of_groups();
			Pair_for_sort* group_grades = Flow.arrayOfAverageGrades();
			mergeSort(group_grades, 0, group_cnt - 1);
			cout << "������ � ���������� ������ " << group_grades[0].first << ", �� ��� ���������� " << group_grades[0].second << ".\n"; 
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