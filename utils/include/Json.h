#pragma once

#include <optional>
#include <string_view>

namespace net::json {

namespace impl {
class Document;
}

class Document
{
public:
  explicit Document(std::string_view data);
  ~Document() noexcept;

  std::optional<bool> getBool(std::string_view key) const;
  std::optional<int> getInt(std::string_view key) const;
  std::optional<double> getDouble(std::string_view key) const;
  std::optional<std::string> getString(std::string_view key) const;

  bool contains(std::string_view key) const;

private:
  std::unique_ptr<impl::Document> m_impl;
};

} // namespace net::json
