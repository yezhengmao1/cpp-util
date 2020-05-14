#include <gtest/gtest.h>

#include "BlockingQueue.h"

#include <memory>
#include <thread>

class BlockingQueueTest : public ::testing::Test {
protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void BlockingQueueTest::SetUpTestCase() {

}

void BlockingQueueTest::TearDownTestCase() {

}

TEST_F(BlockingQueueTest, SyncQueueCTorDtor) {
  {
  std::shared_ptr<BlockingQueue<int>> pQ = 
    std::make_shared<BlockingQueue<int>>(10);
  }
  BlockingQueue<int> q(10);
}

TEST_F(BlockingQueueTest, SyncQueueAdd) {
  BlockingQueue<int> q(10);
  for(int i = 0; i < 10; ++i) {
    q.enqueue(i);
  }
  for(int i = 0; i < 10; ++i) {
    int t = q.dequeue();
    ASSERT_EQ(i, t);
  }
}

void ConsumerProducer(int item, int iCt, int iPt) {
  std::shared_ptr<BlockingQueue<int>> q = 
    std::make_shared<BlockingQueue<int>>(10);

  std::thread p([q, item, iPt]{
        for(int i = 0; i < item; ++i) {
          q->enqueue(i);
          std::this_thread::sleep_for(std::chrono::milliseconds(iPt));
        }
      });
  std::thread c([q, item, iCt]{
        int cmp = 0;
        while(true) {
          int i = q->dequeue();
          ASSERT_EQ(cmp, i);
          ++cmp;
          if(cmp == item) { return; }
          std::this_thread::sleep_for(std::chrono::milliseconds(iCt));
        }
      });

  p.join();
  c.join();
}

TEST_F(BlockingQueueTest, ConsumerFasterProducer) {
  ConsumerProducer(100, 1, 10);
}

TEST_F(BlockingQueueTest, ProducerFasterConsumer) {
  ConsumerProducer(100, 10, 1);
}
