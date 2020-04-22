#pragma once

#include <memory>
#include <string>

namespace net {

class Subscriber
{
public:
  virtual ~Subscriber() noexcept = default;

  /**
   @brief Subscribes to the specified publisher's topic.
   */
  virtual void subscribeTo(const std::string& topic) = 0;

  virtual void subscribeToAllTopics() = 0;

  /**
   @brief Wait for notification from the publisher side.
   */
  virtual std::string waitForNotification() = 0;
};

using SubscriberUnPtr = std::unique_ptr<Subscriber>;

} // namespace net
