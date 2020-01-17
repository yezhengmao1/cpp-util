#include <gtest/gtest.h>

#include <PointerTraits.h>

using namespace STL;

class TestPointerTraits : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void TestPointerTraits::SetUpTestCase() {

}

void TestPointerTraits::TearDownTestCase() {

}

TEST_F(TestPointerTraits, PointerTraits) {
    int i = 1;
    void *void_ptr = &i;
    int *int_ptr = pointer_traits<int*>::pointer_to(i);
    ASSERT_EQ(void_ptr, int_ptr);
}
