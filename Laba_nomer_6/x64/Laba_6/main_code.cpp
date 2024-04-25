#include<iostream>
#include"Tree.hpp"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	Tree Tree;
	int choice, value;


	cout << "\nОПЕРАЦИИ С БИНАРНЫМ ДЕРЕВОМ ПОИСКА.\n";
	cout << "1 - добавить элемент в дерево.\n";
	cout << "2 - удалить элемент из дерева.\n";
	cout << "3 - проверить наличие элемента в дереве.\n";
	cout << "4 - получить количество элементов в дереве.\n";
	cout << "5 - очистить дерево.\n";
	cout << "Любое другое число - выйти.\n";


	while (true) {
		cout << "Введите операцию: ";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Введите значение для добавления: ";
			cin >> value;
			Tree.add(value);
			break;
		case 2:
			cout << "Введите значение для удаления: ";
			cin >> value;
			Tree.remove(value);
			break;
		case 3:
			cout << "Введите значение для поиска: ";
			cin >> value;
			if (Tree.contains(value)) { cout << "Значение найдено в дереве.\n"; }
			else { cout << "Значение не найдено в дереве.\n"; }
			break;
		case 4:
			cout << "Кол-во элементов в дереве: " << Tree.count() << "\n";
			break;
		case 5:
			Tree.clear();
			cout << "Дерево очищено.\n";
			break;
		default: return 0;
		}
	}
	return 0;
}