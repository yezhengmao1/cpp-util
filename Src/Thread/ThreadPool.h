#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <vector>
#include <queue>
#include <mutex>
#include <thread>
#include <future>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
  ThreadPool(size_t num);
  ~ThreadPool();

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool(const ThreadPool&&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&&) = delete;

  template<typename Func, typename ...Args>
  auto addTask(Func&& f, Args&& ...args) -> std::future<decltype(f(args...))>;

private:
  bool stop_;
  std::mutex mutex_;
  std::condition_variable condition_;
  std::vector<std::thread> threads_;
  std::queue<std::function<void()>> tasks_;
};

ThreadPool::ThreadPool(size_t num) : 
  stop_(false),
  mutex_(),
  condition_(),
  threads_(),
  tasks_() {
  for(size_t i = 0; i < num; ++i) {
    threads_.emplace_back(std::thread([this]{
      std::function<void()> task;
      while(true){
        {
          std::unique_lock<std::mutex> locker(this->mutex_);
          this->condition_.wait(
            locker,
            [this]()->bool{
              return this->stop_ || !this->tasks_.empty();
            }
          );
          if(this->stop_ && this->tasks_.empty()) {
            return;
          }
          task = std::move(this->tasks_.front());
          this->tasks_.pop();
        }
        task();
      }
    }));
  }
}

ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> locker(this->mutex_);
    stop_ = true;
  }
  condition_.notify_all();
  for(auto& thread : threads_) {
    thread.join();
  }
}

template<typename Func, typename ...Args>
auto ThreadPool::addTask(Func&& f, Args&& ...args) -> std::future<decltype(f(args...))> {
  using ret_t    = decltype(f(args...));
  using task_t   = std::packaged_task<ret_t()>;
  using future_t = std::future<ret_t>;
  task_t *task = new task_t(std::bind(f, args...));
  future_t ret = task->get_future();
  {
    std::lock_guard<std::mutex> locker(mutex_);
    tasks_.push([task]{ (*task)(); delete task; });
  }
  condition_.notify_one();
  return ret;
}

#endif
