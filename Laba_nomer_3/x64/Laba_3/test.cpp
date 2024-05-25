#include<gtest/gtest.h>
#include "List.cpp" 

// ИСПОЛЬЗОВАТЬ ТОЛЬКО В DEBUG ВЕРСИИ


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

TEST(ListTest, InsertIntoEmptyList) {
    List list;
    list.insert(0, 10); // Вставляем в пустой список.

    ASSERT_EQ(list.head->data, 10); // Голова указывает на новый элемент.
    ASSERT_EQ(list.tail->data, 10); // Хвост указывает на новый элемент.
    ASSERT_EQ(list.common_count, 1); // Счетчик элементов увеличен.
    ASSERT_EQ(list.head->next, list.head); // Список зациклен.
}

TEST(ListTest, InsertIntoNonEmptyList) {
    List list;
    list.add(10); // Добавляем элемент, чтобы список стал непустым.
    list.insert(0, 5); // Вставляем в начало

    ASSERT_EQ(list.head->data, 5); // Новый элемент в голове.
    ASSERT_EQ(list.tail->next, list.head); // Хвост правильно указывает на голову.
    ASSERT_EQ(list.elementAt(1), 10); // Второй элемент - первоначальный.
    ASSERT_EQ(list.common_count, 2); // Должны быть два элемента.

    list.insert(1, 7); // Вставляем в середину.
    ASSERT_EQ(list.elementAt(1), 7); // Элемент на второй позиции равен 7.
    ASSERT_EQ(list.common_count, 3); // Теперь три элемента.

    list.insert(3, 12); // Вставляем в конец.
    ASSERT_EQ(list.tail->data, 12); // Хвост указывает на новый последний элемент. 
    ASSERT_EQ(list.common_count, 4); // Счетчик расширился до четырех.
}


int main1(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
