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
		  -I ../Search \

# 源文件
TEST_SOURCE := $(wildcard *.cpp)
TEST_MAIN := test_main.cpp
TEST_CASE := $(basename $(filter-out $(TEST_MAIN), $(TEST_SOURCE)))

test:
	@echo $(TEST_CASE)

all: $(TEST_CASE)
	$(CC) -o test_all $(INCLUDE) $(TEST_MAIN) $(addsuffix .cpp, $(TEST_CASE)) $(LDFLAGS) $(CFLAGS)

$(TEST_CASE):
	$(CC) -o $@ $(INCLUDE) $(TEST_MAIN) $(addsuffix .cpp, $@) $(LDFLAGS) $(CFLAGS)

.PHONY : clean lcov

clean:
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	rm -f *.info
	rm -f test_all
	rm -f $(foreach obj, $(TEST_CASE), $(obj))

lcov:
	@$(GCOV) *.gcda
	@$(LCOV) --capture --directory ./ --output-file algorithm.info
	@$(LCOV) --remove algorithm.info $(LCOVMASK) -o algorithm.info
	@$(GENHTML) algorithm.info --output-directory result
