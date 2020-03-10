#pragma once

#include "Publisher.h"

#include <zmq.hpp>

namespace net {

class TcpServer
{
public:
  TcpServer();

  void run();

private:
  zmq::context_t m_context;
  std::unique_ptr<Publisher> m_publisher;
};

} // namespace net
