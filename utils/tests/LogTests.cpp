#include <gtest/gtest.h>

#include <Log.h>

using namespace net;

TEST(LogTest, CheckUninitializedConsoleLogger)
{
  EXPECT_NO_THROW(Log::error("error"));
  EXPECT_NO_THROW(Log::info("info"));
  EXPECT_NO_THROW(Log::warn("warn"));
}

TEST(LogTest, CheckConsoleLogger)
{
  EXPECT_TRUE(Log::initialize());
  EXPECT_NO_THROW(Log::error("error"));
  EXPECT_NO_THROW(Log::error("error {}", "message"));
  EXPECT_NO_THROW(Log::info("info"));
  EXPECT_NO_THROW(Log::info("info {}", "message"));
  EXPECT_NO_THROW(Log::warn("warn"));
  EXPECT_NO_THROW(Log::warn("warn {}", "message"));
}
