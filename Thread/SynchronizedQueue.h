#ifndef SYNCHRONIZED_QUEUE_H_
#define SYNCHRONIZED_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename T>
class SynchronizedQueue {
  using self_t = SynchronizedQueue;
public:
  SynchronizedQueue(size_t);
  ~SynchronizedQueue() = default;

  SynchronizedQueue(const self_t&) = delete;
  SynchronizedQueue(const self_t&&) = delete;
  SynchronizedQueue& operator=(const self_t&) = delete;
  SynchronizedQueue& operator=(const self_t&&) = delete;

  void push(const T&);
  T pop();

private:
  size_t sMax_;

  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable condition_;
};

template<typename T>
SynchronizedQueue<T>::SynchronizedQueue(size_t num) :
  queue_(),
  mutex_(),
  condition_() {
  sMax_ = num;
}

template<typename T>
void SynchronizedQueue<T>::push(const T& val) {
  std::unique_lock<std::mutex> locker(mutex_);
  condition_.wait(locker, [this]()->bool{ return this->queue_.size() < sMax_; });
  queue_.push(val);
  condition_.notify_one();
}

template<typename T>
T SynchronizedQueue<T>::pop() {
  std::unique_lock<std::mutex> locker(mutex_);
  condition_.wait(locker, [this]()->bool{ return !(this->queue_.empty()); });
  T ret = std::move(queue_.front());
  queue_.pop();
  condition_.notify_one();
  return ret;
}

#endif
