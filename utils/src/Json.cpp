#include "Json.h"

#include <nlohmann/json.hpp>

namespace net::json {

namespace impl {

class Document
{
public:
  explicit Document(std::string_view data)
    : m_document{ nlohmann::json::parse(data) }
  {}

  template<class T>
  auto extract(std::string_view key) const
  {
    return contains(key) ? std::make_optional<T>(get<T>(key)) : std::nullopt;
  }

  bool contains(std::string_view key) const { return m_document.contains(key); }

private:
  template<class T>
  auto get(std::string_view key) const
  {
    return m_document[std::string{ key }].get<T>();
  }

  nlohmann::json m_document;
};

} // namespace impl

Document::Document(std::string_view data)
  : m_impl{ std::make_unique<impl::Document>(data) }
{}

Document::~Document() noexcept {}

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
  return m_impl->contains(key);
}

} // namespace net::json
