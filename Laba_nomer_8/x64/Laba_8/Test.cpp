#include <gtest/gtest.h>
#include "Tree.hpp"
#include <algorithm>

TEST(TreeTest, RotateNonExistentNode) {
    Tree tree;
    // ��������� �������� � ������.
    tree.add(10);
    tree.add(5);
    tree.add(20);

    // ������� ��������� �������������� ����.
    tree.ToLeft(15);
    auto root = tree.root;
    ASSERT_TRUE(root != nullptr) << "Root should not be nullptr after rotation attempt on non-existent node.";
    ASSERT_EQ(root->value, 10) << "Root should have value 10.";

    tree.ToRight(15);
    root = tree.root;
    ASSERT_TRUE(root != nullptr) << "Root should not be nullptr after rotation attempt on non-existent node.";
    ASSERT_EQ(root->value, 10) << "Root should have value 10.";
}

TEST(TreeTest, RotateRootNode) {
    Tree tree;
    // ��������� �������� � ������.
    tree.add(10);
    tree.add(5);
    tree.add(20);

    // ������� ��������� ����.
    tree.ToLeft(10);
    Node* root = tree.root;
    ASSERT_TRUE(root != nullptr) << "Root should not be nullptr after left rotation.";
    ASSERT_EQ(root->value, 20) << "New root should have value 5 after left rotation.";

    tree.ToRight(5);
    root = tree.root;
    ASSERT_TRUE(root != nullptr) << "Root should not be nullptr after right rotation.";
    ASSERT_EQ(root->value, 20) << "Root should be value 10 after right rotation.";
}

TEST(TreeTest, RotateLeafNode) {
    Tree tree;
    // ��������� �������� � ������.
    tree.add(10);
    tree.add(5);
    tree.add(20);
    tree.add(1);

    // ������� ��������� ����.
    tree.ToLeft(1);
    // �������� ��������� ������ ����� ��������.
    ASSERT_TRUE(tree.root->l != nullptr) << "Root should have left child.";
    ASSERT_EQ(tree.root->l->value, 5) << "Left child of root should have value 5.";

    tree.ToRight(1);
    // �������� ��������� ������ ����� ��������.
    ASSERT_TRUE(tree.root->l != nullptr) << "Root should have left child after right rotation.";
}

TEST(TreeRotationTest, RotateLeftSimpleCase) {
    Tree tree;
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(20);

    tree.ToLeft(10); // ������ �������� ����� ������� ������ ���� �� ��������� 10.

    // ����� �������� ���� �� ��������� 15 ������ ����� ������.
    ASSERT_EQ(tree.root->value, 15);

    // ���� �� ��������� 10 ������ ������ ���� ����� �������� �����.
    ASSERT_EQ(tree.root->l->value, 10);

    // ��������, ��� ��������� ��������� ������������ ���������.
    ASSERT_EQ(tree.root->l->p->value, 15);

    // ��������� ���������� ���� �� ��������� 20.
    ASSERT_EQ(tree.root->r->value, 20);
    ASSERT_EQ(tree.root->r->p->value, 15);

    // ��������, ��� ���������� ����� ��� ��� ���������.
    ASSERT_EQ(tree.root->l->l->value, 5);
    ASSERT_EQ(tree.root->l->l->p->value, 10);
}

TEST(TreeRotationTest, RotateRightSimpleCase) {
    Tree tree;
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(3);

    tree.ToRight(10); // ������ �������� ������ ������� ������ ���� �� ��������� 10.

    // ����� �������� ���� �� ��������� 5 ������ ����� ������.
    ASSERT_EQ(tree.root->value, 5);

    // ���� �� ��������� 10 ������ ������ ���� ������ �������� �����.
    ASSERT_EQ(tree.root->r->value, 10);

    // ��������, ��� ��������� ��������� ������������ ���������.
    ASSERT_EQ(tree.root->r->p->value, 5);

    // ��������� ���������� ���� �� ��������� 3.
    ASSERT_EQ(tree.root->l->value, 3);
    ASSERT_EQ(tree.root->l->p->value, 5);

    // ��������, ��� ����� ��� ���� �� ��������� 15 ��� ��� ���������.
    ASSERT_EQ(tree.root->r->r->value, 15);
    ASSERT_EQ(tree.root->r->r->p->value, 10);
}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}