# 覆盖率生成选项
export LLT = 0
# 编译选项
CC := g++
CFLAGS := -std=c++11 -g
LDFLAGS := -lgtest -pthread
ifeq ($(LLT), 1) 
	CFLAGS += -fprofile-arcs -ftest-coverage
endif
# 头文件
INCLUDE = -I /usr/local/include \
          -I ../排序算法 \
# 源文件
TEST_MAIN := test_main.cpp

TEST_SORT := test_sort

all: 
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TEST_SORT) $(TEST_MAIN) $(TEST_SORT).cpp $(LDFLAGS)

.PHONY: ut
ut:
	@if [ $(LLT) == 1 ]; then \
		./test_sort; \
		gcov $(TEST_SORT).cpp; \
		lcov -d . -t 'UnitTest' -o 'UnitTest.info' -b . -c; \
		genhtml -o result UnitTest.info; \
		rm -rf UnitTest.info; \
	fi; \

.PHONY : clean
clean:
	rm $(TEST_SORT)
	rm *.gcno
	rm *.gcda
