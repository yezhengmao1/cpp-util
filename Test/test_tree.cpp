#include <gtest/gtest.h>

#include "RBTree.h"
#include "MallocAllocator.h"

class TreeTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void TreeTest::SetUpTestCase() {

}

void TreeTest::TearDownTestCase() {

}

TEST_F(TreeTest, RBTreeNode) {
    auto node = Tree::RBTreeNode<int>();
    node.val_ = 100;
    auto ptr = node.ValPtr();
    std::cout << ptr << std::endl;
    std::cout << *ptr << std::endl;
}
