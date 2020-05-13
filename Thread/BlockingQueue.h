#ifndef BLOCKING_QUEUE_H_
#define BLOCKING_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class BlockingQueue {
  using self_t = BlockingQueue;
public:
  BlockingQueue(size_t);
  ~BlockingQueue() = default;

  BlockingQueue(const self_t&) = delete;
  BlockingQueue(const self_t&&) = delete;
  BlockingQueue& operator=(const self_t&) = delete;
  BlockingQueue& operator=(const self_t&&) = delete;

  void push(const T&);
  T pop();

private:
  size_t sMax_;

  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable condition_;
};

template<typename T>
BlockingQueue<T>::BlockingQueue(size_t num) :
  queue_(),
  mutex_(),
  condition_() {
  sMax_ = num;
}

template<typename T>
void BlockingQueue<T>::push(const T& val) {
  std::unique_lock<std::mutex> locker(mutex_);
  condition_.wait(locker, [this]()->bool{ return this->queue_.size() < sMax_; });
  queue_.push(val);
  condition_.notify_one();
}

template<typename T>
T BlockingQueue<T>::pop() {
  std::unique_lock<std::mutex> locker(mutex_);
  condition_.wait(locker, [this]()->bool{ return !(this->queue_.empty()); });
  T ret = std::move(queue_.front());
  queue_.pop();
  condition_.notify_one();
  return ret;
}

#endif
