#include "List.hpp"
#include "simple_map.hpp"
#include <iostream>
#include<string>

void print_menu() {
    cout << "\n1. �������� �����\n";
    cout << "2. ������� ������� � ������� �������� ���������\n";
    cout << "3. ������� ������ ���������� �������\n";
    cout << "4. �������� ������\n";
    cout << "5. ��������� ���������\n";
    cout << "\n����������: ������ ������� ����������� ���������!\n";
}

int main1() {
    setlocale(LC_ALL, "ru");
    List<City> cities;
    simple_map<string, int> regions;
    int choice;
    City new_city;

    print_menu();

    while (true) {
        cout << "\n������� �������: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\n������� �������� ������: ";
            cin >> new_city.name;
            cout << "������� �������� �������: ";
            cin >> new_city.region;
            cout << "������� ���������� �������: ";
            cin >> new_city.population;
            cities.add(new_city);
            regions.insert(new_city.region, new_city.population);
            break;
        }
        case 2: {
            regions.sort();
            simple_map<string, int>::Nodemap* cur = regions.head;
            while (cur != nullptr) {
                cout << "������: " << cur->key << ", ���������: " << cur->value << endl;
                cur = cur->next; // ��������� � ���������� ����
            }
            break;
        }
        case 3: {
            string region;
            cout << "\n������� �������� �������: ";
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
            cout << "\n������������ ����, ���������� ��� ���\n";
            break;
        }
        }
    }

    return 0;
}
