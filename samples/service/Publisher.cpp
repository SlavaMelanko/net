#include "Publisher.h"

#include <Publisher.h>

#include <Log.h>

Publisher::Publisher(zmq::context_t& context, std::string_view host, const uint16_t port)
  : m_publisher{ std::make_unique<net::Publisher>(context, host, port) }
{}

Publisher::~Publisher()
{
  stop();
}

void Publisher::run()
{
  m_publisher->run();
}

void Publisher::stop()
{
  m_publisher->stop();
}

bool Publisher::push(std::string_view message, std::string_view topic)
{
  return m_publisher->push(message, topic);
}
