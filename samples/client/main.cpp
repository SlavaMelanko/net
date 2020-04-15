#include <ZmqClient.h>

#include <Log.h>

#include <zmq.hpp>

#include <CLI/CLI.hpp>

#include <thread>

net::ConnectionSettings MakeConnectionSettings(const std::string& id, const uint32_t port)
{
  net::ConnectionSettings connectionSettings;
  if (!id.empty())
    connectionSettings.id = id;
  connectionSettings.port = port;

  return connectionSettings;
}

int main(int argc, char* argv[])
{
  utils::Log::initialize();

  CLI::App app{ "Client sample" };

  std::string id;
  app.add_option("-i,--id", id);
  uint32_t port{ 0 };
  app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

  CLI11_PARSE(app, argc, argv);

  try {
    zmq::context_t context{ 1 };
    net::ClientUnPtr client =
      std::make_unique<net::ZmqClient>(context, MakeConnectionSettings(id, port));

    int i = 0;
    while (true) {
      const auto message{ "Message #" + std::to_string(++i) };
      const auto response = client->send(message);
      utils::Log::info("Response: \"{}\"", response);
      std::this_thread::sleep_for(std::chrono::milliseconds{ 250 });
    }
  } catch (const std::exception& e) {
    utils::Log::error(e.what());
  }

  return 0;
}
