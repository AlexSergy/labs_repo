#include<iostream>
#include<cstdlib> // для exit()
#include"Queue.cpp"
using namespace std;


int main() {
	setlocale(LC_ALL, "ru");
	Queue Q;
	int choice, value;

	cout << "\nОперации с очередью\n";
	cout << "1 - Ввести переменные\n2 - Изъять 'старейшую' переменную\n3 - Посчитать длину списка\n";
	cout << "4 - Вставить перед каждым отр. числом '1'\n5 - Убрать все отрицательные числа\n6 - Найти количество вхождений определенной переменной\n7 - Отчистить очередь\n8 - Выйти\n";


	while (true) {
		cout << "Выберите команду (1-8): ";
		cin >> choice;
		switch (choice) {
		case 1:
			while (true) {
				cout << "Введите свою переменную (чтобы перестать вводить, введите 0): ";
				cin >> value;
				if (value == 0) { break; }
				Q.queue(value);
			}
			break;
		case 2:
			value = Q.unqueue();
			if (value != -1) { cout << "Извлеченная переменная: " << value << endl; }
			else { cout << "Очередь пуста.\n"; }
			break;
		case 3:
			cout << "Длина очереди: " << Q.count() << endl;
			break;
		case 4:
			Q.insertBeforeNegative();
			cout << "Операция прошла успешно!\n";
			break;
		case 5:
			Q.removeNegative();
			cout << "Отр. числа успешно удалены\n";
			break;
		case 6:
			cout << "Введите, какое число вы хотите посчитать: ";
			cin >> value;
			cout << "Число " << value << " встречается " << Q.count(value) << " раз(а).\n";
			break;
		case 7:
			Q.clear();
			cout << "Очередь очищена.\n";
			break;
		case 8:
			Q.clear();
			exit(0);
		default:
			cout << "Ошибка. Введите корректное значение." << endl;
		}
	}
}