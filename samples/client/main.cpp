#include <ZmqClient.h>

#include <Log.h>

#include <zmq.hpp>

#include <thread>

net::ConnectionSettings GetDefaultConnectionSettings()
{
  net::ConnectionSettings connectionSettings;
  connectionSettings.port = 5555;

  return connectionSettings;
}

int main()
{
  utils::Log::initialize();

  try {
    zmq::context_t context{ 1 };
    net::ClientUnPtr client =
      std::make_unique<net::ZmqClient>(context, GetDefaultConnectionSettings());

    int i = 0;
    while (true) {
      const auto message{ "Message #" + std::to_string(++i) };
      const auto response = client->send(message);
      utils::Log::info("Server responded: \"{}\"", response);
      std::this_thread::sleep_for(std::chrono::seconds{ 1 });
    }
  } catch (const std::exception& e) {
    utils::Log::error(e.what());
  }

  return 0;
}
