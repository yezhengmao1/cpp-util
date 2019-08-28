#include <gtest/gtest.h>
#include "QuickSort.h"
#include "InsertSort.h"
#include "HeapSort.h"
#include "SelectSort.h"
#include "BubbleSort.h"
#include "MergeSort.h"

#include <utility>
#include <random>
#include <climits>

using SortFun = void (*) (std::vector<int>&, int, int);
using TestCaseArr = std::vector<std::vector<int>>;

class SortTest : public ::testing::Test{
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    static TestCaseArr testCase_;
    static TestCaseArr ansCase_;
    static TestCaseArr segTestCase_;
    static TestCaseArr segAnsCase_;
    static std::vector<std::pair<int, int>> seg_;

    static const int kaseNum_ = 10;
    static const int minNum_ = 0;
    static const int maxNum_ = 100;
    void CompareVector(std::vector<int> &l, std::vector<int> &r);
    void TestSortFunc(SortFun fun);
};

TestCaseArr SortTest::testCase_;
TestCaseArr SortTest::ansCase_;
TestCaseArr SortTest::segTestCase_;
TestCaseArr SortTest::segAnsCase_;
std::vector<std::pair<int, int>> SortTest::seg_;

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
    for(int i = 0; i < kaseNum_; ++i) {
        std::vector<int> testCase(segTestCase_[i]);
        std::pair<int, int> lr(seg_[i]);
        (*fun)(testCase, lr.first, lr.second);
        CompareVector(testCase, segAnsCase_[i]);
    }
}

void SortTest::SetUpTestCase() {
    /* 生成测试集合 */
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(minNum_, maxNum_);

    for(int i = 0; i < kaseNum_; ++i) {
        int n = distribution(generator);
        std::vector<int> kase;
        for(int k = 0; k < n; k++) {
            kase.push_back(distribution(generator));
        }
        std::vector<int> ansKase(kase);
        std::sort(ansKase.begin(), ansKase.end());
        testCase_.push_back(kase);
        ansCase_.push_back(ansKase);
    }

    for(int i = 0; i < kaseNum_; ++i) {
        int n = 0, l = 0;
        while(l >= n) {
            n = distribution(generator);
            l = distribution(generator);
        }
        int s = distribution(generator);
        if(l >= n) l -= n;              // l < n
        if(l+s > n) s = n-l;            // l+s <= n
        seg_.push_back({l, l+s-1});
        std::vector<int> kase;
        for(int k = 0; k < n; ++k) {
            kase.push_back(distribution(generator));
        }
        segTestCase_.push_back(kase);
        std::vector<int> ansKase(kase);
        std::sort(ansKase.begin()+l, ansKase.begin()+l+s);
        segAnsCase_.push_back(ansKase);
    }
    std::cout << std::endl;
}

void SortTest::TearDownTestCase() {
}

TEST_F(SortTest, test_quick_sort) {
    TestSortFunc(QuickSort);
}

TEST_F(SortTest, test_heap_sort) {
    TestSortFunc(HeapSort);
}

TEST_F(SortTest, test_merge_sort) {
    TestSortFunc(MergeSort);
}

TEST_F(SortTest, test_select_sort) {
    TestSortFunc(SelectSort);
}

TEST_F(SortTest, test_insert_sort) {
    TestSortFunc(InsertSort);
}

TEST_F(SortTest, test_bubble_sort) {
    TestSortFunc(BubbleSort);
}


