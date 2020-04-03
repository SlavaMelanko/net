#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Log.h>

TEST(LoggingTest, CheckConsoleLogger)
{
  utils::InitLogging();
  CRIT("Critical")
  DEBUG("Debug");
  ERROR("Error");
  INFO("Info");
  TRACE("Trace");
  WARN("Warning");
  EXPECT_TRUE(true);
}

TEST(LogTest, CheckOutUninitializedConsoleLogger)
{
  utils::Log::error("error");
  utils::Log::info("info");
  utils::Log::warn("warn");
  EXPECT_TRUE(true);
}

TEST(LogTest, CheckOutConsoleLogger)
{
  utils::Log::initialize();
  utils::Log::error("error");
  utils::Log::error("error {}", "message");
  utils::Log::info("info");
  utils::Log::info("info {}", "message");
  utils::Log::warn("warn");
  utils::Log::warn("warn {}", "message");
  EXPECT_TRUE(true);
}
