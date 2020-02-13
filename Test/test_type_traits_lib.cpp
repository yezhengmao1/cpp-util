#include <gtest/gtest.h>

#include <TypeTraits.h>
#include <type_traits>

using namespace STL;

class TestTypeTraitsLibCpp : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void TestTypeTraitsLibCpp::SetUpTestCase() {

}

void TestTypeTraitsLibCpp::TearDownTestCase() {

}

char      val_1 = '0';
wchar_t   val_2 = '1';
char16_t  val_3 = '2';
short     val_4 = 0;
int       val_5 = 0;
long      val_6 = 0;
long long val_7 = 0;

unsigned char      val_8 = 0;
unsigned wchar_t   val_9 = 0;
unsigned short     val_10 = 0;
unsigned int       val_11 = 0;
unsigned long      val_12 = 0;
unsigned long long val_13 = 0;

signed char      val_14 = 0;
signed wchar_t   val_15 = 0;
signed short     val_16 = 0;
signed int       val_17 = 0;
signed long      val_18 = 0;
signed long long val_19 = 0;

bool val_20 = 0;
struct {
    char x;
    int y;
} val_21    = {.x = 0, .y = 0};
class {
public:
    short x;
    long y;
} val_22    = {.x = 0, .y = 0};
enum {
    red    = 0,
    black
} val_23    = red;
union {
    int x;
    char* y;
} val_24    = {.x = 0};

TEST_F(TestTypeTraitsLibCpp, testmain) {

}
