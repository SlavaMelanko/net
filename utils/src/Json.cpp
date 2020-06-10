#include "Json.h"

#include <nlohmann/json.hpp>

namespace net::json {

namespace {

class DocumentImpl
{
public:
  explicit DocumentImpl(std::string_view data)
    : m_document{ nlohmann::json::parse(data) }
  {}

  template<class T>
  T extract(std::string_view key) const
  {
    return contains(key) ? get<T>(key) : nullptr;
  }

  bool contains(std::string_view key) const { return m_document.contains(key); }

private:
  template<class T>
  T get(std::string_view key) const
  {
    return m_document[key].get<T>();
  }

  nlohmann::json m_document;
};

} // namespace

Document::Document(std::string_view data)
  : m_impl{ std::make_unique<ParsetImpl>(data) }
{}

std::optional<bool> Document::getBool(std::string_view key) const
{
  return m_impl->extract<bool>(key);
}

std::optional<int> Document::getInt(std::string_view key) const
{
  return m_impl->extract<int>(key);
}

std::optional<double> Document::getDouble(std::string_view key) const
{
  return m_impl->extract<double>(key);
}

std::optional<std::string> Document::getString(std::string_view key) const
{
  return m_impl->extract<std::string>(key);
}

bool Document::contains(std::string_view key) const
{
  return m_document.contains(key);
}

} // namespace net::json
