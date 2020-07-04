#pragma once

#include <Json.h>

#include <string>

namespace net {

class Request
{
public:
  Request() = default;
  Request(const std::string& clientId,
          const std::string& delimiter,
          const std::string& action,
          const std::string& message);

  inline std::string getClientId() const noexcept { return m_clientId; }
  void setClientId(const std::string& clientId);

  inline std::string getDelimiter() const noexcept { return m_delimiter; }
  void setDelimiter(const std::string& delimiter);

  inline std::string getAction() const noexcept { return m_action; }
  void setAction(const std::string& action);

  inline const json::Document& getMessage() const noexcept { return m_message; }
  void setMessage(const std::string& message);

private:
  std::string m_clientId;
  std::string m_delimiter;
  std::string m_action;
  json::Document m_message;
};

} // namespace net
