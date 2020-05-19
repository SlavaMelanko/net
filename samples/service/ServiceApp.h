#pragma once

#include <zmq.hpp>

class ServiceApp
{
public:
  ServiceApp(int argc, char* argv[]);

  void run();

private:
  void initializeLogging();
  bool parseArguments(int argc, char* argv[]);
  void initializeConnections();

  uint32_t m_servicePort;
  uint32_t m_publisherPort;

  zmq::context_t m_context{ 1 };
};
