#include <gtest/gtest.h>

class TemplateTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void TemplateTest::SetUpTestCase() {

}

void TemplateTest::TearDownTestCase() {

}


