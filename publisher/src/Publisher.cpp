#include "Publisher.h"

#include "ZmqPublisher.h"

#include <ConcurrentQueue.h>
#include <Log.h>

namespace net {

Publisher::Publisher(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_running{ false }
  , m_queue{ std::make_unique<ConcurrentQueue<Notification>>() }
  , m_publisher{ std::make_unique<ZmqPublisher>(context, host, port) }
{}

Publisher::~Publisher()
{
  stop();
}

void Publisher::run()
{
  if (m_running) return;

  m_running = true;

  m_thread = std::thread{ &Publisher::process, this };
}

void Publisher::stop()
{
  if (!m_running) return;

  m_running = false;

  if (m_queue->empty()) m_queue->enqueue({});

  if (m_thread.joinable()) m_thread.join();
}

bool Publisher::push(std::string_view message, std::string_view topic)
{
  return m_queue->enqueue({ topic.data(), message.data() });
}

void Publisher::process()
{
  while (m_running) {
    try {
      Notification notification;
      m_queue->wait_dequeue(notification);

      if (!m_running) break;

      if (notification.topic.empty())
        m_publisher->broadcast(notification.message);
      else
        m_publisher->sendOut(notification.topic, notification.message);
    } catch (zmq::error_t& e) {
      Log::error(e.what());
      if (e.num() == ETERM) break;
    }
  }
}

} // namespace net
