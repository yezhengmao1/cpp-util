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
		  -I ../字符串 \
# 源文件
TEST_MAIN := test_main.cpp

TEST_SOURCE := test_sort
TEST_SOURCE += test_string

all: 
	@ for i in $(TEST_SOURCE); \
	do \
	echo complie $${i};\
	$(CC) $(INCLUDE) $(CFLAGS) -o $$i $(TEST_MAIN) $${i}.cpp $(LDFLAGS); \
	done

.PHONY: lcov
lcov:
	@ for i in $(TEST_SOURCE); \
	do \
	./$$i; \
	gcov $${i}.cpp; \
	done 
	lcov -d . -t 'UnitTest' -o 'UnitTest.info' -b . -c; \
	genhtml -o result UnitTest.info; \
	rm -rf UnitTest.info; \

.PHONY : clean
clean:
	@ for i in $(TEST_SOURCE); \
	do \
	echo rm $${i}; \
	rm $$i; \
	done
	rm *.gcno
	rm *.gcda
