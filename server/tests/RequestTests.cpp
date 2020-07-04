#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Request.h>

#include <type_traits>

TEST(RequestTest, CheckTypeTraits)
{
  using Type = net::Request;

  // Primary type categories.
  EXPECT_TRUE(std::is_class_v<Type>);

  // Type properties.
  EXPECT_FALSE(std::is_trivially_copyable_v<Type>);
#if defined(__APPLE__) || defined(__linux__)
  EXPECT_TRUE(std::is_standard_layout_v<Type>);
#elif defined(_WIN32)
  // AppVeyor: true for release, and false for debug?
  // EXPECT_FALSE(std::is_standard_layout_v<Type>);
#endif
  EXPECT_FALSE(std::is_abstract_v<Type>);
  EXPECT_FALSE(std::is_polymorphic_v<Type>);
  EXPECT_FALSE(std::is_final_v<Type>);

  // Supported operations.
  EXPECT_TRUE(std::is_default_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_default_constructible_v<Type>);
  EXPECT_FALSE(std::is_nothrow_default_constructible_v<Type>);

  EXPECT_FALSE(std::is_copy_constructible_v<Type>);
  EXPECT_FALSE(std::is_copy_assignable_v<Type>);

  EXPECT_TRUE(std::is_move_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_constructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_constructible_v<Type>);

  EXPECT_TRUE(std::is_move_assignable_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_assignable_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_assignable_v<Type>);

  EXPECT_TRUE(std::is_destructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_destructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_destructible_v<Type>);

  EXPECT_FALSE(std::has_virtual_destructor_v<Type>);
}

TEST(RequestTest, CreateWithBadClientID)
{
  EXPECT_THROW(
    {
      try {
        std::make_unique<net::Request>("id", "", "test", "");
      } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(R"(Bad client ID: "id" (length must be at least 5 chars))", e.what());
        throw;
      } catch (...) {
        EXPECT_TRUE(false);
      }
    },
    std::invalid_argument);
}

TEST(RequestTest, CreateWithBadDelimiter)
{
  EXPECT_THROW(
    {
      try {
        std::make_unique<net::Request>("client_id", "|", "test", "");
      } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(R"(Bad delimiter: "|" (must be ""))", e.what());
        throw;
      } catch (...) {
        EXPECT_TRUE(false);
      }
    },
    std::invalid_argument);
}

TEST(RequestTest, CreateWithBadAction)
{
  EXPECT_THROW(
    {
      try {
        std::make_unique<net::Request>("client_id", "", "", "");
      } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(R"(Bad action)", e.what());
        throw;
      } catch (...) {
        EXPECT_TRUE(false);
      }
    },
    std::invalid_argument);
}

TEST(RequestTest, CreateWithBadMessage)
{
  EXPECT_THROW(
    {
      try {
        std::make_unique<net::Request>("client_id", "", "test", "!JSON");
      } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(R"(Bad messsage: "!JSON")", e.what());
        throw;
      } catch (...) {
        EXPECT_TRUE(false);
      }
    },
    std::invalid_argument);
}

TEST(RequestTest, CreateWithEmptyMessage)
{
  net::Request request{ "client_id", "", "test", "" };
  EXPECT_EQ(request.getClientId(), "client_id");
  EXPECT_EQ(request.getDelimiter(), "");
  EXPECT_EQ(request.getAction(), "test");
  EXPECT_TRUE(request.getMessage().empty());
}

TEST(RequestTest, CreateValidRequest)
{
  net::Request request{ "client_id", "", "test", R"({"value":10})" };
  EXPECT_EQ(request.getClientId(), "client_id");
  EXPECT_EQ(request.getDelimiter(), "");
  EXPECT_EQ(request.getAction(), "test");
  EXPECT_EQ(request.getMessage().getInt("value"), 10);
}
