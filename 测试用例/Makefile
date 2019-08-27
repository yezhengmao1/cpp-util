# 编译选项
CC := g++
CFLAGS := -std=c++11 -g
LDFLAGS := /usr/local/lib/libgtest.a \
           /usr/local/lib/libgtest_main.a \
           -lpthread \
# 头文件
INCLUDE = -I /usr/local/include \
          -I ../排序算法 \
# 源文件
TEST_MAIN := test_main.cpp

TEST_SORT := test_sort

all: 
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TEST_SORT) $(TEST_MAIN) $(TEST_SORT).cpp $(LDFLAGS)

.PHONY : clean
clean:
	rm $(TEST_SORT)

