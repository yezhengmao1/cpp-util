#include <gtest/gtest.h>

#include <TypeTraits.h>
#include <type_traits>

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

union TestUnion {
    int x;
    float y;
    char *m;
};

enum TestEnum {
    x = 0,
    y,
    z,
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

TEST_F(TestTypeTraits, Conditional) {
    bool kase = false;
    kase = std::is_same<int, typename conditional<true, int, double>::type>::value;
    kase &= std::is_same<double, typename conditional<false, int, double>::type>::value;
    ASSERT_EQ(kase, true);
}

TEST_F(TestTypeTraits, IsUnionEnumClass) {
    ASSERT_EQ(true, is_union<TestUnion>::value);
    ASSERT_EQ(false, is_union<TestClass>::value);
    ASSERT_EQ(false, is_union<TestEnum>::value);
    ASSERT_EQ(false, is_union<int>::value);
    ASSERT_EQ(false, is_enum<TestUnion>::value);
    ASSERT_EQ(false, is_enum<TestClass>::value);
    ASSERT_EQ(true, is_enum<TestEnum>::value);
    ASSERT_EQ(false, is_enum<int>::value);
    ASSERT_EQ(false, is_class<TestUnion>::value);
    ASSERT_EQ(true, is_class<TestClass>::value);
    ASSERT_EQ(false, is_class<TestEnum>::value);
    ASSERT_EQ(false, is_class<int>::value);
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

TEST_F(TestTypeTraits, RemovePointer) {
    std::vector<bool> truekase = {
        is_same<int, remove_pointer<int*>::type>::value,
        is_same<int, remove_pointer<int* const>::type>::value,
        is_same<int, remove_pointer<int* volatile const>::type>::value,
    };
    std::vector<bool> falsekase = {
        is_same<int, remove_pointer<const int*>::type>::value,
    };
    for(auto i : truekase) {
        ASSERT_EQ(true, i);
    }
    for(auto i : falsekase) {
        ASSERT_EQ(false, i);
    }
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

TEST_F(TestTypeTraits, IsConst) {
    ASSERT_EQ(true, is_const<const int>::value);
    ASSERT_EQ(false, is_const<const int*>::value);
    ASSERT_EQ(false, is_const<const int&>::value);
    ASSERT_EQ(true, is_const<int* const>::value);
    ASSERT_EQ(false, is_const<typename remove_cv<const int&>::type>::value);
    ASSERT_EQ(true, is_const<typename remove_reference<const int&>::type>::value);
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
    ASSERT_EQ(true, is_pointer<void*>::value);
    ASSERT_EQ(true, is_pointer<const void*>::value);
    ASSERT_EQ(true, is_pointer<volatile const void*>::value);
    ASSERT_EQ(true, is_pointer<volatile void* const>::value);
    ASSERT_EQ(true, is_pointer<void**>::value);
    ASSERT_EQ(true, is_pointer<int(*)(int)>::value);
    ASSERT_EQ(false, is_pointer<void>::value);
    ASSERT_EQ(false, is_pointer<int[]>::value);
    ASSERT_EQ(false, is_pointer<int[][10]>::value);
    ASSERT_EQ(false, is_pointer<std::nullptr_t>::value);
    ASSERT_EQ(false, is_pointer<decltype(&TestClass::B)>::value);
}

TEST_F(TestTypeTraits, IsArray) {
    ASSERT_EQ(false, is_bounded_array<TestClass>::value);
    ASSERT_EQ(false, is_bounded_array<TestClass[]>::value);
    ASSERT_EQ(true, is_bounded_array<TestClass[10]>::value);
    ASSERT_EQ(false, is_bounded_array<int>::value);
    ASSERT_EQ(false, is_bounded_array<int[]>::value);
    ASSERT_EQ(true, is_bounded_array<int[10]>::value);
    ASSERT_EQ(true, is_bounded_array<const int[10]>::value);

    ASSERT_EQ(false, is_unbounded_array<TestClass>::value);
    ASSERT_EQ(true, is_unbounded_array<TestClass[]>::value);
    ASSERT_EQ(false, is_unbounded_array<TestClass[10]>::value);
    ASSERT_EQ(false, is_unbounded_array<int>::value);
    ASSERT_EQ(true, is_unbounded_array<int[]>::value);
    ASSERT_EQ(false, is_unbounded_array<int[10]>::value);

    ASSERT_EQ(false, is_array<TestClass>::value);
    ASSERT_EQ(true, is_array<TestClass[]>::value);
    ASSERT_EQ(true, is_array<TestClass[10]>::value);
    ASSERT_EQ(false, is_array<int>::value);
    ASSERT_EQ(true, is_array<int[]>::value);
    ASSERT_EQ(true, is_array<int[10]>::value);
}

TEST_F(TestTypeTraits, IsIntegral) {
    ASSERT_EQ(false, is_integral<double>::value);
    ASSERT_EQ(false, is_integral<int*>::value);
    ASSERT_EQ(false, is_integral<TestClass>::value);
    ASSERT_EQ(true, is_integral<int>::value);
    ASSERT_EQ(true, is_integral<decltype('a')>::value);
    ASSERT_EQ(true, is_integral<decltype(true)>::value);
    ASSERT_EQ(true, is_integral<decltype(-100)>::value);
    ASSERT_EQ(true, is_integral<signed int>::value);
}

TEST_F(TestTypeTraits, IsFunction) {
    ASSERT_EQ(true, is_function<int(int)>::value);
    ASSERT_EQ(true, is_function<void(int)>::value);
    ASSERT_EQ(true, is_function<void(int, int, int*, int[])>::value);
    ASSERT_EQ(false, is_function<decltype(&TestClass::Func)>::value);
    ASSERT_EQ(false, is_function<void(*)(int, int)>::value);
}

TEST_F(TestTypeTraits, IsMemberPtr) {
    ASSERT_EQ(true, is_member_pointer<decltype(&TestClass::Func)>::value);
    ASSERT_EQ(true, is_member_pointer<int TestClass::*>::value);
    ASSERT_EQ(true, is_member_pointer<decltype(&TestClass::B)>::value);
    ASSERT_EQ(false, is_member_pointer<int>::value);
    ASSERT_EQ(false, is_member_pointer<int(void)>::value);
    ASSERT_EQ(true, is_member_function_pointer<decltype(&TestClass::Func)>::value);
    ASSERT_EQ(false, is_member_function_pointer<int TestClass::*>::value);
    ASSERT_EQ(false, is_member_object_pointer<decltype(&TestClass::Func)>::value);
    ASSERT_EQ(true, is_member_object_pointer<int TestClass::*>::value);
    ASSERT_EQ(false, is_member_object_pointer<int*>::value);
}

TEST_F(TestTypeTraits, IsNullPtr) {
    ASSERT_EQ(true, is_null_pointer<std::nullptr_t>::value);
    ASSERT_EQ(true, is_null_pointer<decltype(nullptr)>::value);
    ASSERT_EQ(false, is_null_pointer<void*>::value);
    ASSERT_EQ(false, is_null_pointer<int*>::value);
}

TEST_F(TestTypeTraits, IsArithmetic) {
    ASSERT_EQ(false, is_arithmetic<TestClass>::value);
    ASSERT_EQ(true, is_arithmetic<bool>::value);
    ASSERT_EQ(true, is_arithmetic<int>::value);
    ASSERT_EQ(true, is_arithmetic<int const>::value);
    ASSERT_EQ(true, is_arithmetic<const volatile int>::value);
    ASSERT_EQ(false, is_arithmetic<int*>::value);
    ASSERT_EQ(false, is_arithmetic<int&>::value);
    ASSERT_EQ(true, is_arithmetic<char>::value);
    ASSERT_EQ(true, is_arithmetic<float>::value);
    ASSERT_EQ(true, is_arithmetic<double>::value);
    ASSERT_EQ(true, is_arithmetic<unsigned char>::value);
}

TEST_F(TestTypeTraits, IsSigned) {
    ASSERT_EQ(std::is_signed<char>::value, is_signed<char>::value);
    ASSERT_EQ(std::is_signed<unsigned char>::value, is_signed<unsigned char>::value);
    ASSERT_EQ(std::is_signed<signed char>::value, is_signed<signed char>::value);
    ASSERT_EQ(true, is_signed<char>::value);
    ASSERT_EQ(false, is_signed<TestClass>::value);
}

TEST_F(TestTypeTraits, IsUnsigned) {
    ASSERT_EQ(std::is_unsigned<char>::value, is_unsigned<char>::value);
    ASSERT_EQ(std::is_unsigned<unsigned char>::value, is_unsigned<unsigned char>::value);
    ASSERT_EQ(std::is_unsigned<signed char>::value, is_unsigned<signed char>::value);
    ASSERT_EQ(false, is_unsigned<float>::value);
    ASSERT_EQ(false, is_unsigned<double>::value);
    ASSERT_EQ(false, is_unsigned<char>::value);
    ASSERT_EQ(true, is_unsigned<unsigned char>::value);
}
