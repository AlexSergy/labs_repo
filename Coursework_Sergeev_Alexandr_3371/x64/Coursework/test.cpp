#include <fstream>
#include<iostream>
#include <vector>
#include <string>
#include "Flow.hpp"
#include "Student.hpp"
#include "Students_data.hpp"
#include "Info.hpp"
#include "Group.hpp"
#include <array>

void Student_output(int count, Student* array) {
    for (int i = 0; i < count; i++) {
        cout << "ФИО: " << array[i].data.key << " | ";
        cout << " Телефон: " << array[i].data.value.phoneNumber << " | ";
        cout << " Группа: " << array[i].data.value.groupNumber << " | ";
        cout << " Оценки: "; for (int j = 0; j < 5; j++) { cout << " " << array[i].data.value.arr[j] << " "; } cout << " | ";
        cout << " Стипендия: " << array[i].data.value.scholarship << " рублей.\n";
    }
}

void merge(Pair_for_sort*& arr, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    Pair_for_sort* L = new Pair_for_sort[n1];
    Pair_for_sort* R = new Pair_for_sort[n2];

    // копируем все в временные массивы
    for (int i = 0; i < n1; i++) { L[i] = arr[left + i]; }
    for (int j = 0; j < n2; j++) { R[j] = arr[middle + 1 + j]; }

    // Сливаем временные массивы обратно
    int i = 0, j = 0, k = 0;
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


void CreateTestStudents(Flow& flow) {
    vector<Student> testStudents{
        std::initializer_list<Student>{
            {"Michael Lee", "CS101", {{4, 3, 4, 4, 5}}, 1000, "+9998887777"},
            {"Sarah Taylor", "CS103", {{5, 5, 5, 4, 4}}, 1300, "+6665554444"},
            {"David Miller", "CS102", {{4, 4, 4, 5, 5}}, 1200, "+2223334444"},
            {"Jessica Chen", "CS101", {{5, 4, 4, 3, 4}}, 1100, "+7778889999"},
            {"John Doe", "CS101", {{5, 4, 3, 4, 5}}, 1000, "+1234567890"},
            {"Jane Smith", "CS101", {{4, 5, 4, 3, 5}}, 1200, "+0987654321"},
            {"Bob Johnson", "CS102", {{5, 5, 4, 4, 5}}, 1500, "+5551234567"},
            {"Alice Brown", "CS101", {{4, 4, 5, 4, 4}}, 1100, "+1112223333"},
            {"Tom Wilson", "CS103", {{3, 4, 4, 3, 5}}, 900, "+9876543210"},
            {"Emily Davis", "CS102", {{5, 4, 5, 5, 4}}, 1400, "+0123456789"},
            {"William Smith", "CS104", {{4, 3, 5, 4, 4}}, 1200, "+2345678901"},
            {"Olivia Johnson", "CS102", {{5, 5, 4, 5, 4}}, 1400, "+3456789012"},
            {"James Brown", "CS101", {{4, 4, 4, 4, 5}}, 1100, "+4567890123"},
            {"Sophia Davis", "CS103", {{5, 4, 5, 4, 5}}, 1300, "+5678901234"},
            {"Daniel Wilson", "CS104", {{3, 4, 4, 4, 3}}, 900, "+6789012345"},
            {"Emma Miller", "CS102", {{5, 5, 5, 4, 4}}, 1500, "+7890123456"},
            {"Jacob Taylor", "CS101", {{4, 4, 3, 5, 5}}, 1100, "+8901234567"},
            {"Ava Anderson", "CS103", {{5, 4, 5, 4, 4}}, 1200, "+9012345678"},
            {"Michael Thomas", "CS104", {{4, 4, 4, 3, 5}}, 1000, "+0123456789"},
            {"Abigail Jackson", "CS102", {{5, 5, 4, 5, 5}}, 1400, "+1234567890"},
            {"Matthew White", "CS101", {{4, 3, 4, 4, 4}}, 1000, "+2345678901"},
            {"Isabella Harris", "CS103", {{5, 5, 5, 4, 5}}, 1400, "+3456789012"},
            {"Joshua Garcia", "CS104", {{4, 4, 4, 4, 3}}, 900, "+4567890123"},
            {"Mia Martinez", "CS102", {{5, 4, 5, 5, 5}}, 1500, "+5678901234"},
            {"Andrew Robinson", "CS101", {{4, 4, 3, 4, 4}}, 1000, "+6789012345"},
            {"Sophia Hernandez", "CS103", {{5, 5, 5, 4, 4}}, 1300, "+7890123456"},
            {"Daniel Clark", "CS104", {{3, 4, 4, 4, 4}}, 1000, "+8901234567"},
            {"Emily Rodriguez", "CS102", {{5, 4, 5, 4, 5}}, 1400, "+9012345678"},
            {"Matthew Lewis", "CS101", {{4, 4, 4, 4, 4}}, 1100, "+0123456789"},
            {"Ava Walker", "CS103", {{5, 5, 4, 5, 4}}, 1200, "+1234567890"},
        }
    };

    for (const auto& student : testStudents) {
        flow.add(student.data.value.groupNumber, student);
    }
}

void SaveStudentsToFile(Flow& flow, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        Student* students = flow.toArray();
        for (int i = 0; i < flow.count(); i++) {
            outFile << "ФИО: " << students[i].data.key << " | ";
            outFile << "Телефон: " << students[i].data.value.phoneNumber << " | ";
            outFile << "Группа: " << students[i].data.value.groupNumber << " | ";
            outFile << "Оценки: ";
            for (int j = 0; j < 5; j++) {
                outFile << students[i].data.value.arr[j] << " ";
            }
            outFile << "| Стипендия: " << students[i].data.value.scholarship << " рублей.\n";
        }
        delete[] students;
        outFile.close();
    }
    else {
        cerr << "Не удалось открыть файл " << filename << " для записи.\n";
    }
}

int main() {
    Flow flow;
    CreateTestStudents(flow);
    SaveStudentsToFile(flow, "students_of_flow.txt");
    // Остальной код...
    return 0;
}