#include "List.hpp"
#include "simple_map.hpp"
#include <iostream>
#include <string>

void print_menu() {
    cout << "\n�������� � ��������\n";
    cout << "1. �������� �����\n";
    cout << "2. �������� ����� �� ������.\n";
    cout << "3. ������� ����� �� ������.\n";
    cout << "4. ����������, ����� � ������ �������.\n";
    cout << "5. ������� ���������� �������.\n";
    cout << "\n�������� � ���������\n";
    cout << "6. ������� ������� � ������� �������� ���������\n";
    cout << "7. ������� ������ ���������� �������\n";
    cout << "8. �������� ������ ������� (������ � ��� ��������� ������ ��������).\n";
    cout << "9. ��������� ���������\n";
    cout << "\n����������: ������ ������� ����������� ���������! ���������� � ����!\n";
}

struct City {
    string name;
    string region;
    int population;

    City() {}
    City(const string& region) : region(region) {}
    bool operator==(const City& other) const { return region == other.region; }
};

void removeCitiesByRegion(List<City>& cities, simple_map<string, int>& regions, const string& region) {
    regions.remove(region);
    City searchReg(region); /* 
    ��������� ����� �� ������ �������, ��� ��� ��� �����, 
    �� ��� ��, ��� ������� ����� � ��� �������� ��������� */
    while (cities.look_for(searchReg)) { cities.del_element(searchReg); }
}

void printSortedRegions(simple_map<string, int>& regions) {
    Pair<string, int>* regionsArr = regions.hashset.toArray();
    int count = regions.hashset.count();
    regions.mergeSort(regionsArr, 0, count - 1);
    for (int i = 0; i < count; i++) { cout << "������: " << regionsArr[i].key << ", ���������: " << regionsArr[i].value << endl; }
    delete[] regionsArr;
}

void fail() {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), 'n'); 
    cout << "������������ ����. ���������� ��� ���." << endl;
}

int main() {
    setlocale(LC_ALL, "ru");
    List<City> cities;
    simple_map<string, int> regions;
    int choice;
    City new_city;
    int index = 0;


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
        case 2:
            cout << "������� �����, ��� ������� �������� �����:";
            cin >> index;
            if (cin.fail() || index < 0 || index > cities.count()) { fail(); }
            else {
                cout << "\n������� �������� ������: ";
                cin >> new_city.name;
                cout << "������� �������� �������: ";
                cin >> new_city.region;
                cout << "������� ���������� �������: ";
                cin >> new_city.population;
                cities.insert(index, new_city);
                regions.insert(new_city.region, new_city.population);
            }
            break;
        case 3:
            cout << "������� �����, ��� ������� ������ ������� �����: ";
            cin >> index;
            if (cin.fail() || index < 0 || index > cities.count()) { fail(); }
            else {
                const Node<City>& Node = cities.elementAt(index);
                regions.remove_population(Node.data.region, Node.data.population);
                cities.removeAt(index);
            }
            break;
        case 4: {
            cout << "������� �����, ��� ������� ������ ���������� �����: ";
            cin >> index;
            if (cin.fail() || index < 0 || index > cities.count()) { fail(); }
            else {
                City& city = cities.elementAt(index);
                cout << "��������: " << city.name << ", ������: " << city.region << ", ���������: " << city.population << endl;
            }
            break;
        }
        case 5: {
            cout << "������� ���������� �������: " << cities.count() << endl;
            break;
        }
        case 6: {
            printSortedRegions(regions);
            break;
        }
        case 7: {
            string reg;
            cout << "�������� �������� �������: ";
            cin >> reg;
            removeCitiesByRegion(cities, regions, reg);
            break;
        }
        case 8: {
            cities.clear(); 
            regions.hashset.clear();
            cout << "������ ������� � �������� ������." << endl;
            break;
        }
        case 9: { return 0; }
        default: { 
            cout << "\n������������ ����, ���������� ��� ���\n";
            break;
        }
        }
    }
}
