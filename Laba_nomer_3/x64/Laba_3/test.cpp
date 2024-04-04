#include<gtest/gtest.h>
#include "List.cpp" 

// ������������ ������ � DEBUG ������

// ���� �� ���������� ��������� � ������.
TEST(ListTest, add) {
    List myList;
    myList.add(1);
    EXPECT_EQ(myList.count(), 1);
    EXPECT_EQ(myList.elementAt(0), 1);

    myList.add(2);
    myList.add(3);
    EXPECT_EQ(myList.count(), 3);
    EXPECT_EQ(myList.elementAt(2), 3);

    // ��������� ��������� num_flag, ���� �� ������������
    myList.elementAt(0);
    myList.add(4);
    EXPECT_EQ(myList.elementAt(3), 4); // num_flag ������ ������������� ���������� ����� ����������
}

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

// ���� �� �������� ��������� �� ������.
TEST(ListTest, removeAt) {
    List myList;
    myList.add(4);
    myList.add(5);
    myList.add(6);

    // ���� �� �������� �� �������� ������
    myList.removeAt(1);
    EXPECT_EQ(myList.elementAt(1), 6);
    EXPECT_EQ(myList.count(), 2);

    // ��������� �������� ���������� ��������
    myList.removeAt(1);
    EXPECT_EQ(myList.count(), 1);

    // ������� �������� �� ������� ������
    myList.clear();
    myList.removeAt(0);
    EXPECT_EQ(myList.count(), 0);
}

// ���� �� �������� ������������� �����.
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

    // �������� �� ��������� ��� ������ ������
    myList.clear();
    myList.removeNegative();
    EXPECT_EQ(myList.count(), 0);
}

// ���� �� ������� ������.
TEST(ListTest, clear) {
    List myList;
    myList.add(8);
    myList.add(9);
    myList.add(10);

    myList.clear();
    EXPECT_EQ(myList.count(), 0);

    // �������� ������� ��� ������� ������
    myList.clear();
    EXPECT_EQ(myList.count(), 0);
}

// ����������� ���� �� �������� ���������� �������.
TEST(ListTest, ComplexOperations) {
    List myList;

    // ���������� � ���������� �������������� ����� �� �������
    myList.add(-10);
    myList.add(-20);
    myList.add(-30);
    EXPECT_EQ(myList.elementAt(0), -10);
    myList.elementAt(0); // ��������� ����� �� ������� -10
    EXPECT_EQ(myList.count(), 3);

    // ������� ����������� �������� � �������� �����
    myList.add(25);
    EXPECT_EQ(myList.elementAt(3), 25);
    EXPECT_EQ(myList.elementAt(0), -10); // num_flag ������� ����������

    // ������� ����� ������ ������������� ��������� � ���������� �������
    myList.insertBeforeNegative();
    EXPECT_EQ(myList.count(), 7);
    EXPECT_EQ(myList.elementAt(0), 1); // ����� ������� ����� -10
    EXPECT_EQ(myList.elementAt(2), 1); // ����� ������� ����� -20
    EXPECT_EQ(myList.elementAt(4), 1); // ����� ������� ����� -30

    // �������� ������������� ��������� � ���������� �������
    myList.removeNegative();
    EXPECT_EQ(myList.count(), 4);
    EXPECT_EQ(myList.elementAt(0), 1); // ������ ������� ������ 1
    EXPECT_EQ(myList.elementAt(1), 1); // ������ ������� ������ 1
    EXPECT_EQ(myList.elementAt(3), 25); // ��������� ������� ������ 25

    // ������� ��������, �������� �������� � �������� count
    myList.insert(1, 100);
    EXPECT_EQ(myList.elementAt(1), 100);
    myList.removeAt(2);
    EXPECT_EQ(myList.elementAt(1), 100); // ����� ����������� ������� �������
    EXPECT_EQ(myList.count(), 4); // ���������� ���������� ��������� ����� ��������

    // ������� ������ � �������� �������
    myList.clear();
    EXPECT_EQ(myList.count(), 0);
    try {
        myList.elementAt(0); // ������ ������ ����������
    }
    catch (const std::out_of_range& e) {
        EXPECT_EQ(e.what(), std::string("Invalid value!"));
    }

    // �������� �� ���������� ��������
    myList.removeAt(-1); // �������� � ������������ ��������
    myList.removeAt(0); // �������� � ������������ ��������
    myList.insert(-1, 999); // ������� � ������������ ��������
    myList.insert(0, 999); // ������� ��� � ������ ������
    EXPECT_EQ(myList.count(), 1);
    EXPECT_EQ(myList.elementAt(0), 999);
}

int main1(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
