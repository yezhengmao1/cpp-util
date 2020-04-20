#include <gtest/gtest.h>

#include "KmpSearch.h"

class KMPTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void KMPTest::SetUpTestCase() {

}

void KMPTest::TearDownTestCase() {

}

TEST_F(KMPTest, KMPTable) {
    const char* str = "ACABACACD";
    std::vector<std::size_t> kase{0, 0, 0, 1, 0, 1, 2, 3, 2, 0};
    auto ans = KmpTable(str);
    ASSERT_EQ(ans.size(), kase.size());
    for(std::size_t i = 0; i < kase.size(); ++i) {
        ASSERT_EQ(kase[i], ans[i]);
    }
}

TEST_F(KMPTest, KMPSearch) {
    auto ret = KmpSearch("test", "t");
    ASSERT_EQ(ret.size(), 2);
    ASSERT_EQ(ret[0], 0);
    ASSERT_EQ(ret[1], 3);

    ret = KmpSearch("aaaa", "a");
    ASSERT_EQ(ret.size(), 4);
    for(std::size_t i = 0; i < 4; ++i) {
        ASSERT_EQ(ret[i], i);
    }
}
