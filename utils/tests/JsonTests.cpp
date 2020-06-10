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
      } catch (const std::runtime_error& e) {
        EXPECT_EQ("Unable to open \"" + filename.string() + "\" file", e.what());
        throw;
      } catch (...) {
        ASSERT_TRUE(false);
      }
    },
    std::runtime_error);
}

TEST(JsonTest, ParseEmptyString)
{
  EXPECT_THROW(Document{ "" });
}
