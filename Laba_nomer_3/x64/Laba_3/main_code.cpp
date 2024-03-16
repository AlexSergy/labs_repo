#include<iostream>
#include<cstdlib>
#include"List.cpp"

using namespace std;

int main() {
	setlocale(LC_ALL, "ru");
	List L;
	int choice, value;

	cout << "\nОперации с циклическим односвязным списком\n";
	cout << "1 - Ввести переменные в конец списка.\n2 - Вставить элемент в i-ую позицию.\n3 - Удалить элемент с i-ой позицией.\n";
	cout << "4 - Узнать, что за элемент стоит на i-ом месте.\n5 - Узнать количество элементов в списке.\n6 - Вставить перед отр. элементами '1'.\n7 - Удалить отр. элементы.\n8 - Посчитать, сколько раз встречается некоторый элемент.\n";
	cout << "9 - Очистить коллекцию\nЛюбое другое число - Выйти\n" << endl;

	cout << "Примечание! Для 2-4 пунктов индексация начинается с 0!\n" << endl;


	while (true) {
		cout << "Выберите команду: ";
		cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите значение для добавления в конец списка (для завершения введите любое некорректное значение или неверный тип данных)\n";
            while (true) {
                cout << "Значение - ";
                if (!(cin >> value)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Выход в меню.\n";
                    break;
                }
                L.add(value);
            }
            break;
        case 2:
            cout << "Введите позицию для вставки элемента: ";
            int position;
            cin >> position;
            cout << "Введите значение элемента: ";
            cin >> value;
            L.insert(position, value);
            break;
        case 3:
            cout << "Введите позицию элемента для удаления: ";
            cin >> position;
            L.removeAt(position);
            break;
        case 4:
            cout << "Введите позицию элемента для получения: ";
            cin >> position;
            cout << "Элемент в позиции " << position << ": " << L.elementAt(position) << "\n";
            break;
        case 5:
            cout << "Количество элементов в списке: " << L.count() << "\n";
            break;
        case 6:
            L.insertBeforeNegative();
            cout << "Операция вставки 1 перед отрицательными элементами выполнена\n";
            break;
        case 7:
            L.removeNegative();
            cout << "Удаление отрицательных элементов выполнено\n";
            break;
        case 8:
            cout << "Введите значение для подсчета вхождений: ";
            cin >> value;
            cout << "Количество вхождений " << value << ": " << L.count(value) << "\n";
            break;
        case 9:
            L.clear();
            cout << "Список очищен\n";
            break;
        default:
            L.clear();
            exit(0);
        }
	}
}