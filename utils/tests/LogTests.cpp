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
