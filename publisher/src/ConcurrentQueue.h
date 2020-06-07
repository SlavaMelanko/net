#pragma once

#include <moodycamel/blockingconcurrentqueue.h>

namespace net {

template<class T>
class ConcurrentQueue
{
public:
  inline bool enqueue(T const& item) { return m_queue.enqueue(item); }

  inline bool enqueue(T&& item) { return m_queue.enqueue(std::move(item)); }

  template<typename U>
  inline void wait_dequeue(U& item)
  {
    m_queue.wait_dequeue(item);
  }

  inline size_t size() const { return m_queue.size_approx(); }

  inline bool empty() const { return size() == 0; }

private:
  moodycamel::BlockingConcurrentQueue<T> m_queue;
};

} // namespace net
