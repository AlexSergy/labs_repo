#include <iostream>
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include "Tree.hpp" // Заголовочный файл для вашего класса Tree



void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool checkBalance(Tree& t) {
    int height = t.height(t.root);
    int maxHeight = 1.44 * log2(t.size + 1) + 1; // Максимальная высота для сбалансированного дерева
    return height <= maxHeight;
}

TEST(ToRightTest, BasicRotateRight) {
    Tree t;
    t.add(20);
    t.add(10);
    t.add(30);
    t.add(5);
    t.add(15);
    t.ToRight(20);  // Поворот относительно корня
    auto arr = t.ToArray(Tree::Order::Prefix);
    int expectedArray[5] = { 10, 5, 20, 15, 30 };
    for (int i = 0; i < t.count(); ++i) {
        ASSERT_EQ(arr[i], expectedArray[i]) << "Arrays differ at index " << i;
    }
    delete[] arr;
}



TEST(ToRightTest, ComplexRotateRight) {
    Tree t;

    // Создание сложного дерева
    t.add(20);
    t.add(10);
    t.add(5);
    t.add(3);
    t.add(7);
    t.add(15);
    t.add(13);
    t.add(17);
    t.add(40);
    t.add(30);
    t.add(25);
    t.add(35);
    t.add(50);
    t.add(45);
    t.add(55);

    // Поворот вправо от корневого узла
    t.ToRight(20);
    auto arr = t.ToArray(Tree::Order::Prefix);
    int expectedArrayRootRotate[15] = { 10, 5, 3, 7, 20, 15, 13, 17, 40, 30, 25, 35, 50, 45, 55 };
    for (int i = 0; i < t.count(); ++i) {
        ASSERT_EQ(arr[i], expectedArrayRootRotate[i]) << "Arrays differ at index " << i;
    }

    // Поворот вправо от не корневого узла (например, 40)
    t.ToRight(40);
    delete[] arr;
    arr = t.ToArray(Tree::Order::Prefix);
    int expectedArraySubNodeRotate[15] = { 10, 5, 3, 7, 20, 15, 13, 17, 30, 25, 40, 35, 50, 45, 55 };
    for (int i = 0; i < t.count(); ++i) {
        ASSERT_EQ(arr[i], expectedArraySubNodeRotate[i]) << "Arrays differ at index " << i;
    }

    // Поворот вправо от узла, который не имеет левого потомка (например, 3)
    t.ToRight(3);
    delete[] arr;
    arr = t.ToArray(Tree::Order::Prefix);
    // Узел 3 не имеет левого потомка, поэтому структура дерева не должна измениться
    for (int i = 0; i < t.count(); ++i) {
        ASSERT_EQ(arr[i], expectedArraySubNodeRotate[i]) << "Arrays should stay the same at index " << i;
    }

    delete[] arr;
}



TEST(TreeTest, BalanceEmptyTree) {
    Tree t;
    t.Balance();
    EXPECT_EQ(t.root, nullptr);
    EXPECT_EQ(t.size, 0);
}

TEST(TreeTest, BalanceUnbalancedTree) {
    Tree t;
    std::vector<int> arr = { 10, 5, 15, 3, 7, 12, 20, 1, 8, 6, 14, 18, 25 };
    for (int x : arr) {
        t.add(x);
    }
    t.Balance();
    EXPECT_TRUE(checkBalance(t));
}

TEST(TreeTest, BalanceAfterDeletions) {
    Tree t;
    std::vector<int> arr = { 10, 5, 15, 3, 7, 12, 20, 1, 8, 6, 14, 18, 25 };
    for (int x : arr) {
        t.add(x);
    }
    t.remove(15);
    t.remove(3);
    t.remove(7);
    t.Balance();
    EXPECT_TRUE(checkBalance(t));
}

TEST(TreeTest, BalanceAfterRotations) {
    Tree t;
    std::vector<int> arr = { 10, 5, 15, 3, 7, 12, 20, 1, 8, 6, 14, 18, 25 };
    for (int x : arr) {
        t.add(x);
    }
    t.ToLeft(15);
    t.ToRight(5);
    t.Balance();
    EXPECT_TRUE(checkBalance(t));
}

TEST(TreeTest, BalanceAfterInsertionsAndDeletions) {
    Tree t;
    std::vector<int> arr = { 8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15 };
    for (int x : arr) {
        t.add(x);
    }
    t.Balance();
    t.add(16);
    t.remove(4);
    t.Balance();
    EXPECT_TRUE(checkBalance(t));
}




