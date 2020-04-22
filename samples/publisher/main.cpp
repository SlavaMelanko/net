#include <Log.h>
#include <ZmqPublisher.h>

#include <CLI/CLI.hpp>

#include <thread>

int main(int argc, char* argv[])
{
  utils::Log::initialize();

  try {
    CLI::App app{ "Publisher sample" };

    std::string host{ "127.0.0.1" };
    app.add_option("-o,--host", host)->check(CLI::ValidIPV4);
    uint32_t port{ 0 };
    app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    zmq::context_t context{ 1 };
    net::PublisherUnPtr publisher = std::make_unique<net::ZmqPublisher>(context, host, port);

    int i = 0;
    while (true) {
      const std::string message{ "Message #" + std::to_string(++i) };
      publisher->broadcast(message);
      std::this_thread::sleep_for(std::chrono::seconds{ 1 });
    }
  } catch (const std::exception& e) {
    utils::Log::error(e.what());
  }

  return 0;
}
