#include <gtest/gtest.h>

#include "Prime.h"

#include <vector>

template<unsigned ...args>
void PrintSeq(std::integer_sequence<unsigned, args...> seq) {
  ((std::cout << args << " "), ...);
  std::cout << std::endl;
}


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
  IsPrime<5, std::integer_sequence<unsigned, 3, 2>>::value t1;
  ASSERT_EQ(t1, true);
  IsPrime<7, std::integer_sequence<unsigned, 5, 3, 2>>::value t2;
  ASSERT_EQ(t2, true);
  IsPrime<4, std::integer_sequence<unsigned, 3, 2>>::value f1;
  ASSERT_EQ(f1, false);
  IsPrime<6, std::integer_sequence<unsigned, 5, 3, 2>>::value f2;
  ASSERT_EQ(f2, false);
  IsPrime<8, std::integer_sequence<unsigned, 7, 5, 3, 2>>::value f3;
  ASSERT_EQ(f3, false);
}

TEST_F(PrimeTest, AppendPrimeTest) {
  Concat<std::integer_sequence<unsigned>, std::integer_sequence<unsigned>>::value t;
  ASSERT_EQ(0, t.size());

  std::is_same<
    Concat<
      std::integer_sequence<unsigned, 1, 2>,
      std::integer_sequence<unsigned>
    >::value,
      std::integer_sequence<unsigned, 1, 2>
    > t1;
  ASSERT_EQ(t1, true);

  std::is_same<
    Concat<
      std::integer_sequence<unsigned>,
      std::integer_sequence<unsigned, 3, 4>
    >::value,
      std::integer_sequence<unsigned, 3, 4>
    > t2;
  ASSERT_EQ(t2, true);

  std::is_same<
    Concat<
      std::integer_sequence<unsigned, 1, 2>,
      std::integer_sequence<unsigned, 3, 4>
    >::value,
      std::integer_sequence<unsigned, 1, 2, 3, 4>
    > t3;
  ASSERT_EQ(t3, true);
}
