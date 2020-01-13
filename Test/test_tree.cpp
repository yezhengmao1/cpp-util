#include <gtest/gtest.h>

#include "RBTree.h"
#include "MallocAllocator.h"

#include <map>

using namespace Tree;
using namespace std;

typedef RBTreeNode<int>* NodePtr;
typedef const RBTreeNode<int>* ConstNodePtr;
typedef RBTreeNodeBase* BasePtr;
typedef const RBTreeNodeBase* ConstBasePtr;

class TreeTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();

    static map<int, NodePtr> test_case;
    static map<int, ConstNodePtr> test_const_case;
    static RBTreeHeader header;
};

map<int, NodePtr> TreeTest::test_case;
map<int, ConstNodePtr> TreeTest::test_const_case;
RBTreeHeader TreeTest::header;

void TreeTest::SetUpTestCase() {
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
}

void TreeTest::TearDownTestCase() {

}

TEST_F(TreeTest, RBTreeNode) {
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

TEST_F(TreeTest, RBTreeIterator) {
    typedef struct TestStruct {
        int x;
        int y;
    } TestStruct;
    typedef RBTreeIterator<TestStruct> StructIterator;

    RBTreeNode<TestStruct>* vnode = new RBTreeNode<TestStruct>();
    StructIterator s_it(vnode);
    vnode->val_.x = 1; 
    vnode->val_.y = 2;
    ASSERT_EQ(s_it->x, 1);
    ASSERT_EQ(s_it->y, 2);

    auto end_pos = &(header.headerNode_);

    typedef Tree::RBTreeIterator<int>::iterator Iterator;
    typedef Tree::RBTreeIterator<int>::const_iterator ConstIterator;

    Iterator begin(test_case[1]);
    Iterator end(end_pos);
    // ++ test
    auto inc = begin;
    int ans = 1;
    ASSERT_EQ(true, inc == begin);
    ASSERT_EQ(true, inc != end);
    while(inc != end) {
        ASSERT_EQ(ans++, *(inc++));
    }
    // -- test
    auto dec = --end;
    ans = 7;
    while(dec != end) {
        ASSERT_EQ(ans--, *(dec--));
    }
    // const test
    ConstIterator cbegin(test_case[1]);
    ConstIterator cend(end_pos);
    ASSERT_EQ(*cbegin, 1);
    auto kase = begin;
    *kase = 10;
    ASSERT_EQ(((NodePtr)kase.node_)->val_, 10);
    ASSERT_EQ(*cbegin, 10);
    (*kase)--;
    ASSERT_EQ(((NodePtr)kase.node_)->val_, 9);
    ASSERT_EQ(*cbegin, 9);
    *kase = 1;
    ASSERT_EQ(((NodePtr)begin.node_)->val_, 1);
    ASSERT_EQ(*cbegin, 1);
    cbegin++;
    ASSERT_EQ(*++cbegin, 3);
    ASSERT_EQ(*--cbegin, 2);
    ASSERT_EQ(*cbegin++, 2);
    ASSERT_EQ(*cbegin--, 3);
    ASSERT_EQ(*cbegin, 2);
}
