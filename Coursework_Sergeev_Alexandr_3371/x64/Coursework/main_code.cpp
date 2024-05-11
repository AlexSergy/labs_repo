#include"Flow.hpp"
#include"Info.hpp"
#include"Student.hpp"
#include<iostream>
#include<fstream>
#include<string>

using namespace std;

void printMenu() {
	cout << "\n\tОПЕРАЦИИ С ПОТОКОМ СТУДЕНТОВ\n";
	cout << "1 - Добавить студента.\n";
	cout << "2 - Удалить студента.\n";
	cout << "3 - Редактировать данные студента.\n";
	cout << "4 - Вывести информацию о студенте.\n";
	cout << "5 - Вывести список всех студентов потока.\n";
	cout << "6 - Вывести количество студентов потока.\n";
	cout << "\n\tОПЕРАЦИИ С ГРУППАМИ\n";
	cout << "7 - Удалить группу по номеру.\n";
	cout << "8 - Редактировать номер группы.\n";
	cout << "9 - Вывести список студентов указанной группы.\n";
	cout << "10 - Вывести группы по отсортированному среднему баллу.\n";
	cout << "11 - Вывести группу с максимальным средним баллом (в алфавитном порядке).\n";
	cout << "\n\tВВОД ВЫВОД ДАННЫХ\n";
	cout << "12 - Вывести данные о потоке из файла.\n";
	cout << "13 - Сохранить данные о потоке в файл.\n";
	cout << "Любой другой символ - закончить программу.\n";
	cout << "--------------------------------------------------------------------\n";
}

void Student_output(int count, Student* array) {
	for (int i = 0; i < count; i++) {
		cout << "ФИО: " << array[i].data.key << " | ";
		cout << " Телефон: " << array[i].data.value.phoneNumber << " | ";
		cout << " Группа: " << array[i].data.value.groupNumber << " | ";
		cout << " Оценки: "; for (int j = 0; j < 5; j++) { cout << " " << array[i].data.value.arr[j] << " "; } cout << " | ";
		cout << " Стипендия: " << array[i].data.value.scholarship << " рублей.\n";
	}
}

