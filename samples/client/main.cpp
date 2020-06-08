#include <Log.h>
#include <ZmqClient.h>

#include <zmq.hpp>

#include <CLI/CLI.hpp>

#include <thread>

int main(int argc, char* argv[])
{
  net::Log::initialize();

  try {
    CLI::App app{ "Client sample" };

    std::string id;
    app.add_option("-i,--id", id);
    uint32_t port{ 0 };
    app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    zmq::context_t context{ 1 };
    std::unique_ptr<net::IClient> client =
      std::make_unique<net::ZmqClient>(context, net::MakeConnectionSettings(id, port));

    int i = 0;
    while (true) {
      const auto message{ "Message #" + std::to_string(++i) };
      const auto response = client->send(message);
      net::Log::info("Response: \"{}\"", response);
      std::this_thread::sleep_for(std::chrono::milliseconds{ 200 });
    }
  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }

  return 0;
}
