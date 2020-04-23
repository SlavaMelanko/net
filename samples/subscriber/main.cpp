#include <Log.h>
#include <ZmqSubscriber.h>

#include <CLI/CLI.hpp>

/**
 * Please note, even if you start a subscriber, wait a while, and then start the publisher,
 * the subscriber will always miss the first messages that the publisher sends. This is because as
 * the subscriber connects to the publisher (something that takes a small but non-zero time),
 * the publisher may already be sending messages out.
 */

int main(int argc, char* argv[])
{
  net::Log::initialize();

  try {
    CLI::App app{ "Subscriber sample" };

    std::string host{ "127.0.0.1" };
    app.add_option("-o,--host", host)->check(CLI::ValidIPV4);
    uint32_t port{ 0 };
    app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    zmq::context_t context{ 1 };
    net::SubscriberUnPtr subscriber = std::make_unique<net::ZmqSubscriber>(context, host, port);
    subscriber->subscribeToAllTopics();

    while (true) {
      subscriber->waitForNotification();
    }
  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }

  return 0;
}
