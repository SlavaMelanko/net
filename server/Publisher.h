#pragma once

#include <string>

namespace net {

class Publisher
{
public:
    virtual ~Publisher() noexcept = default;

    /**
     @brief Sends out data to the clients that were subscribed to the specified topic.
     */
    virtual bool sendOut(const std::string &topic, const std::string &data) = 0;
    /**
     @brief Sends out data to all connected clients.
     */
    virtual bool broadcast(const std::string &data) = 0;
};

} // namespace net
