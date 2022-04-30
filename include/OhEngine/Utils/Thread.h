#pragma once

#include <atomic>
#include <mutex>
#include <optional>
#include <queue>
#include <thread>

template <class T> class Thread {
protected:
  std::thread m_Thread;
  std::queue<T> m_Queue;
  mutable std::mutex m_Mutex;
  std::atomic<bool> m_bIsRunning;

  std::optional<T> dequeue() {
    std::lock_guard<std::mutex> lock(m_Mutex);
    if (m_Queue.empty())
      return {};
    auto rtn = m_Queue.front();
    m_Queue.pop();
    return rtn;
  }

  void enqueue(const T &TItem) {
    std::lock_guard<std::mutex> lock(m_Mutex); // lock
    m_Queue.emplace(std::move(TItem));         // enqueue object
  }

  void enqueue(T &&TItem) {
    std::lock_guard<std::mutex> lock(m_Mutex); // lock
    m_Queue.emplace(std::move(TItem));         // enqueue object
  }

  virtual void execute() = 0;

public:
  Thread() { m_bIsRunning = false; }
  virtual ~Thread() {}

  void start() {
    m_Thread = std::thread(&Thread::execute, this);
    m_bIsRunning = true;
  }

  void stop() { m_bIsRunning = false; }

  bool isRunning() { return m_bIsRunning; }
};
