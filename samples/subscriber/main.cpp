#include "ZmqSubscriber.h"

#include <Log.h>

#include <memory>

int main()
{
  utils::InitLogging();

  /**
   Please note, even if you start a subscriber, wait a while, and then start the publisher, the
   subscriber will always miss the first messages that the publisher sends. This is because as the
   subscriber connects to the publisher (something that takes a small but non-zero time), the
   publisher may already be sending messages out.
   */

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
