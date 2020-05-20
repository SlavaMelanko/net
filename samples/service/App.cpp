#include "App.h"

#include "Service.h"

#include <Log.h>

#include <CLI/CLI.hpp>

App::App(int argc, char* argv[])
{
  initializeLogging();
  if (!parseArguments(argc, argv))
    throw std::runtime_error{ "Unable to parse arguments" };
  bind();
}

App::~App()
{
  m_context.close();
}

void App::run() {}

void App::initializeLogging()
{
  net::Log::initialize();
}

bool App::parseArguments(int argc, char* argv[])
{
  try {
    CLI::App app{ "Service app sample" };

    // Parse server binding setting.
    app.add_option("-s,--server-port", m_serverPort)->check(CLI::PositiveNumber);
    // And publisher settings.
    app.add_option("-p,--publisher-port", m_publisherPort)->check(CLI::PositiveNumber);

    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    net::Log::error(e.what());
    return false;
  }

  return true;
}

void App::bind()
{
  m_service = std::make_unique<Service>(m_context, "127.0.0.1", m_serverPort);
}
