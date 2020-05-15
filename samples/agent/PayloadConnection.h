#pragma once

#include <zmq.hpp>

#include <thread>

namespace net {
class Client;
}

class PayloadConnection
{
public:
  PayloadConnection(zmq::context_t& context, const std::string& id, const uint32_t port);
  ~PayloadConnection() noexcept;

  void run();

private:
  void process();

  std::unique_ptr<net::Client> m_client;
  std::thread m_thread;
};
