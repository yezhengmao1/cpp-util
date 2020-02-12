export LCOVMASK = '/usr/local/*'
GCOV := gcov
LCOV := lcov
GENHTML := genhtml
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

TEST_TYPETRAITSLIB = test_type_traits_lib.cpp
TARGET_TYPETRAITSLIB = test_type_traits_lib

TEST_POINTERTRAITS := test_pointer_traits.cpp
TARGET_POINTERTRAITS := test_pointer_traits

TEST_ALLOCATORTRAITS := test_allocator_traits.cpp
TARGET_ALLOCATORRAITS := test_allocator_traits

all: sort \
	 tree \
	 allocator \
	 type_traits \
	 type_traits_lib \
	 pointer_traits \
	 allocator_traits

sort:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_SORT) $(TEST_MAIN) $(TEST_SORT) $(LDFLAGS)

tree:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_TREE) $(TEST_MAIN) $(TEST_TREE) $(LDFLAGS)

allocator:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_ALLOCATOR) $(TEST_MAIN) $(TEST_ALLOCATOR) $(LDFLAGS)

type_traits:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_TYPETRAITS) $(TEST_MAIN) $(TEST_TYPETRAITS) $(LDFLAGS)

type_traits_lib:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_TYPETRAITSLIB) $(TEST_MAIN) $(TEST_TYPETRAITSLIB) $(LDFLAGS)

pointer_traits:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_POINTERTRAITS) $(TEST_MAIN) $(TEST_POINTERTRAITS) $(LDFLAGS)

allocator_traits:
	$(CC) $(INCLUDE) $(CFLAGS) -o $(TARGET_ALLOCATORRAITS) $(TEST_MAIN) $(TEST_ALLOCATORTRAITS) $(LDFLAGS)

lcov:
	@$(GCOV) *.gcda
	@$(LCOV) --capture --directory ./ --output-file algorithm.info
	@$(LCOV) --remove algorithm.info $(LCOVMASK) -o algorithm.info
	@$(GENHTML) algorithm.info --output-directory result

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
