#include <gtest/gtest.h>
#include "Tree.hpp"
#include <algorithm>
#include<numeric>

TEST(TreeTest, ClearEmptyTree) {
    Tree t;
    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearSingleNodeTree) {
    Tree t;
    t.add(42);
    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearComplexTree) {
    Tree t;
    vector<int> values = { 50, 30, 20, 40, 70, 60, 80 };
    for (int value : values) {
        t.add(value);
    }

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearAndReuse) {
    Tree t;
    vector<int> values1 = { 50, 30, 20, 40, 70, 60, 80 };
    for (int value : values1) {
        t.add(value);
    }

    t.clear();

    vector<int> values2 = { 25, 75, 10, 35, 65, 90 };
    for (int value : values2) {
        t.add(value);
    }

    int* arr = t.ToArray();
    vector<int> expected = { 10, 25, 35, 65, 75, 90 };
    for (int i = 0; i < t.size; i++) {
        EXPECT_EQ(arr[i], expected[i]);
    }
    delete[] arr;
}
TEST(TreeTest, ClearAfterRotations) {
    Tree t;
    vector<int> values = { 50, 30, 70, 20, 40, 60, 80 };
    for (int value : values) {
        t.add(value);
    }

    // Выполняем некоторые повороты
    t.ToLeft(30);
    t.ToRight(70);
    t.ToLeft(40);

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearAfterBalancing) {
    Tree t;
    vector<int> values = { 50, 25, 75, 10, 30, 60, 90, 5, 15, 28, 35, 55, 65, 85, 95 };
    for (int value : values) {
        t.add(value);
    }

    // Балансируем дерево
    t.Balance();

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearWithDuplicates) {
    Tree t;
    vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 30, 40, 60 };
    for (int value : values) {
        t.add(value);
    }

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearWithRecursiveStructure) {
    Tree t;
    vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 15, 25, 35, 45, 55, 65, 75, 85 };
    for (int value : values) {
        t.add(value);
    }

    // Создаем рекурсивную структуру внутри дерева
    t.ToLeft(20);
    t.ToRight(40);
    t.ToLeft(60);
    t.ToRight(80);

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearWithLargeTree) {
    Tree t;
    vector<int> values(10000);
    iota(values.begin(), values.end(), 0); // Заполняем вектор значениями от 0 до 99999
    random_shuffle(values.begin(), values.end()); // Перемешиваем значения

    for (int value : values) {
        t.add(value);
    }

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, ClearWithMultipleOperations) {
    Tree t;
    vector<int> values = { 50, 30, 70, 20, 40, 60, 80, 10, 25, 35, 45, 55, 65, 75, 85 };
    for (int value : values) {
        t.add(value);
    }

    // Выполняем несколько операций над деревом
    t.ToLeft(30);
    t.ToRight(70);
    t.remove(50);
    t.add(90);
    t.Balance();

    t.clear();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}