#include "Publisher.h"

#include <ZmqPublisher.h>

#include <Log.h>

Publisher::Publisher(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_publisher{ std::make_unique<net::ZmqPublisher>(context, host, port) }
{
}

Publisher::~Publisher()
{
  if (m_thread.joinable())
    m_thread.join();
}

void Publisher::run()
{
  m_thread = std::thread{ &Publisher::process, this };
}

void Publisher::process()
{
  int i = 0;
  while (true) {
    try {
      const std::string message{ "Message #" + std::to_string(++i) };
      m_publisher->broadcast(message);
      std::this_thread::sleep_for(std::chrono::seconds{ 2 });
    } catch (zmq::error_t& e) {
      net::Log::error(e.what());
      if (e.num() == ETERM)
        break;    }
  }
}
