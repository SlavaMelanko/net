#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Json.h>

const std::string validJson{
  R"({"id":"tr20200610n123","cs":1234,"amount":123.45,"success":true})"
};
const std::string invalidJson{
  R"({"id":"tr20200610n123","cs":1234,"amount":123.45,"success":true)"
};

TEST(JsonTest, ParseValidJson)
{
  EXPECT_NO_THROW(net::json::Document{ validJson });
}

TEST(JsonTest, ParseInvalidJson)
{
  EXPECT_THROW(
    {
      try {
        net::json::Document{ invalidJson };
      } catch (const std::exception& e) {
        ASSERT_TRUE(true);
        throw;
      } catch (...) {
        ASSERT_TRUE(false);
      }
    },
    std::exception);
}

TEST(JsonTest, ParseEmptyString)
{
  EXPECT_THROW(
    {
      try {
        net::json::Document{ "" };
      } catch (const std::exception& e) {
        ASSERT_TRUE(true);
        throw;
      } catch (...) {
        ASSERT_TRUE(false);
      }
    },
    std::exception);
}

TEST(JsonTest, MoveJson)
{
  net::json::Document document{ validJson };
  EXPECT_FALSE(document.empty());
  auto copy1 = std::move(document);
  EXPECT_FALSE(copy1.empty());
  EXPECT_TRUE(document.empty());
  auto copy2{ std::move(copy1) };
  EXPECT_FALSE(copy2.empty());
  EXPECT_TRUE(copy1.empty());
}

TEST(JsonTest, GetValues)
{
  net::json::Document document{ validJson };

  EPECT_TRUE(document.contains("success") && document.contains("cs") &&
             document.contains("amount") && document.contains("id"));

  EXPECT_TRUE(document.getBool("success"));
  EXPECT_EQ(document.getInt("cs"), 1234);
  EXPECT_EQ(document.getDouble("amount"), 123.45);
  EXPECT_EQ(document.getString("id"), "tr20200610n123");
}

TEST(JsonTest, SetAndGetValues)
{
  net::json::Document document;

  document.setBool("bool", true);
  const auto intVal = 1;
  document.setInt("int", intVal);
  const auto doubleVal = 2.3;
  document.setDouble("double", doubleVal);
  const auto strVal = "Hello";
  document.setString("string", strVal);

  EXPECT_TRUE(document.getBool("bool"));
  EXPECT_EQ(document.getInt("int"), intVal);
  EXPECT_EQ(document.getDouble("double"), doubleVal);
  EXPECT_EQ(document.getString("string"), strVal);
}
