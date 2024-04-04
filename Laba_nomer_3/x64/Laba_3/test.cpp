#include<gtest/gtest.h>
#include "List.cpp" 

// ИСПОЛЬЗОВАТЬ ТОЛЬКО В DEBUG ВЕРСИИ

// Тест на добавление элементов в список.
TEST(ListTest, add) {
    List myList;
    myList.add(1);
    EXPECT_EQ(myList.count(), 1);
    EXPECT_EQ(myList.elementAt(0), 1);

    myList.add(2);
    myList.add(3);
    EXPECT_EQ(myList.count(), 3);
    EXPECT_EQ(myList.elementAt(2), 3);

    // Проверяем поведение num_flag, если он задействован
    myList.elementAt(0);
    myList.add(4);
    EXPECT_EQ(myList.elementAt(3), 4); // num_flag должен автоматически обновиться после добавления
}

// Тест на вставку элементов в список.
TEST(ListTest, insert) {
    List myList;
    myList.insert(0, -1);  // Вставка в начало списка.
    EXPECT_EQ(myList.elementAt(0), -1);

    myList.insert(1, 5);  // Вставка в конец списка, который состоит более чем из одного элемента.
    EXPECT_EQ(myList.elementAt(1), 5);

    // Вставка в несуществующую позицию (не должна приводить к ошибке)
    myList.insert(5, 6);
    EXPECT_EQ(myList.count(), 3);

    // Вставка в середину списка
    myList.insert(1, 2);
    EXPECT_EQ(myList.elementAt(1), 2);
    EXPECT_EQ(myList.count(), 4);
}

// Тест на удаление элементов из списка.
TEST(ListTest, removeAt) {
    List myList;
    myList.add(4);
    myList.add(5);
    myList.add(6);

    // Тест на удаление из середины списка
    myList.removeAt(1);
    EXPECT_EQ(myList.elementAt(1), 6);
    EXPECT_EQ(myList.count(), 2);

    // Проверяем удаление последнего элемента
    myList.removeAt(1);
    EXPECT_EQ(myList.count(), 1);

    // Попытка удаления из пустого списка
    myList.clear();
    myList.removeAt(0);
    EXPECT_EQ(myList.count(), 0);
}

// Тест на удаление отрицательных чисел.
TEST(ListTest, removeNegative) {
    List myList;
    myList.add(-7);
    myList.add(2);
    myList.add(-3);
    myList.add(4);

    myList.removeNegative();
    EXPECT_EQ(myList.count(), 2);
    EXPECT_EQ(myList.elementAt(0), 2);
    EXPECT_EQ(myList.elementAt(1), 4);

    // Проверка на поведение при пустом списке
    myList.clear();
    myList.removeNegative();
    EXPECT_EQ(myList.count(), 0);
}

// Тест на очистку списка.
TEST(ListTest, clear) {
    List myList;
    myList.add(8);
    myList.add(9);
    myList.add(10);

    myList.clear();
    EXPECT_EQ(myList.count(), 0);

    // Проверка очистки уже пустого списка
    myList.clear();
    EXPECT_EQ(myList.count(), 0);
}

// Комплексный тест на проверку нескольких функций.
TEST(ListTest, ComplexOperations) {
    List myList;

    // Добавление и сохранение отрицательного флага на элемент
    myList.add(-10);
    myList.add(-20);
    myList.add(-30);
    EXPECT_EQ(myList.elementAt(0), -10);
    myList.elementAt(0); // Установка флага на элемент -10
    EXPECT_EQ(myList.count(), 3);

    // Вставка нормального элемента и проверка флага
    myList.add(25);
    EXPECT_EQ(myList.elementAt(3), 25);
    EXPECT_EQ(myList.elementAt(0), -10); // num_flag остался неизменным

    // Вставка перед каждым отрицательным элементом и обновление позиций
    myList.insertBeforeNegative();
    EXPECT_EQ(myList.count(), 7);
    EXPECT_EQ(myList.elementAt(0), 1); // Новый элемент перед -10
    EXPECT_EQ(myList.elementAt(2), 1); // Новый элемент перед -20
    EXPECT_EQ(myList.elementAt(4), 1); // Новый элемент перед -30

    // Удаление отрицательных элементов и обновление позиций
    myList.removeNegative();
    EXPECT_EQ(myList.count(), 4);
    EXPECT_EQ(myList.elementAt(0), 1); // Первый элемент теперь 1
    EXPECT_EQ(myList.elementAt(1), 1); // Второй элемент теперь 1
    EXPECT_EQ(myList.elementAt(3), 25); // Четвертый элемент теперь 25

    // Вставка элемента, удаление элемента и проверка count
    myList.insert(1, 100);
    EXPECT_EQ(myList.elementAt(1), 100);
    myList.removeAt(2);
    EXPECT_EQ(myList.elementAt(1), 100); // Ранее вставленный элемент остался
    EXPECT_EQ(myList.count(), 4); // Изменилось количество элементов после удаления

    // Очистка списка и проверка пустоты
    myList.clear();
    EXPECT_EQ(myList.count(), 0);
    try {
        myList.elementAt(0); // Должно выдать исключение
    }
    catch (const std::out_of_range& e) {
        EXPECT_EQ(e.what(), std::string("Invalid value!"));
    }

    // Проверки на негативные сценарии
    myList.removeAt(-1); // Удаление с недопустимым индексом
    myList.removeAt(0); // Удаление с недопустимым индексом
    myList.insert(-1, 999); // Вставка с недопустимым индексом
    myList.insert(0, 999); // Вставка при в пустом списке
    EXPECT_EQ(myList.count(), 1);
    EXPECT_EQ(myList.elementAt(0), 999);
}

int main1(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
