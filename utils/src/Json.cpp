#include "Json.h"

#include <nlohmann/json.hpp>

namespace net::json {

namespace impl {

class Document
{
public:
  Document() = default;

  explicit Document(std::string_view data)
    : m_document{ nlohmann::json::parse(data) }
  {}

  template<class T>
  auto extract(std::string_view key) const
  {
    return contains(key) ? std::make_optional<T>(get<T>(key)) : std::nullopt;
  }

  template<typename T>
  void set(std::string_view key, T value)
  {
    m_document[std::string{ key }] = value;
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

Document::Document()
  : m_impl{ std::make_unique<impl::Document>() }
{}

Document::Document(std::string_view data)
  : m_impl{ std::make_unique<impl::Document>(data) }
{}

Document::~Document() noexcept {}

std::optional<bool> Document::getBool(std::string_view key) const
{
  return m_impl->extract<bool>(key);
}

void Document::setBool(std::string_view key, const bool value)
{
  m_impl->set(key, value);
}

std::optional<int> Document::getInt(std::string_view key) const
{
  return m_impl->extract<int>(key);
}

void Document::setInt(std::string_view key, const int value)
{
  m_impl->set(key, value);
}

std::optional<double> Document::getDouble(std::string_view key) const
{
  return m_impl->extract<double>(key);
}

void Document::setDouble(std::string_view key, const double& value)
{
  m_impl->set(key, value);
}

std::optional<std::string> Document::getString(std::string_view key) const
{
  return m_impl->extract<std::string>(key);
}

void Document::setString(std::string_view key, const std::string& value)
{
  m_impl->set(key, value);
}

bool Document::contains(std::string_view key) const
{
  return m_impl->contains(key);
}

} // namespace net::json
