#include <gtest/gtest.h>
#include "QuickSort.h"
#include "InsertSort.h"

#include <random>
#include <climits>

using SortFun = void (*) (std::vector<int>&, int, int);

class SortTest : public ::testing::Test{
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static std::vector<std::vector<int>> testCase_;
    static std::vector<std::vector<int>> ansCase_;

    static const int kaseNum_ = 1000;
    static const int minNum_ = 0;
    static const int maxNum_ = 1000;
    void CompareVector(std::vector<int> &l, std::vector<int> &r);
    void TestSortFunc(SortFun fun);
};

std::vector<std::vector<int>> SortTest::testCase_;
std::vector<std::vector<int>> SortTest::ansCase_;

void SortTest::CompareVector(std::vector<int> &l, std::vector<int> &r) {
    int size_l = l.size();
    int size_r = r.size();
    ASSERT_EQ(l, r);
    for(int i = 0; i < size_l; ++i) {
        ASSERT_EQ(l[i], r[i]);
    }
}

void SortTest::TestSortFunc(SortFun fun) {
    for(int i = 0; i < kaseNum_; ++i) {
        std::vector<int> testKase(testCase_[i]);
        (*fun)(testKase, 0, testKase.size() - 1);
        CompareVector(testKase, ansCase_[i]);
    }    
}

void SortTest::SetUpTestCase() {
    /* 生成测试集合 */
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(minNum_, maxNum_);

    for(int i = 0; i < kaseNum_; ++i) {
        int n = distribution(generator);
        if(n < 0) continue;
        std::vector<int> kase;
        for(int k = 0; k < n; k++) {
            kase.push_back(distribution(generator));
        }
        std::vector<int> ansKase(kase);
        std::sort(ansKase.begin(), ansKase.end());
        testCase_.push_back(kase);
        ansCase_.push_back(ansKase);
    }
    std::cout << std::endl;
}

void SortTest::TearDownTestCase() {
}

TEST_F(SortTest, test_quick_sort) {
    TestSortFunc(QuickSort);
}

TEST_F(SortTest, test_insert_sort) {
    TestSortFunc(InsertSort);
}
