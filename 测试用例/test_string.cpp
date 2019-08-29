#include <gtest/gtest.h>
#include "kmp.h"

#include <random>
#include <string>
#include <utility>

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
    const int kmpTestCaseNum = 100;

    std::default_random_engine generator;
    std::uniform_int_distribution<int> strLen(0, 10000);
    std::uniform_int_distribution<char> randomChar('a', 'z');

    bool flag = true;

    for(int i = 0; i < kmpTestCaseNum; ++i) {
        int n = strLen(generator);
        std::uniform_int_distribution<int> startStr(0, n);
        int l = startStr(generator);
        std::uniform_int_distribution<int> subLen(0, n-l);
        int s = subLen(generator);

        std::string kase = "";
        for(int k = 0; k < n; ++k) {
            kase = kase + randomChar(generator);
        }

        std::string subStr = "";
        if(flag) {
            subStr = kase.substr(l, s);
        }else {
            for(int i = 0; i < s; ++i) {
                subStr = subStr + randomChar(generator);
            }
        }
        
        flag = !flag;
        std::size_t pos = kase.find(subStr);
        int ret = KMP(kase, subStr);
        ASSERT_EQ(ret, pos);
    }
}
