#include <gtest/gtest.h>
#include "kmp.h"

class StringTest: public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TerDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void StringTest::SetUpTestCase() {}
void StringTest::TearDownTestCase() {}

TEST_F(StringTest, test_kmp) {
    std::string str = "abcabc";
    std::string p = "ca";
    int ret = KMP(str, p);
    ASSERT_EQ(ret, 2);
}
