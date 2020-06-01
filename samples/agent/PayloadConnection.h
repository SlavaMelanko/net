#pragma once

#include "Connection.h"

#include <zmq.hpp>

#include <thread>

namespace net {
class Client;
}

class PayloadConnection : public Connection
{
public:
  PayloadConnection(zmq::context_t& context, const std::string& id, const uint32_t port);
  ~PayloadConnection() noexcept;

  void run() override;

private:
  void process() override;

  std::unique_ptr<net::Client> m_client;
  std::thread m_thread;
};
