#include <gtest/gtest.h>

#include "Allocator.h"

#include <vector>

using namespace STL;

class AllocatorTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void AllocatorTest::SetUpTestCase() {

}

void AllocatorTest::TearDownTestCase() {

}

// Test Sruct 
struct TestStruct {
    int x;
    int y;
    double z;
    char w;
};

TEST_F(AllocatorTest, DefaultAllocator) {
    allocator<int> int_allocator;
    allocator<TestStruct> struct_allocator;
    ASSERT_EQ(true, int_allocator == struct_allocator);

    int* int_arr = nullptr;
    ASSERT_EQ(int_arr, nullptr);

    int_arr = int_allocator.allocate(5);
    ASSERT_NE(int_arr, nullptr);
    for(int i = 0; i < 5; ++i) {
        int_arr[i] = i;
    }
    for(int i = 0; i < 5; ++i) {
        ASSERT_EQ(int_arr[i], i);
    }

    int_allocator.deallocate(int_arr, 5);
}

TEST_F(AllocatorTest, VectorAllocator) {
    int arr[5] = {1, 2, 3, 4, 5};
    std::vector<int> a(arr, arr+5);
    std::vector<int, STL::allocator<int>> b(arr, arr+5);
    for(int i = 0; i < 5; ++i) {
        ASSERT_EQ(a[i], b[i]);
    }
}
