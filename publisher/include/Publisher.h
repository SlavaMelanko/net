#pragma once

#include <zmq.hpp>

#include <thread>

namespace net {

class IPublisher;

template<class T>
class ConcurrentQueue;

class Publisher
{
public:
  struct Notification
  {
    std::string topic;
    std::string message;
  };

  Publisher(zmq::context_t& context, std::string_view host, const uint16_t port);
  ~Publisher();

  void run();
  void stop();

  /**
   * @brief Enqueues notification message.
   *
   * @param message Notification data to be sent.
   * @param topic Topic name where to send out a notification message.
   *              If it is empty, notification will be broadcasted to all subscribers.
   *
   * @return true if notification message has been enqueued successfully, otherwise - false.
   */
  bool push(std::string_view message, std::string_view topic = "");

private:
  void process();

  std::atomic_bool m_running;
  std::unique_ptr<ConcurrentQueue<Notification>> m_queue;
  std::unique_ptr<IPublisher> m_publisher;
  std::thread m_thread;
};

} // namespace net
