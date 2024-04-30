#include<iostream>
#include"HashSet.hpp"
#include<string>
#include<limits> // для обработки некорректного ввода

using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    HashSet hashSet;
    int choice;
    string value;

    cout << "\nОперации с хеш-таблицей\n";
    cout << "1 - Добавить слово в хеш-таблицу.\n";
    cout << "2 - Удалить слово из хеш-таблицы.\n";
    cout << "3 - Проверить, содержится ли слово в хеш-таблице.\n";
    cout << "4 - Узнать количество слов в хеш-таблице.\n";
    cout << "5 - Очистить хеш-таблицу.\n";
    cout << "6 - Вывести все слова из хеш-таблицы.\n";
    cout << "Любое другое число - Выйти\n" << endl;

    while (true) {
        cout << "Выберите команду: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Некорректный ввод, попробуйте еще раз.\n";
            continue;
        }

        switch (choice) {
        case 1:
            cout << "Введите слово для добавления: ";
            cin >> value;
            hashSet.add(value);
            break;
        case 2:
            cout << "Введите слово для удаления: ";
            cin >> value;
            hashSet.remove(value);
            break;
        case 3:
            cout << "Введите слово для проверки: ";
            cin >> value;
            if (hashSet.contains(value)) {
                cout << "Слово найдено.\n";
            }
            else {
                cout << "Слово не найдено.\n";
            }
            break;
        case 4:
            cout << "Количество слов: " << hashSet.count() << "\n";
            break;
        case 5:
            hashSet.clear();
            cout << "Таблица очищена.\n";
            break;
        case 6: {
            int count = hashSet.count();
            auto wordsArr = hashSet.ToArray();
            cout << "Слова в хеш-таблице: ";
            for (int i = 0; i < count; ++i) {
                cout << wordsArr[i] << (i < count - 1 ? ", " : ".");
            }
            cout << "\n";
            delete[] wordsArr; // очистка памяти после использования
            break;
        }
        default:
            cout << "Выход из программы.\n";
            return 0;
        }
    }
}
