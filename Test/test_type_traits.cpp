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

struct TestClass {
    int A;
    int* B;
    int Func() { return 1; }
};

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

TEST_F(TestTypeTraits, AddCV) {
    struct test_case {
        int fun() { return 1; }
        int fun() const { return 2; }
        int fun() volatile { return 3; }
        int fun() const volatile { return 4; }
    };
    
    ASSERT_EQ(test_case().fun(), 1);
    ASSERT_EQ(add_const<test_case>::type().fun(), 2);
    ASSERT_EQ(add_volatile<test_case>::type().fun(), 3);
    ASSERT_EQ(add_cv<test_case>::type().fun(), 4);
}

TEST_F(TestTypeTraits, IsVoid) {
    ASSERT_EQ(true, is_void<void>::value);
    ASSERT_EQ(true, is_void<const void>::value);
    ASSERT_EQ(true, is_void<const volatile void>::value);
    ASSERT_EQ(false, is_void<int>::value);
}

TEST_F(TestTypeTraits, IsReference) {
    ASSERT_EQ(false, is_lvalue_reference<TestClass>::value);
    ASSERT_EQ(true, is_lvalue_reference<TestClass&>::value);
    ASSERT_EQ(false, is_lvalue_reference<TestClass&&>::value);
    ASSERT_EQ(false, is_lvalue_reference<int>::value);
    ASSERT_EQ(true, is_lvalue_reference<int&>::value);
    ASSERT_EQ(false, is_lvalue_reference<int&&>::value);

    ASSERT_EQ(false, is_rvalue_reference<TestClass>::value);
    ASSERT_EQ(false, is_rvalue_reference<TestClass&>::value);
    ASSERT_EQ(true, is_rvalue_reference<TestClass&&>::value);
    ASSERT_EQ(false, is_rvalue_reference<int>::value);
    ASSERT_EQ(false, is_rvalue_reference<int&>::value);
    ASSERT_EQ(true, is_rvalue_reference<int&&>::value);

    ASSERT_EQ(false, is_reference<TestClass>::value);
    ASSERT_EQ(true, is_reference<TestClass&>::value);
    ASSERT_EQ(true, is_reference<TestClass&&>::value);
    ASSERT_EQ(false, is_reference<int>::value);
    ASSERT_EQ(true, is_reference<int&>::value);
    ASSERT_EQ(true, is_reference<int&&>::value);
}

TEST_F(TestTypeTraits, IsFloatingPoint) {
    ASSERT_EQ(true, is_floating_point<float>::value);
    ASSERT_EQ(true, is_floating_point<const float>::value);
    ASSERT_EQ(true, is_floating_point<volatile float>::value);
    ASSERT_EQ(true, is_floating_point<const volatile float>::value);
    ASSERT_EQ(true, is_floating_point<double>::value);
    ASSERT_EQ(true, is_floating_point<long double>::value);
    ASSERT_EQ(false, is_floating_point<float*>::value);
}

TEST_F(TestTypeTraits, IsPtr) {
    typedef int (*fun_ptr)(int, int);
    ASSERT_EQ(true, is_pointer<void*>::value);
    ASSERT_EQ(true, is_pointer<const void*>::value);
    ASSERT_EQ(true, is_pointer<volatile const void*>::value);
    ASSERT_EQ(true, is_pointer<volatile void* const>::value);
    ASSERT_EQ(true, is_pointer<void**>::value);
    ASSERT_EQ(true, is_pointer<fun_ptr>::value);
    ASSERT_EQ(false, is_pointer<void>::value);
    ASSERT_EQ(false, is_pointer<int[]>::value);
    ASSERT_EQ(false, is_pointer<int[][10]>::value);
    ASSERT_EQ(false, is_pointer<std::nullptr_t>::value);
    ASSERT_EQ(false, is_pointer<decltype(&TestClass::B)>::value);
}

TEST_F(TestTypeTraits, IsMemberPtr) {
}

TEST_F(TestTypeTraits, IsNullPtr) {
    ASSERT_EQ(true, is_null_pointer<std::nullptr_t>::value);
    ASSERT_EQ(true, is_null_pointer<decltype(nullptr)>::value);
    ASSERT_EQ(false, is_null_pointer<void*>::value);
    ASSERT_EQ(false, is_null_pointer<int*>::value);
}
