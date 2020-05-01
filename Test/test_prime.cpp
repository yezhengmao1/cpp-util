#include <gtest/gtest.h>

#include "Prime.h"

#include <vector>

class PrimeTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void PrimeTest::SetUpTestCase() {

}

void PrimeTest::TearDownTestCase() {

}

TEST_F(PrimeTest, IsPrimeTest) {
  std::vector<bool> tKase = {
    IsPrime<5, 3, 2>::value::value,
    IsPrime<7, 5, 3, 2>::value::value,
  };
  std::vector<bool> fKase = {
    IsPrime<4, 3, 2>::value::value,
    IsPrime<6, 5, 3, 2>::value::value,
  };
  for(auto t : tKase) {
    ASSERT_EQ(t, true);
  }
  for(auto f : fKase) {
    ASSERT_EQ(f, false);
  }
}
