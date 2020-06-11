#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Json.h>
using namespace net::json;

const std::string validJson{ R"({"id":"tr20200610n123","amount":123.45,"success":true})" };
const std::string invalidJson{ R"({"id":"tr20200610n123","amount":123.45,"success":true)" };

TEST(JsonTest, ParseValidJson)
{
  EXPECT_NO_THROW(Document{ validJson });
}

TEST(JsonTest, ParseInvalidJson)
{
  EXPECT_THROW(
    {
      try {
        Document{ invalidJson };
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
        Document{ "" };
      } catch (const std::exception& e) {
        ASSERT_TRUE(true);
        throw;
      } catch (...) {
        ASSERT_TRUE(false);
      }
    },
    std::exception);
}
