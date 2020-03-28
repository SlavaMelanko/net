#pragma once

#include "Publisher.h"

#include <zmq.hpp>

namespace net {

class ZmqPublisher : public Publisher
{
public:
  ZmqPublisher(zmq::context_t& context, std::string_view host, const uint16_t port);

  void sendOut(const std::string& topic, const std::string& data) override;
  void broadcast(const std::string& data) override;

private:
  zmq::socket_t m_socket;
};

} // namespace net
