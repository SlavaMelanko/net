#include <Log.h>
#include <ZmqWorker.h>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[])
{
  net::Log::initialize();

  try {
    CLI::App app{ "Worker sample" };

    uint32_t port{ 0 };
    app.add_option("-p,--port", port)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    zmq::context_t context{ 1 };
    net::WorkerUnPtr worker = std::make_unique<net::ZmqWorker>(context, port);

    while (true) {
      worker->process();
    }
  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }
}
