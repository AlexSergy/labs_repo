#pragma once
#include"Group.hpp"
#include"Info.hpp"
#include"Students_data.hpp"
#include"Student.hpp"
#include<memory>
#include<sstream> // Чтобы любой тип мог преобразовываться в str.


using namespace std;


struct Pair_for_sort {
	string first;
	float second;

	Pair_for_sort() : first(), second() {}
	Pair_for_sort(const string& key, const float& value) : first(key), second(value) {}

	Pair_for_sort& operator=(const Pair_for_sort& other) { first = other.first; second = other.second; return *this; }
};


class Flow {
public:
	size_t size;
	Group* arr;
	float load_factor;
	int element_count;

	Group& operator[](int index) {
		if (index > size) { throw out_of_range("Ошибка индекса."); } // На всякий случай
		return arr[index];
	}

	Flow(size_t initial_size = 25) : size(initial_size), load_factor(0.75), element_count(0) { arr = new Group[size]; }
	~Flow() {
		clear();
		delete[] arr;
	}

	// по умолчанию преобразовываем все возможные данные в str
	// затем от них берем hash
	int hashFoo(const string& key) {
		ostringstream oss;
		oss << key; // полагаем, что для T определен operator<<
		string valueStr = oss.str();
		int hash = 0;
		for (char c : valueStr) { hash = (hash * 31 + c); }
		return (hash % size);
	}

	void resize() {
		size_t new_size = size * 2;
		Group* new_arr = new Group[new_size];
		size_t old_size = size;
		size = new_size;
		for (size_t i = 0; i < old_size; i++) {
			for (Student* node = arr[i].head; node != nullptr; node = node->next) {
				new_arr[hashFoo(node->data.value.groupNumber)].add(*node);
			}
		}
		delete[] arr;
		arr = new_arr;
	}

	void add(const string& groupNumber, const Student student) {
		size_t index = hashFoo(groupNumber);
		if (arr[index].groupNumber != "0") {
			if (arr[index].groupNumber == student.data.value.groupNumber) {
				if (!arr[index].look_for(student)) { arr[index].add(student); }
				else throw logic_error("Ошибка: студент с таким номером телефона уже существует в группе.\nПожалуйста, проверьте правильность ввода и попробуйте еще раз добавить студента.\n");
			}
			else {
				resize();
				index = hashFoo(groupNumber);
				arr[index].add(student);
			}
		}
		else { arr[index].add(student); }
		if (static_cast<float>(get_count_of_groups()) / size >= load_factor) { resize(); } // This one's a little tricky, but I left it like this.
		element_count++;
	}

	void updateStudent(const Student& updateStudent, const string oldGroupNumber, const string oldNumber) {
		int index = hashFoo(oldGroupNumber);
		Student* oldStudent = nullptr;
		try { oldStudent = arr[index].look_for_node_without_access(Student(Pair(oldGroupNumber, oldNumber)));  }
		catch (const  runtime_error& a) { throw runtime_error("Студент не найден.\n"); }
		Student temp = *oldStudent;
		temp.prev = temp.next = nullptr;
		arr[index].remove(oldStudent);
		if (updateStudent.data.value.groupNumber != oldGroupNumber) { index = hashFoo(updateStudent.data.value.groupNumber); }
		if (arr[index].look_for(updateStudent)) {
			arr[index].add(temp);
			throw exception("Ошибка: студент с таким номером телефона уже существует в новой группе.\nПожалуйста, проверьте правильность ввода и попробуйте еще раз.\n");
		}
		else { arr[index].add(updateStudent); }
	}
		

	void remove(const string& number, const string& group) {
		Student student = Pair(group, number); int index = hashFoo(group);
		if (arr[index].look_for(student)) {
			arr[index].del_element(student);
			element_count--;
		}
	}

	bool contains(const string& key) {
		Pair pair(key, Info());
		return arr[hashFoo(pair.key)].look_for(pair);
	}

	int count() { return element_count; }

	void clear() {
		for (size_t i = 0; i < size; i++) { arr[i].clear(); }
		element_count = 0;
	}

	Student* toArray() {
		Student* students = new Student[count()];
		if (count() == 0) { return students; }
		int index = 0;
		for (int i = 0; i < size; i++) {
			if (arr[i].count() > 0) {
				Student* cur = arr[i].head;
				while (cur) { students[index++] = *cur; cur = cur->next; }
			}
		}
		return students;
	}

	Student* toArray(string group) {
		int index = hashFoo(group), i = 0;
		Student* students = new Student[arr[index].count()];
		if (arr[index].groupNumber == group) {
			Student* cur = arr[index].head;
			while (cur) { 
				students[i++] = *cur;
				cur = cur->next; 
			}
			return students;
		}
		else { throw logic_error("Group not found or group numbers do not match."); }
	}

	Pair_for_sort* arrayOfAverageGrades() {
		int j = 0, cnt = get_count_of_groups();
		Pair_for_sort* av_grades = new Pair_for_sort[cnt];
		for (int i = 0; i < size; i++) {
			if (arr[i].count() > 0) {
				av_grades[j].first = arr[i].groupNumber;
				av_grades[j++].second = arr[i].updateAverageScore();
			}
		}
		if (cnt == 0) return nullptr;
		return av_grades;
	}

	int get_count_of_groups() {
		int cnt = 0;
		for (int i = 0; i < size; i++) { cnt += arr[i].common_count == 0 ? 0 : 1; }
		return cnt;
	}

	Info& getValueForKey(const string key) { return arr[hashFoo(key)].look_for_node(Pair(key, Info())).data.value; }
};