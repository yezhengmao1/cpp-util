#include <gtest/gtest.h>

#include "ThreadPool.h"

class ThreadPoolTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ThreadPoolTest::SetUpTestCase() {

}

void ThreadPoolTest::TearDownTestCase() {

}

double TestThreadPoolSize(int pNum, int tNum, std::vector<std::future<int>>& rets) {
  ThreadPool tp(pNum);

  auto start = std::chrono::system_clock::now();
  for(int i = 0; i < tNum; ++i) {
    rets.emplace_back(tp.addTask([i]()->int {
          std::this_thread::sleep_for(std::chrono::milliseconds(100));
          return i;
        }
    ));
  }
  for(int i = 0; i < tNum; ++i) {
    rets[i].wait();
  }
  auto end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}

TEST_F(ThreadPoolTest, ThreadPoolSizeGE) {
  std::vector<std::future<int>> ret;
  double t = TestThreadPoolSize(10, 10, ret);
  for(int i = 0; i < ret.size(); ++i) {
    ASSERT_EQ(ret[i].get(), i);
  }
  ASSERT_GT(t, 0.09);
}

TEST_F(ThreadPoolTest, ThreadPoolSizeLE) {
  std::vector<std::future<int>> ret;
  double t = TestThreadPoolSize(1, 2, ret);
  for(int i = 0; i < ret.size(); ++i) {
    ASSERT_EQ(ret[i].get(), i);
  }
  ASSERT_GT(t, 0.199);
}

TEST_F(ThreadPoolTest, ThreadPoolDtor) {
  auto start = std::chrono::system_clock::now();
  {
    std::shared_ptr<ThreadPool> pTp = std::make_shared<ThreadPool>(10);
    for(int i = 0; i < 10; ++i) {
      pTp->addTask([]{ std::this_thread::sleep_for(std::chrono::milliseconds(100)); });
    }
  }
  auto end = std::chrono::system_clock::now();

  auto ndtorStart = std::chrono::system_clock::now();
  std::shared_ptr<ThreadPool> pTp = std::make_shared<ThreadPool>(10);
  for(int i = 0; i < 10; ++i) {
      pTp->addTask([]{ std::this_thread::sleep_for(std::chrono::milliseconds(100)); });
  }
  auto ndtorEnd = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;
  std::chrono::duration<double> ndtor_elapsed_seconds = ndtorEnd - ndtorStart;

  ASSERT_GT(elapsed_seconds.count(), 0.0999);
  ASSERT_LE(ndtor_elapsed_seconds.count(), 0.1000);
}

constexpr int iMax = 5e5;

bool IsPrime(int n) {
  for(int i = 2; i <= n / 2; ++i) {
    if(n % i == 0) {
      return false;
    }
  }
  return true;
}

TEST_F(ThreadPoolTest, PrimeSingleThread) {
  for(int i = 2; i <= iMax; ++i) {
    IsPrime(i);
  }
}

TEST_F(ThreadPoolTest, PrimeThreadPool) {
  ThreadPool p(10);
  for(int i = 2; i <= iMax; ++i) {
    p.addTask(IsPrime, i);
  }
}
