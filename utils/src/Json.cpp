#include "Json.h"

#include <nlohmann/json.hpp>

namespace net::json {

namespace impl {

class Document
{
public:
  Document() = default;

  explicit Document(std::string_view data)
    : m_document(nlohmann::json::parse(data))
  {}

  Document(Document&& document) noexcept = default;
  Document& operator=(Document&& document) noexcept = default;

  template<class T>
  auto get(std::string_view key) const
  {
    return m_document[std::string{ key }].get<T>();
  }

  template<typename T>
  void set(std::string_view key, T value)
  {
    m_document[std::string{ key }] = value;
  }

  bool contains(std::string_view key) const { return m_document.contains(key); }

  bool empty() const noexcept { return m_document.empty(); }

  std::string dump() const { return m_document.dump(); }

private:
  nlohmann::json m_document;
};

} // namespace impl

Document::Document()
  : m_impl{ std::make_unique<impl::Document>() }
{}

Document::Document(std::string_view data)
  : m_impl{ std::make_unique<impl::Document>(data) }
{}

Document::Document(Document&& document) noexcept = default;

Document& Document::operator=(Document&& document) noexcept = default;

Document::~Document() noexcept {}

Document& Document::operator=(std::string data)
{
  Document document{ std::move(data) };
  std::swap(*this, document);

  return *this;
}

bool Document::getBool(std::string_view key) const
{
  return m_impl->get<bool>(key);
}

void Document::setBool(std::string_view key, const bool value)
{
  m_impl->set(key, value);
}

int Document::getInt(std::string_view key) const
{
  return m_impl->get<int>(key);
}

void Document::setInt(std::string_view key, const int value)
{
  m_impl->set(key, value);
}

double Document::getDouble(std::string_view key) const
{
  return m_impl->get<double>(key);
}

void Document::setDouble(std::string_view key, const double& value)
{
  m_impl->set(key, value);
}

std::string Document::getString(std::string_view key) const
{
  return m_impl->get<std::string>(key);
}

void Document::setString(std::string_view key, const std::string& value)
{
  m_impl->set(key, value);
}

bool Document::contains(std::string_view key) const
{
  return m_impl->contains(key);
}

bool Document::empty() const noexcept
{
  if (!m_impl) return true;

  return m_impl->empty();
}

std::string Document::dump() const
{
  return m_impl->dump();
}

} // namespace net::json
