#pragma once

#include <string>

namespace net {

class Subscriber
{
public:
    virtual ~Subscriber() noexcept = default;

    /**
     @brief Subscribes to the specified publisher's topic.
     */
    virtual void subscribeTo(const std::string &topic) = 0;

    virtual void subscribeToAllTopics() = 0;

    /**
     @brief Wait for notification from the publisher side.
     */
    virtual std::string waitForNotification() = 0;
};

} // namespace net
