#include <gtest/gtest.h>

#include <Log.h>

class Environment : public testing::Environment
{
public:
  void SetUp() override { utils::Log::initialize(); }
  void TearDown() override {}
};

int main(int argc, char* argv[])
{
  testing::InitGoogleTest(&argc, argv);
  testing::AddGlobalTestEnvironment(new Environment);

  return RUN_ALL_TESTS();
}
