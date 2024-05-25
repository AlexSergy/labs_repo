#include <gtest/gtest.h>
#include <random>
#include <chrono>
#include <algorithm>
#include <unordered_set>
#include "HashSet.hpp"
#include <vector>
#include<array>

TEST(HashSetTest, AddRemoveContains) {
    HashSet set;

    // ���������� ���������
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // �������� ���������� ���������
    EXPECT_TRUE(set.contains("apple"));
    EXPECT_TRUE(set.contains("banana"));
    EXPECT_TRUE(set.contains("cherry"));
    EXPECT_FALSE(set.contains("orange"));

    // �������� ���������
    set.remove("banana");
    EXPECT_FALSE(set.contains("banana"));

    // ���������� ������������� ��������
    set.add("apple");
    EXPECT_TRUE(set.contains("apple"));
}

TEST(HashSetTest, CountAndClear) {
    HashSet set;

    // �������� count() ��� ������� ������
    EXPECT_EQ(set.count(), 0);

    // ���������� ���������
    set.add("apple");
    set.add("banana");
    set.add("cherry");
    set.add("date");

    // �������� count() ����� ����������
    EXPECT_EQ(set.count(), 4);

    // ������� ������
    set.clear();
    EXPECT_EQ(set.count(), 0);

    // ���������� ��������� ����� �������
    set.add("grape");
    set.add("kiwi");
    EXPECT_EQ(set.count(), 2);
}

TEST(HashSetTest, ToArray) {
    HashSet set;

    // �������� ToArray() ��� ������� ������
    string* empty_array = set.ToArray();
    EXPECT_EQ(empty_array, nullptr);
    delete[] empty_array;

    // ���������� ���������
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // �������� ToArray() ����� ����������
    string* array = set.ToArray();
    EXPECT_NE(array, nullptr);

    // �������� ����������� �������
    std::vector<string> expected = { "apple", "banana", "cherry" };
    std::vector<string> actual(array, array + set.count());
    std::sort(actual.begin(), actual.end());
    EXPECT_EQ(actual, expected);

    delete[] array;
}

TEST(HashSetTest, AddDuplicates) {
    HashSet set;

    // ���������� ������������� ���������
    set.add("apple");
    set.add("banana");
    set.add("cherry");
    set.add("apple");
    set.add("banana");

    // �������� ���������� ���������
    EXPECT_EQ(set.count(), 3);

    // �������� ���������� ���������
    EXPECT_TRUE(set.contains("apple"));
    EXPECT_TRUE(set.contains("banana"));
    EXPECT_TRUE(set.contains("cherry"));
}

TEST(HashSetTest, RemoveNonExistingElement) {
    HashSet set;

    // ���������� ���������
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // �������� ��������������� ��������
    set.remove("orange");

    // �������� ���������� ���������
    EXPECT_EQ(set.count(), 3);

    // �������� ���������� ���������
    EXPECT_TRUE(set.contains("apple"));
    EXPECT_TRUE(set.contains("banana"));
    EXPECT_TRUE(set.contains("cherry"));
}

TEST(HashSetTest, ClearAndAdd) {
    HashSet set;

    // ���������� ���������
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // ������� ������
    set.clear();
    EXPECT_EQ(set.count(), 0);

    // ���������� ����� ���������
    set.add("grape");
    set.add("kiwi");
    set.add("lemon");

    // �������� ���������� ���������
    EXPECT_EQ(set.count(), 3);

    // �������� ���������� ���������
    EXPECT_TRUE(set.contains("grape"));
    EXPECT_TRUE(set.contains("kiwi"));
    EXPECT_TRUE(set.contains("lemon"));
    EXPECT_FALSE(set.contains("apple"));
    EXPECT_FALSE(set.contains("banana"));
    EXPECT_FALSE(set.contains("cherry"));
}


TEST(HashSetTest, LargeDataSet) {
    HashSet set;
    const int numElements = 10000;

    // ���������� �������� ���������� ���������
    for (int i = 0; i < numElements; i++) {
        set.add(std::to_string(i));
    }

    // �������� ���������� ���������
    EXPECT_EQ(set.count(), numElements);

    // �������� ���������� ��������� ���������
    std::vector<int> randomIndices = { 42, 7890, 3333, 9999 };
    for (int index : randomIndices) {
        EXPECT_TRUE(set.contains(std::to_string(index)));
    }

    // �������� �������� ���������
    for (int i = 0; i < numElements / 2; i++) {
        set.remove(std::to_string(i));
    }

    // �������� ���������� ���������� ���������
    EXPECT_EQ(set.count(), numElements / 2);

    // ���������� ����� ��������� ����� ��������
    for (int i = numElements; i < numElements + 100; i++) {
        set.add(std::to_string(i));
    }

    // �������� ���������� ��������� ����� ����������
    EXPECT_EQ(set.count(), numElements / 2 + 100);
}

TEST(HashSetTest, StressTest) {
    HashSet set;
    const int numOperations = 10000;
    const int maxValue = 1000;
    std::vector<int> values;

    // ���������� �������� ���������� �������� ���������� � ��������
    for (int i = 0; i < numOperations; i++) {
        int value = rand() % maxValue;
        if (rand() % 2 == 0) {
            set.add(std::to_string(value));
            values.push_back(value);
        }
        else {
            set.remove(std::to_string(value));
            values.erase(std::remove(values.begin(), values.end(), value), values.end());
        }
    }

    // �������� ���������� ��������� ����� ������-�����
    for (int value : values) {
        EXPECT_TRUE(set.contains(std::to_string(value)));
    }

    // �������� ���������� ���������
    EXPECT_EQ(set.count(), values.size()/2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}