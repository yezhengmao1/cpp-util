export LCOVMASK = '/usr/local/*'
# 编译选项
CC := g++
CFLAGS := -std=c++11 -g --coverage
LDFLAGS := -lgtest -lpthread
# 头文件
INCLUDE = -I /usr/local/include \
          -I ../Sort \
		  -I ../String \
# 源文件
TEST_MAIN := test_main.cpp

TEST_SORT := test_sort.cpp
TARGET_SORT := test_sort

TEST_STRING := test_string.cpp
TARGET_STRING := test_string

all: sort

sort:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_SORT) $(TEST_MAIN) $(TEST_SORT) $(LDFLAGS)

lcov:
	@gcov *.gcda
	@lcov --capture --directory ./ --output-file algorithm.info
	@lcov --remove algorithm.info $(LCOVMASK) -o algorithm.info
	@genhtml algorithm.info --output-directory result

.PHONY : clean
clean:
	@rm *.gcno
	@rm *.gcda
	@rm *.gcov
	@rm *.info
