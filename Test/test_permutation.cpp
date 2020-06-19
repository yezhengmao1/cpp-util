#include <gtest/gtest.h>

#include <random>

#include "Permutation.h"

class PermutationTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void PermutationTest::SetUpTestCase() {

}

void PermutationTest::TearDownTestCase() {

}

TEST_F(PermutationTest, next_permutation) {
  for(int i = 0; i < 10; ++i) {
    std::vector<int> kase, kase_cmp;
    for(int j = 0; j < i; ++j) {
      kase.push_back(j);
      kase_cmp.push_back(j);
    }
    for(;;) {
      for(int j = 0; j < kase.size(); ++j) {
        ASSERT_EQ(kase[j], kase_cmp[j]);
      }
      bool c = NextPermutation(kase.begin(), kase.end());
      bool a = std::next_permutation(kase_cmp.begin(), kase_cmp.end());
      ASSERT_EQ(c, a);
      if(!a) { break; }
    }
  }
}

TEST_F(PermutationTest, next_permutation_random) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 100);
  for(int i = 0; i < 10; ++i) {
    std::vector<int> kase, kase_cmp;
    for(int j = 0; j < i; ++j) {
      int tmp = distrib(gen);
      kase.push_back(tmp);
      kase_cmp.push_back(tmp);
    }
    for(;;) {
      for(int j = 0; j < kase.size(); ++j) {
        ASSERT_EQ(kase[j], kase_cmp[j]);
      }
      bool c = NextPermutation(kase.begin(), kase.end());
      bool a = std::next_permutation(kase_cmp.begin(), kase_cmp.end());
      ASSERT_EQ(c, a);
      if(!a) { break; }
    }
  }
}

TEST_F(PermutationTest, prev_permutation) {
  for(int i = 0; i < 10; ++i) {
    std::vector<int> kase, kase_cmp;
    for(int j = i; j >= 0; --j) {
      kase.push_back(j);
      kase_cmp.push_back(j);
    }
    for(;;) {
      for(int j = 0; j < kase.size(); ++j) {
        ASSERT_EQ(kase[j], kase_cmp[j]);
      }
      bool c = PrevPermutation(kase.begin(), kase.end());
      bool a = std::prev_permutation(kase_cmp.begin(), kase_cmp.end());
      ASSERT_EQ(c, a);
      if(!a) { break; }
    }
  }
}

TEST_F(PermutationTest, prev_permutation_random) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 100);
  for(int i = 0; i < 10; ++i) {
    std::vector<int> kase, kase_cmp;
    for(int j = i; j >= 0; --j) {
      int tmp = distrib(gen);
      kase.push_back(tmp);
      kase_cmp.push_back(tmp);
    }
    for(;;) {
      for(int j = 0; j < kase.size(); ++j) {
        ASSERT_EQ(kase[j], kase_cmp[j]);
      }
      bool c = PrevPermutation(kase.begin(), kase.end());
      bool a = std::prev_permutation(kase_cmp.begin(), kase_cmp.end());
      ASSERT_EQ(c, a);
      if(!a) { break; }
    }
  }
}
