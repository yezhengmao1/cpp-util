#include <gtest/gtest.h>
#include "QuickSort.h"

#include <random>

class SortTest : public ::testing::Test{
protected:
	virtual void SetUp() {}
	virtual void TearDown() {}
public:
	static void SetUpTestCase();
	static void TearDownTestCase();
	static std::vector<std::vector<int>> testCase_;
	static std::vector<std::vector<int>> ansCase_;
};

std::vector<std::vector<int>> SortTest::testCase_;
std::vector<std::vector<int>> SortTest::ansCase_;

void SortTest::SetUpTestCase() {
	/* 生成测试集合 */
	const int kaseNum = 100;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(0, 1000);

	for(int i = 0; i < 100; ++i) {
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
	std::cout << std::endl;
}

void SortTest::TearDownTestCase() {
}

TEST_F(SortTest, test_quick_sort) {
	int kaseNum = testCase_.size();
	for(int i = 0; i < kaseNum; ++i) {
		std::vector<int> testKase(testCase_[i]);
		QuickSort(testKase, 0, testKase.size() - 1);
		for(int k = 0; k < testKase.size(); ++k) {
			ASSERT_EQ(testKase[k], ansCase_[i][k]);
		}
	}
}
