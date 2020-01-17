#include <gtest/gtest.h>

#include "Allocator.h"

#include <vector>

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

TEST_F(AllocatorTest, MallocAllocator) {
    int arr[5] = {1, 2, 3, 4, 5};
    std::vector<int> a(arr, arr+5);
    std::vector<int, STL::allocator<int>> b(arr, arr+5);
    for(int i = 0; i < 5; ++i) {
        ASSERT_EQ(a[i], b[i]);
    }
}