// Тест для проверки балансировки
TEST(BalanceTest, TestBalance) {
    Tree t;

    // Создание специального тестового дерева, которое будет несбалансированным
    // Например, одностороннее дерево (цепочка):
    // 0 - 1 - 2 - 3 - 4 - 5 - ...
    for (int i = 0; i < 10; ++i) {
        t.add(i);
    }

    // Применяем балансировку
    t.Balance();

    // Проверяем, что разница в высотах между левым и правым поддеревьями корня не больше 1
    int leftHeight = t.height(t.root->l);
    int rightHeight = t.height(t.root->r);
    ASSERT_LE(std::abs(leftHeight - rightHeight), 1) << "Tree is not balanced after Balance()";

    // Проверяем, что балансировка не нарушила свойства бинарного поискового дерева
    // Тут как вариант можем проверить соблюдение порядка элементов, например, с помощью массива из ToArray
    int* arr = t.ToArray(Tree::Infix);
    for (int i = 0; i < t.count() - 1; ++i) {
        ASSERT_LE(arr[i], arr[i + 1]) << "Binary Search Tree property is violated";
    }

    // Освобождаем память массива
    delete[] arr;
}


// Проверка корректности бинарного дерева поиска
bool isBST(Node* root, Node* l = nullptr, Node* r = nullptr) {
    if (root == nullptr)
        return true;
    if (l != nullptr && root->value <= l->value)
        return false;
    if (r != nullptr && root->value >= r->value)
        return false;
    return isBST(root->l, l, root) && isBST(root->r, root, r);
}

// Тест полной балансировки для одностороннего дерева
TEST(TreeBalance, RightSkewedTreeTest) {
    Tree t;

    // Создаем одностороннее дерево
    for (int i = 0; i < 10; ++i) {
        t.add(i);
    }

    // Выполняем балансировку
    t.Balance();

    // Проверяем, что дерево теперь является бинарным деревом поиска
    ASSERT_TRUE(isBST(t.root));

    // Проверяем балансировку дерева.
    // Делаем упрощенное предположение, что для полностью сбалансированного дерева разница в высоте должна быть меньше или равна 1.
    ASSERT_LE(std::abs(t.height(t.root->l) - t.height(t.root->r)), 1);
}

// Тест балансировки для случайного дерева
TEST(TreeBalance, RandomTreeTest) {
    Tree t;
    std::vector<int> values(100);
    iota(values.begin(), values.end(), 0); // Заполняем значениями от 0 до 99
    std::shuffle(values.begin(), values.end(), std::mt19937{ std::random_device{}() });

    // Добавляем элементы в случайном порядке
    for (int val : values) {
        t.add(val);
    }

    // Выполняем балансировку
    t.Balance();

    // Проверяем, что дерево теперь является бинарным деревом поиска
    ASSERT_TRUE(isBST(t.root));

    // Проверяем балансировку дерева
    ASSERT_LE(std::abs(t.height(t.root->l) - t.height(t.root->r)), 1);
}

// Помощник для создания вектора из элементов дерева в порядке Infix
std::vector<int> treeToVector(Tree& t) {
    int* array = t.ToArray(Tree::Order::Infix);
    std::vector<int> result(t.count());
    std::copy(array, array + t.count(), result.begin());
    delete[] array;
    return result;
}

// Проверка, что балансировка не нарушает порядок элементов BST
TEST(TreeBalanceTest, TestMaintainsOrder) {
    Tree t;
    t.add(3);
    t.add(1);
    t.add(4);
    t.add(2);
    t.add(5);

    auto before_balance = treeToVector(t);

    t.Balance();

    auto after_balance = treeToVector(t);

    EXPECT_EQ(before_balance, after_balance);
}

// Проверка уменьшения высоты балансировки
TEST(TreeBalanceTest, TestHeightReduction) {
    Tree t;
    // Добавление элементов для создания несбалансированного дерева
    for (int i = 0; i < 10; i++) {
        t.add(i);
    }

    auto height_before = t.height(t.root);
    t.Balance();
    auto height_after = t.height(t.root);

    EXPECT_GT(height_before, height_after);
}

// Проверка балансировки на случайном наборе значений
TEST(TreeBalanceTest, TestRandomBalancing) {
    Tree t;
    std::vector<int> values(100);
    std::iota(values.begin(), values.end(), 1);
    std::random_shuffle(values.begin(), values.end());

    for (int value : values) {
        t.add(value);
    }
    t.Balance();

    // Значения должны сохраниться после балансировки
    auto values_after = treeToVector(t);

    std::sort(values.begin(), values.end());
    EXPECT_EQ(values, values_after);

    // Высота левого и правого поддеревьев должна отличаться не более чем на 1
    int left_height = t.height(t.root->l);
    int right_height = t.height(t.root->r);
    EXPECT_LE(std::abs(left_height - right_height), 1);
}

int main(int argc, char** argv) {
    setlocale(LC_ALL, "ru");
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}