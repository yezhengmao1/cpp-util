export LCOVMASK = '/usr/local/*'
# 编译选项
CC := g++
CFLAGS := -std=c++17 -g --coverage
LDFLAGS := -lgtest -lpthread
# 头文件
INCLUDE = -I /usr/local/include \
		  -I ../STL \
          -I ../Sort \
		  -I ../Tree \
		  -I ../String \
# 源文件
TEST_MAIN := test_main.cpp

TEST_SORT := test_sort.cpp
TARGET_SORT := test_sort

TEST_STRING := test_string.cpp
TARGET_STRING := test_string

TEST_TREE := test_tree.cpp
TARGET_TREE := test_tree

TEST_ALLOCATOR := test_allocator.cpp
TARGET_ALLOCATOR := test_allocator

TEST_TYPETRAITS := test_type_traits.cpp
TARGET_TYPETRAITS := test_type_traits

all: sort tree allocator type_traits

sort:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_SORT) $(TEST_MAIN) $(TEST_SORT) $(LDFLAGS)

tree:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_TREE) $(TEST_MAIN) $(TEST_TREE) $(LDFLAGS)

allocator:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_ALLOCATOR) $(TEST_MAIN) $(TEST_ALLOCATOR) $(LDFLAGS)

type_traits:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_TYPETRAITS) $(TEST_MAIN) $(TEST_TYPETRAITS) $(LDFLAGS)

lcov:
	@gcov *.gcda
	@lcov --capture --directory ./ --output-file algorithm.info
	@lcov --remove algorithm.info $(LCOVMASK) -o algorithm.info
	@genhtml algorithm.info --output-directory result

.PHONY : clean
clean:
	@rm $(TARGET_SORT)
	@rm $(TARGET_TREE)
	@rm $(TARGET_ALLOCATOR)
	@rm $(TARGET_TYPETRAITS)
	@rm *.gcno
	@rm *.gcda
	@rm *.gcov
	@rm *.info
