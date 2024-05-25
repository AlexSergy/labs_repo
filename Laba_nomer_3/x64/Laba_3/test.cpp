#include<gtest/gtest.h>
#include "List.cpp" 

// ������������ ������ � DEBUG ������


// ���� �� ������� ��������� � ������.
TEST(ListTest, insert) {
    List myList;
    myList.insert(0, -1);  // ������� � ������ ������.
    EXPECT_EQ(myList.elementAt(0), -1);

    myList.insert(1, 5);  // ������� � ����� ������, ������� ������� ����� ��� �� ������ ��������.
    EXPECT_EQ(myList.elementAt(1), 5);

    // ������� � �������������� ������� (�� ������ ��������� � ������)
    myList.insert(5, 6);
    EXPECT_EQ(myList.count(), 3);

    // ������� � �������� ������
    myList.insert(1, 2);
    EXPECT_EQ(myList.elementAt(1), 2);
    EXPECT_EQ(myList.count(), 4);
}

TEST(ListTest, InsertIntoEmptyList) {
    List list;
    list.insert(0, 10); // ��������� � ������ ������.

    ASSERT_EQ(list.head->data, 10); // ������ ��������� �� ����� �������.
    ASSERT_EQ(list.tail->data, 10); // ����� ��������� �� ����� �������.
    ASSERT_EQ(list.common_count, 1); // ������� ��������� ��������.
    ASSERT_EQ(list.head->next, list.head); // ������ ��������.
}

TEST(ListTest, InsertIntoNonEmptyList) {
    List list;
    list.add(10); // ��������� �������, ����� ������ ���� ��������.
    list.insert(0, 5); // ��������� � ������

    ASSERT_EQ(list.head->data, 5); // ����� ������� � ������.
    ASSERT_EQ(list.tail->next, list.head); // ����� ��������� ��������� �� ������.
    ASSERT_EQ(list.elementAt(1), 10); // ������ ������� - ��������������.
    ASSERT_EQ(list.common_count, 2); // ������ ���� ��� ��������.

    list.insert(1, 7); // ��������� � ��������.
    ASSERT_EQ(list.elementAt(1), 7); // ������� �� ������ ������� ����� 7.
    ASSERT_EQ(list.common_count, 3); // ������ ��� ��������.

    list.insert(3, 12); // ��������� � �����.
    ASSERT_EQ(list.tail->data, 12); // ����� ��������� �� ����� ��������� �������. 
    ASSERT_EQ(list.common_count, 4); // ������� ���������� �� �������.
}


int main1(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
