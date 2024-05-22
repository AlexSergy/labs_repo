#pragma once
#include<string>
using namespace std;

template <size_t N>
struct Array {
    int data[N] = {};

    Array(int other_data[N]) { for (size_t i = 0; i < N; ++i) { data[i] = other_data[i]; }}
    Array() { for (size_t i = 0; i < N; ++i) { data[i] = int(); } }

    

    int& operator[](size_t index) { return data[index]; }
    const int& operator[](size_t index) const { return data[index]; }
    bool operator==(const Array& arr) {
        bool flag = true;
        for (int i = 0; i < N; i++) { if (data[i] != arr[i]) { flag = false; } }
        return flag;
    }
    int sum() const {
        int result = 0;
        for (size_t i = 0; i < N; i++) { result += data[i]; }
        return result;
    }

};

struct Info {
    string groupNumber;
    Array<5> arr;
    double scholarship;
    string phoneNumber;

    Info(const string& gr, const string& num) : groupNumber(gr), arr(), scholarship(0.0), phoneNumber(num) {}
    Info(const string& gN, const Array<5>& gr, const double& sc, const string& pN) : groupNumber(gN), arr(gr), scholarship(sc), phoneNumber(pN) {};
    // Just in case ↑
    Info() : groupNumber("0"), arr(), scholarship(0.0), phoneNumber("") {}

    Info& operator=(const Info& other) {
        groupNumber = other.groupNumber;
        arr = other.arr;
        scholarship = other.scholarship;
        phoneNumber = other.phoneNumber;
        return *this;
    }
    bool operator==(const Info& info) const { return  (info.phoneNumber == phoneNumber); }

    float average_grade() const { return  static_cast<float>(arr.sum()) / 5; }
    // Если понадобится, сделай геттеры и т.д.
};