#include <Log.h>
#include <ZmqBroker.h>

#include <zhelpers.hpp>

#include <CLI/CLI.hpp>

int main(int argc, char* argv[])
{
  net::Log::initialize();

  try {
    CLI::App app{ "Broker sample" };

    uint32_t frontendPort{ 0 };
    app.add_option("-f,--frontend-port", frontendPort)->check(CLI::PositiveNumber);
    uint32_t backendPort{ 0 };
    app.add_option("-b,--backend-port", backendPort)->check(CLI::PositiveNumber);

    CLI11_PARSE(app, argc, argv);

    net::ZmqBroker broker{ frontendPort, backendPort };

    broker.poll();

  } catch (const std::exception& e) {
    net::Log::error(e.what());
  }

  return 0;
}
