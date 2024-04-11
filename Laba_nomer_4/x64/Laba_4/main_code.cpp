#include "List.hpp"
#include "simple_map.hpp"
#include <iostream>
#include<string>

void print_menu() {
    cout << "\n1. Добавить город\n";
    cout << "2. Вывести регионы в порядке убывания населения\n";
    cout << "3. Удалить города указанного региона\n";
    cout << "4. Очистить список\n";
    cout << "5. Закончить программу\n";
    cout << "\nПримечание: строки вводите английскими символами!\n";
}

int main1() {
    setlocale(LC_ALL, "ru");
    List<City> cities;
    simple_map<string, int> regions;
    int choice;
    City new_city;

    print_menu();

    while (true) {
        cout << "\nВведите команду: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\nВведите название города: ";
            cin >> new_city.name;
            cout << "Введите название региона: ";
            cin >> new_city.region;
            cout << "Введите количество жителей: ";
            cin >> new_city.population;
            cities.add(new_city);
            regions.insert(new_city.region, new_city.population);
            break;
        }
        case 2: {
            regions.sort();
            simple_map<string, int>::Nodemap* cur = regions.head;
            while (cur != nullptr) {
                cout << "Регион: " << cur->key << ", население: " << cur->value << endl;
                cur = cur->next; // переходим к следующему узлу
            }
            break;
        }
        case 3: {
            string region;
            cout << "\nВведите название региона: ";
            cin >> region;
            cities.removeCitiesByRegion(region); 
            regions.remove(region); 
            break;
        }
        case 4: {
            cities.clear();
            regions.clear();
            break;
        }
        case 5: { return 0; }

        default:{ 
            cout << "\nНекорректный ввод, попробуйте еще раз\n";
            break;
        }
        }
    }

    return 0;
}
