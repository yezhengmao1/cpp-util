#include <gtest/gtest.h>

#include <TypeTraits.h>

using namespace STL;

class TestTypeTraits : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void TestTypeTraits::SetUpTestCase() {

}

void TestTypeTraits::TearDownTestCase() {

}

int func(integral_constant<int, 1>::type) { return 1; }
int func(integral_constant<int, 2>::type) { return 2; }

template<int N>
int test_func() {
    return func(typename integral_constant<int, N>::type());
}

TEST_F(TestTypeTraits, Constant) {
    typedef integral_constant<int, 2> two;

    two i;
    int j = two().operator int();
    int k = i.operator int();
    int m = i;

    ASSERT_EQ(two::value * 2, 4);
    ASSERT_EQ(two(), 2);
    ASSERT_EQ(i, 2);
    ASSERT_EQ(j, 2);
    ASSERT_EQ(two().value, 2);
    ASSERT_EQ(test_func<1>(), 1);
    ASSERT_EQ(test_func<2>(), 2);
}


TEST_F(TestTypeTraits, Bool) {
    ASSERT_EQ(true_type::value, true);
    ASSERT_EQ(false_type::value, false);
}


TEST_F(TestTypeTraits, TypeIsSame) {
    std::vector<bool> truekase = {
        is_same<int, int>::value,
        is_same<int, signed int>::value,
        is_same<char, char>::value,
    };
    std::vector<bool> falsekase = {
        is_same<int, double>::value,
        is_same<int, int*>::value,
        is_same<int, const int>::value,
        is_same<char, unsigned char>::value,
        is_same<char, signed char>::value,
    };
    for(auto i : truekase) {
        ASSERT_EQ(i, true);
    }
    for(auto i : falsekase) {
        ASSERT_EQ(i, false);
    }
}

TEST_F(TestTypeTraits, RemoveCV) {
    std::vector<bool> truekase = {
        is_same<remove_cv<const int>::type, int>::value,
        is_same<remove_cv<volatile int>::type, int>::value,
        is_same<remove_cv<const volatile int>::type, int>::value,
        // const volatile 修饰*(int*)
        is_same<remove_cv<const volatile int*>::type, const volatile int*>::value,
        // const volatile 修饰int*
        is_same<remove_cv<int * const volatile>::type, int*>::value,
        is_same<remove_cv<int * volatile const>::type, int*>::value,
        // const 修饰 int*, volatile 修饰 *(int*)
        is_same<remove_cv<volatile int * const>::type, volatile int*>::value,
        // volatile 修饰 int*, const 修饰 *(int*)
        is_same<remove_cv<const int * volatile>::type, const int*>::value,
    };
    std::vector<bool> falsekase = {
        is_same<remove_cv<const volatile int*>::type, int>::value,
    };
    for(auto i : truekase) {
        ASSERT_EQ(i, true);
    }
    for(auto i : falsekase) {
        ASSERT_EQ(i, false);
    }
}
