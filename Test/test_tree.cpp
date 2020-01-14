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

void ShowTree(NodePtr node, int level = 0) {
    if(node == nullptr) return;
    for(int i = 0; i < level; ++i) {
        cout << "  ";
    }
    cout << node->val_ << endl;
    ShowTree((NodePtr)node->left_, level+1);
    ShowTree((NodePtr)node->right_, level+1);
}

void InsertNodeInt(NodePtr node, Tree::RBTreeHeader &header) {
    BasePtr &root = header.headerNode_.parent_;
    NodePtr loop = (NodePtr)root;
    while(true) {
        if(node->val_ < loop->val_) {
            if(loop->left_ == nullptr) break;
            loop = (NodePtr)loop->left_;
        }else {
            if(loop->right_ == nullptr) break;
            loop = (NodePtr)loop->right_;
        }
    }
    node->parent_ = loop;
    if(node->val_ >= loop->val_) {
        loop->right_ = node;
    }else {
        loop->left_ = node;
    }

    RBTreeRebalanceForInsert(node, header.headerNode_);
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

TEST_F(TreeTest, BalanceForInsert) {
    Tree::RBTreeHeader header;

    typedef Tree::RBTreeNode<int>* NodePtr;
    typedef Tree::RBTreeNodeBase*  BasePtr;

    NodePtr node = new Tree::RBTreeNode<int>();
    node->color_ = Tree::Black;
    node->val_ = 1;
    node->left_ = nullptr;
    node->right_ = nullptr;
    node->parent_ = &(header.headerNode_);
    header.headerNode_.parent_ = node;
    header.headerNode_.left_ = node;
    
    vector<int> test_case = {9, 5, 4, 2, 7, 6, 8, 3};
    for(auto i : test_case) {
        NodePtr n = new Tree::RBTreeNode<int>();
        n->val_ = i;
        n->left_ = n->right_ = n->parent_ = nullptr;
        InsertNodeInt(n, header);
        if(i == 9) {
            header.headerNode_.right_ = n;
        }
    }

    typedef Tree::RBTreeIterator<int>::iterator Iterator;
    typedef Tree::RBTreeIterator<int>::const_iterator ConstIterator;
    
    ConstIterator cbegin(header.headerNode_.left_);
    ConstIterator cend(&header.headerNode_);
    auto it = cbegin;
    int cmp = 1;
    while(it != cend) {
        ASSERT_EQ(cmp++, *it++);
    }
}
