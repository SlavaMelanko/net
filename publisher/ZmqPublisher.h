#pragma once

#include "Publisher.h"

#include <zmq.hpp>

namespace net {

class ZmqPublisher : public Publisher
{
public:
    ZmqPublisher(zmq::context_t &context, const std::string_view host, const uint16_t port);

    bool sendOut(const std::string &topic, const std::string &data) override;
    bool broadcast(const std::string &data) override;

private:
    zmq::socket_t m_publisher;
};

} // namespace net
