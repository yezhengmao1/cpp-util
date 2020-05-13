#include <gtest/gtest.h>

#include "SynchronizedQueue.h"

#include <memory>
#include <thread>

class SynchronizedQueueTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void SynchronizedQueueTest::SetUpTestCase() {

}

void SynchronizedQueueTest::TearDownTestCase() {

}

TEST_F(SynchronizedQueueTest, SyncQueueCTorDtor) {
  {
  std::shared_ptr<SynchronizedQueue<int>> pQ = 
    std::make_shared<SynchronizedQueue<int>>(10);
  }
  SynchronizedQueue<int> q(10);
}

TEST_F(SynchronizedQueueTest, SyncQueueAdd) {
  SynchronizedQueue<int> q(10);
  for(int i = 0; i < 10; ++i) {
    q.push(i);
  }
  for(int i = 0; i < 10; ++i) {
    int t = q.pop();
    ASSERT_EQ(i, t);
  }
}

void ConsumerProducer(int item, int iCt, int iPt) {
  std::shared_ptr<SynchronizedQueue<int>> q = 
    std::make_shared<SynchronizedQueue<int>>(10);

  std::thread p([q, item, iPt]{
        for(int i = 0; i < item; ++i) {
          q->push(i);
          std::this_thread::sleep_for(std::chrono::milliseconds(iPt));
        }
      });
  std::thread c([q, item, iCt]{
        int cmp = 0;
        while(true) {
          int i = q->pop();
          ASSERT_EQ(cmp, i);
          ++cmp;
          if(cmp == item) { return; }
          std::this_thread::sleep_for(std::chrono::milliseconds(iCt));
        }
      });

  p.join();
  c.join();
}

TEST_F(SynchronizedQueueTest, ConsumerFasterProducer) {
  ConsumerProducer(100, 1, 10);
}

TEST_F(SynchronizedQueueTest, ProducerFasterConsumer) {
  ConsumerProducer(100, 10, 1);
}
