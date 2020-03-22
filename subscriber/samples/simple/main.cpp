#include "ZmqSubscriber.h"

#include <Log.h>

#include <memory>

int main()
{
  utils::InitLogging();

  try {
    zmq::context_t context{ 1 };
    std::unique_ptr<net::Subscriber> subscriber =
      std::make_unique<net::ZmqSubscriber>(context, "127.0.0.1", 5555);
    subscriber->subscribeToAllTopics();

    while (true) {
      subscriber->waitForNotification();
    }
  } catch (const std::exception& e) {
    ERROR(e.what());
  }

  return 0;
}
