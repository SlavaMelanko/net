#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Log.h>
using namespace net;

TEST(LogTest, CheckOutUninitializedConsoleLogger)
{
  Log::error("error");
  Log::info("info");
  Log::warn("warn");
  EXPECT_TRUE(true);
}

TEST(LogTest, CheckOutConsoleLogger)
{
  Log::initialize();
  Log::error("error");
  Log::error("error {}", "message");
  Log::info("info");
  Log::info("info {}", "message");
  Log::warn("warn");
  Log::warn("warn {}", "message");
  EXPECT_TRUE(true);
}
