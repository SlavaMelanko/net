#include "ServiceApp.h"

#include <Log.h>

#include <CLI/CLI.hpp>

ServiceApp::ServiceApp(int argc, char* argv[])
{
  initializeLogging();
  if (!parseArguments(argc, argv))
    throw std::runtime_error{ "Unable to parse arguments" };
  initializeConnections();
}

void ServiceApp::run() {}

void ServiceApp::initializeLogging()
{
  net::Log::initialize();
}

bool ServiceApp::parseArguments(int argc, char* argv[])
{
  try {
    CLI::App app{ "Agent app sample" };

    // Parse server binding setting.
    app.add_option("-s,--service-port", m_servicePort)->check(CLI::PositiveNumber);
    // And publisher settings.
    app.add_option("-p,--publisher-port", m_publisherPort)->check(CLI::PositiveNumber);

    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    net::Log::error(e.what());
    return false;
  }

  return true;
}

void ServiceApp::initializeConnections() {}
