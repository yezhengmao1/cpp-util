## 依赖说明

gtest: 单元测试工具

gcov/lcov: 代码覆盖率生成工具

gcc/clang: 需要支持c++17标准

## 编译说明

将目录切换至 Test 目录下，生成所有测试

```bash
$ make all 
```

生成单个测试用例，test_case 为相应 cpp 文件测试用例

```bash
$ make <test_case>
# 例如生成 test_sort.cpp 测试用例
# $ make sort
```

运行测试用例后，生成代码覆盖率

```bash
$ make lcov
# 设置环境变量值 LCOVMASK 文件夹下文件将不会统计覆盖率
```

## 文件说明

### Search - 搜索算法

[二分搜索](http://hh-yzm.com/index.php/archives/42/)

### Sort - 排序算法

[冒泡排序](http://hh-yzm.com/index.php/archives/34/#3.2.%E5%86%92%E6%B3%A1%E6%8E%92%E5%BA%8F)
[插入排序](http://hh-yzm.com/index.php/archives/34/#3.1.%E6%8F%92%E5%85%A5%E6%8E%92%E5%BA%8F)
[选择排序](http://hh-yzm.com/index.php/archives/34/#3.3.%E9%80%89%E6%8B%A9%E6%8E%92%E5%BA%8F)
[归并排序](http://hh-yzm.com/index.php/archives/34/#3.4.%E5%BD%92%E5%B9%B6%E6%8E%92%E5%BA%8F)
[堆排序](http://hh-yzm.com/index.php/archives/34/#3.5.%E5%A0%86%E6%8E%92%E5%BA%8F)
[快速排序](http://hh-yzm.com/index.php/archives/34/#3.6.%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)

### Tree - 树

