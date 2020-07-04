#include "Request.h"

#include <Log.h>

#include <fmt/format.h>

namespace net {

Request::Request(const std::string& clientId,
                 const std::string& delimiter,
                 const std::string& action,
                 const std::string& message)
{
  setClientId(clientId);
  setDelimiter(delimiter);
  setAction(action);
  setMessage(message);

  Log::info("#{}: @{} - \"{}\"", m_clientId, m_action, m_message.dump());
}

void Request::setClientId(const std::string& clientId)
{
  constexpr size_t minimumClientIdLength = 5;

  if (clientId.length() < minimumClientIdLength)
    throw std::invalid_argument{ fmt::format(
      R"(Bad client ID: "{}" (length must be at least 5 chars))", clientId) };

  m_clientId = clientId;
}

void Request::setDelimiter(const std::string& delimiter)
{
  if (!delimiter.empty())
    throw std::invalid_argument{ fmt::format(R"(Bad delimiter: "{}" (must be ""))", delimiter) };

  m_delimiter = delimiter;
}

void Request::setAction(const std::string& action)
{
  if (action.empty()) throw std::invalid_argument{ "Bad action" };

  m_action = action;
}

void Request::setMessage(const std::string& message)
{
  try {
    m_message = message.empty() ? "{}" : message;
  } catch (const std::exception& e) {
    throw std::invalid_argument{ fmt::format(R"(Bad messsage: "{}")", message) };
  }
}

} // namespace net
