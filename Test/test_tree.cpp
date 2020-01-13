#include <gtest/gtest.h>

#include "RBTree.h"
#include "MallocAllocator.h"

#include <map>

using namespace Tree;
using namespace std;

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

TEST_F(TreeTest, RBTreeNodeIncDec) {
    // 数据准备
    typedef RBTreeNode<int>* NodePtr;
    typedef RBTreeNodeBase* BasePtr;
    typedef const RBTreeNodeBase* ConstBasePtr;

    map<int, BasePtr> test_case;
    map<int, ConstBasePtr> test_const_case;
    RBTreeHeader header;

    for(int i = 1; i <= 7; i++) {
        NodePtr node = new RBTreeNode<int>();
        node->val_ = i;
        node->left_ = nullptr;
        node->right_ = nullptr;
        test_case.insert(make_pair(i, node));
        test_const_case.insert(make_pair(i, node));
    }
    header.headerNode_.parent_ = test_case[4];
    header.headerNode_.left_ = test_case[1];
    header.headerNode_.right_ = test_case[7];

    test_case[4]->parent_ = &(header.headerNode_);

#define ADDLEFT(ROOT, L) do { \
    test_case[ROOT]->left_=test_case[L]; \
    test_case[L]->parent_=test_case[ROOT]; \
}while(0)
#define ADDRIGHT(ROOT, R) do { \
    test_case[ROOT]->right_=test_case[R]; \
    test_case[R]->parent_=test_case[ROOT]; \
}while(0)

    ADDLEFT(4, 2);
    ADDRIGHT(4, 6);
    ADDLEFT(2, 1);
    ADDRIGHT(2, 3);
    ADDLEFT(6, 5);
    ADDRIGHT(6, 7);
    
    auto end_pos = &(header.headerNode_);
    ConstBasePtr const_end_pos = &(header.headerNode_);
    
    ASSERT_EQ(end_pos, decrement(test_case[1]));
    ASSERT_EQ(const_end_pos, decrement(test_const_case[1]));
    ASSERT_EQ(decrement(end_pos), test_case[7]);
    ASSERT_EQ(decrement(const_end_pos), test_case[7]);

    for(int i = 2; i <= 7; ++i) {
        ASSERT_EQ(decrement(test_case[i]), test_case[i-1]);
        ASSERT_EQ(decrement(test_const_case[i]), test_case[i-1]);
    }
    ASSERT_EQ(end_pos, increment(test_case[7]));
    ASSERT_EQ(end_pos, increment(test_const_case[7]));
    for(int i = 1; i < 7; i++) {
        ASSERT_EQ(increment(test_case[i]), test_case[i+1]);
        ASSERT_EQ(increment(test_const_case[i]), test_case[i+1]);
    }
}
