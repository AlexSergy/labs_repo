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

    // Добавление элементов
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // Проверка содержания элементов
    EXPECT_TRUE(set.contains("apple"));
    EXPECT_TRUE(set.contains("banana"));
    EXPECT_TRUE(set.contains("cherry"));
    EXPECT_FALSE(set.contains("orange"));

    // Удаление элементов
    set.remove("banana");
    EXPECT_FALSE(set.contains("banana"));

    // Добавление существующего элемента
    set.add("apple");
    EXPECT_TRUE(set.contains("apple"));
}

TEST(HashSetTest, CountAndClear) {
    HashSet set;

    // Проверка count() для пустого набора
    EXPECT_EQ(set.count(), 0);

    // Добавление элементов
    set.add("apple");
    set.add("banana");
    set.add("cherry");
    set.add("date");

    // Проверка count() после добавления
    EXPECT_EQ(set.count(), 4);

    // Очистка набора
    set.clear();
    EXPECT_EQ(set.count(), 0);

    // Добавление элементов после очистки
    set.add("grape");
    set.add("kiwi");
    EXPECT_EQ(set.count(), 2);
}

TEST(HashSetTest, ToArray) {
    HashSet set;

    // Проверка ToArray() для пустого набора
    string* empty_array = set.ToArray();
    EXPECT_EQ(empty_array, nullptr);
    delete[] empty_array;

    // Добавление элементов
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // Проверка ToArray() после добавления
    string* array = set.ToArray();
    EXPECT_NE(array, nullptr);

    // Проверка содержимого массива
    std::vector<string> expected = { "apple", "banana", "cherry" };
    std::vector<string> actual(array, array + set.count());
    std::sort(actual.begin(), actual.end());
    EXPECT_EQ(actual, expected);

    delete[] array;
}

TEST(HashSetTest, AddDuplicates) {
    HashSet set;

    // Добавление повторяющихся элементов
    set.add("apple");
    set.add("banana");
    set.add("cherry");
    set.add("apple");
    set.add("banana");

    // Проверка количества элементов
    EXPECT_EQ(set.count(), 3);

    // Проверка содержания элементов
    EXPECT_TRUE(set.contains("apple"));
    EXPECT_TRUE(set.contains("banana"));
    EXPECT_TRUE(set.contains("cherry"));
}

TEST(HashSetTest, RemoveNonExistingElement) {
    HashSet set;

    // Добавление элементов
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // Удаление несуществующего элемента
    set.remove("orange");

    // Проверка количества элементов
    EXPECT_EQ(set.count(), 3);

    // Проверка содержания элементов
    EXPECT_TRUE(set.contains("apple"));
    EXPECT_TRUE(set.contains("banana"));
    EXPECT_TRUE(set.contains("cherry"));
}

TEST(HashSetTest, ClearAndAdd) {
    HashSet set;

    // Добавление элементов
    set.add("apple");
    set.add("banana");
    set.add("cherry");

    // Очистка набора
    set.clear();
    EXPECT_EQ(set.count(), 0);

    // Добавление новых элементов
    set.add("grape");
    set.add("kiwi");
    set.add("lemon");

    // Проверка количества элементов
    EXPECT_EQ(set.count(), 3);

    // Проверка содержания элементов
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

    // Добавление большого количества элементов
    for (int i = 0; i < numElements; i++) {
        set.add(std::to_string(i));
    }

    // Проверка количества элементов
    EXPECT_EQ(set.count(), numElements);

    // Проверка содержания случайных элементов
    std::vector<int> randomIndices = { 42, 7890, 3333, 9999 };
    for (int index : randomIndices) {
        EXPECT_TRUE(set.contains(std::to_string(index)));
    }

    // Удаление половины элементов
    for (int i = 0; i < numElements / 2; i++) {
        set.remove(std::to_string(i));
    }

    // Проверка количества оставшихся элементов
    EXPECT_EQ(set.count(), numElements / 2);

    // Добавление новых элементов после удаления
    for (int i = numElements; i < numElements + 100; i++) {
        set.add(std::to_string(i));
    }

    // Проверка количества элементов после добавления
    EXPECT_EQ(set.count(), numElements / 2 + 100);
}

TEST(HashSetTest, StressTest) {
    HashSet set;
    const int numOperations = 10000;
    const int maxValue = 1000;
    std::vector<int> values;

    // Выполнение большого количества операций добавления и удаления
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

    // Проверка содержания элементов после стресс-теста
    for (int value : values) {
        EXPECT_TRUE(set.contains(std::to_string(value)));
    }

    // Проверка количества элементов
    EXPECT_EQ(set.count(), values.size()/2);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}