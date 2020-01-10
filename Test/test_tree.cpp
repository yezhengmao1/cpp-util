#include <gtest/gtest.h>

#include "Tree.h"

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

TEST_F(TreeTest, Node) {
}