void merge(Pair_for_sort* arr, int left, int middle, int right) {
	int n1 = middle - left + 1;
	int n2 = right - middle;

	Pair_for_sort* L = new Pair_for_sort[n1];
	Pair_for_sort* R = new Pair_for_sort[n2];

	// копируем все в временные массивы
	for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; }
	for (int j = 0; j < n2; j++) { R[j] = arr[middle + 1 + j]; }

	// Сливаем временные массивы обратно
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

	// Если остались элементы, копируем оставшееся
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
		cout << "Введите команду: ";
		cin >> choice;

		switch (choice) {
		case 1: {
			// Консольный ввод данных о студентах
			cout << "Введите ФИО студента: ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');getline(cin, new_student.data.key);
			cout << "Введите номер группы (по ней идет поиск группы студента в потоке): "; cin >> new_student.data.value.groupNumber;
			cout << "Введите пять оценок студента: "; for (int i = 0; i < 5; i++) { cout << i << ") "; cin >> new_student.data.value.arr[i]; }
			cout << "Введите стипендию студента: "; cin >> new_student.data.value.scholarship;
			cout << "Введите телефонный номер студента (по нему в списках идентифицируются студенты): "; cin >> new_student.data.value.phoneNumber;
			Flow.add(new_student.data.value.groupNumber, new_student);
			cout << "Студент успешно введен в поток.\n";
			new_student.clear();
			break;
		}
		case 2: {
			cout << "Введите группу студента: ";
			cin >> group;
			cout << "Введите номер телефона удаляемого студента: ";
			cin >> number;
			Flow.remove(number, group);
			cout << "Студент успешно удален.\n";
			break;
		}
		case 3: {
			cout << "Введите группу студента: ";
			cin >> group;
			cout << "Введите номер телефона редактируемого студента: ";
			cin >> number;
			cout << "\tВвод обновленной информации о студенте\n";
			cout << "(если хотите просто перевести студента из одной группы в другую,\n просто измените номер группы, и введите старые данные)\n";
			cout << "Введите обновленный номер группы: "; cin >> new_student.data.value.groupNumber;
			cout << "Введите обновленные оценки студента:\n"; for (int i = 0; i < 5; i++) { cout << i << ") "; cin >> new_student.data.value.arr[i]; }
			cout << "Введите обновленную стипендию студента: "; cin >> new_student.data.value.scholarship;
			cout << "Введите обновленный телефонный номер студента (по нему в списках идентифицируются студенты): "; cin >> new_student.data.value.phoneNumber;
			if (new_student.data.value.groupNumber == group) {
				Flow.updateStudent(new_student, number, group); 
				cout << "Данные успешно изменены.\n";
			}
			else {
				Flow.add(new_student.data.value.groupNumber, new_student);
				Flow.remove(number, group);
				cout << "Обновленный студент успешно переведен.\n";
			}
			new_student.clear();
			break;
		}
		case 4: {
			cout << "Введите группу студента: ";
			cin >> group;
			cout << "Введите номер телефона просматриваемого студента: ";
			cin >> number;
			Student* student_info = Flow.arr[Flow.hashFoo(group)].look_for_node_without_access(Student(Pair(group, number)));
			cout << "ФИО: " << student_info->data.key;
			cout << " Оценки: "; for (int i = 0; i < 5; i++) { cout << " " << student_info->data.value.arr[i] << " "; };
			cout << " Стипендия: " << student_info->data.value.scholarship << " рублей.\n";
			break;
		}
		case 5: {
			Student* array = Flow.toArray();
			Student_output(static_cast<int>(Flow.element_count), array);
			break;
		}
		case 6: {
			cout << "Общее количество студентов: " << Flow.count() << endl; break;
		}
		case 7: {
			cout << "Введите номер удаляемой группы: ";
			cin >> group;
			Flow.arr[Flow.hashFoo(group)].clear();
			cout << "Группа успешно удалена.\n";
			break;
		}
		case 8: {
			string newGroup;
			cout << "Введите номер редактируемой группы: ";
			cin >> group;
			cout << "Введите новый номер группы: ";
			cin >> newGroup;
			Flow.arr[Flow.hashFoo(group)].groupNumber = newGroup;
			cout << "Номер группы успешно отредактирован.\n";
			break;
		}
		case 9: {
			cout << "Введите номер интересующей группы: ";
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
			{ cout << "Группа: " << group_grades[i].group << ", Средний балл: " << group_grades[i].grade << endl; } 
			delete[] group_grades;
			break;
		}
		case 11: { 
			int group_cnt = Flow.get_count_of_groups();
			Pair_for_sort* group_grades = Flow.arrayOfAverageGrades();
			mergeSort(group_grades, 0, group_cnt - 1);
			cout << "Группа с наибольшим баллом " << group_grades[0].group << ", ее бал составляет " << group_grades[0].grade << ".\n"; 
			delete[] group_grades;
			break; 
		}
		case 12: {
			string filename;
			cout << "Введите имя файла txt в директории: ";
			cin >> filename;
			ifstream inFile(filename);
			if (!inFile.is_open()) { cerr << "Не удалось открыть файл для чтения.\n"; }
			else {
				string line;
				Flow.clear();
				while (getline(inFile, line)) {
					istringstream iss(line);
					string token;
					getline(iss, token, ':'); // пропуск ФИО
					getline(iss, new_student.data.key, '|'); 
					new_student.data.key.erase(0, 1); // удаление пробела в начале имени
					getline(iss, token, ':'); // Пропуск Телефона
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
			if (!outFile.is_open()) { cerr << "Не удалось открыть файл\n"; break; }
			Student* array = Flow.toArray();
			for (int i = 0; i < Flow.element_count; i++) {
				outFile << "ФИО: " << array[i].data.key << " | ";
				outFile << "Телефон: " << array[i].data.value.phoneNumber << " | ";
				outFile << "Группа: " << array[i].data.value.groupNumber << " | ";
				outFile << "Оценки: ";
				for (int j = 0; j < 5; j++) { outFile << array[i].data.value.arr[j] << " "; }
				outFile << "| Стипендия: " << array[i].data.value.scholarship << " рублей.n";
				outFile.close();
				delete[] array;
			}
			break;
		}
		}
		
	} while (choice != 13);
	return 0;
}