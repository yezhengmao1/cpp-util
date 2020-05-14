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

  void enqueue(const T&);
  T dequeue();

private:
  size_t sMax_;

  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable not_full_;
  std::condition_variable not_empty_;
};

template<typename T>
BlockingQueue<T>::BlockingQueue(size_t num) :
  queue_(),
  mutex_(),
  not_full_(),
  not_empty_() {
  sMax_ = num;
}

template<typename T>
void BlockingQueue<T>::enqueue(const T& val) {
  std::unique_lock<std::mutex> locker(mutex_);
  if(queue_.size() >= sMax_) {
    not_full_.wait(locker, [this]()->bool{ return this->queue_.size() < sMax_; });
  }
  queue_.push(val);
  not_empty_.notify_one();
}

template<typename T>
T BlockingQueue<T>::dequeue() {
  std::unique_lock<std::mutex> locker(mutex_);
  if(queue_.empty()) {
    not_empty_.wait(locker, [this]()->bool{ return !(this->queue_.empty()); });
  }
  T ret = std::move(queue_.front());
  queue_.pop();
  not_full_.notify_one();
  return ret;
}

#endif
