#pragma once

#include <memory>
#include <string_view>

namespace net::json {

namespace impl {
class Document;
}

class Document
{
public:
  Document();
  explicit Document(std::string_view data);

  Document(Document&& document) noexcept;
  Document& operator=(Document&& document) noexcept;

  ~Document() noexcept;

  Document& operator=(std::string_view data);

  bool getBool(std::string_view key) const;
  void setBool(std::string_view key, const bool value) const;

  int getInt(std::string_view key) const;
  void setInt(std::string_view key, const int value) const;

  double getDouble(std::string_view key) const;
  void setDouble(std::string_view key, const double& value) const;

  std::string getString(std::string_view key) const;
  void setString(std::string_view key, const std::string& value) const;

  bool contains(std::string_view key) const;

  bool empty() const noexcept;

  std::string dump() const;

private:
  std::unique_ptr<impl::Document> m_impl;
};

} // namespace net::json
