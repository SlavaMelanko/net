#include "NotificationConnection.h"

#include <Log.h>
#include <ZmqSubscriber.h>

NotificationConnection::NotificationConnection(zmq::context_t& context, const uint32_t port)
  : m_subscriber{ std::make_unique<net::ZmqSubscriber>(context, port) }
{
  m_subscriber->subscribeToAllTopics();
}

NotificationConnection::~NotificationConnection() noexcept
{
  if (m_thread.joinable()) m_thread.join();
}

void NotificationConnection::run()
{
  m_thread = std::thread{ &NotificationConnection::process, this };
}

void NotificationConnection::process()
{
  try {
    while (true) {
      std::this_thread::sleep_for(std::chrono::seconds{ 1 });
      m_subscriber->waitForNotification();
    }
  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }
}
