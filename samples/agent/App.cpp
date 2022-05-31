#include "App.h"

#include "NotificationConnection.h"
#include "PayloadConnection.h"

#include <Log.h>

#include <CLI/CLI.hpp>

App::App(int argc, char* argv[])
{
  initializeLogging();
  if (!parseArguments(argc, argv))
    throw std::runtime_error{ "Unable to parse arguments" };
  initializeConnections();
}

App::~App() noexcept
{
  m_context.close();
}

void App::run()
{
  m_payloadConnection->run();
  m_notificationConnection->run();
}

void App::initializeLogging()
{
  net::Log::initialize();
}

bool App::parseArguments(int argc, char* argv[])
{
  try {
    CLI::App app{ "Agent app sample" };

    // Parse client connection setting.
    app.add_option("-i,--id", m_id);
    app.add_option("-s,--service-port", m_servicePort)->check(CLI::PositiveNumber);
    // And subscriber settings.
    app.add_option("-p,--publisher-port", m_publisherPort)->check(CLI::PositiveNumber);

    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    net::Log::error(e.what());
    return false;
  }

  return true;
}

void App::initializeConnections()
{
  m_payloadConnection = std::make_unique<PayloadConnection>(m_context, m_id, m_servicePort);
  m_notificationConnection = std::make_unique<NotificationConnection>(m_context, m_publisherPort);
}
