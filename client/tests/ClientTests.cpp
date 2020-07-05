#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ZmqClient.h>

#include <type_traits>

TEST(ServerTest, CheckTypeTraits)
{
  using Type = net::ZmqClient;

  // Primary type categories.
  EXPECT_TRUE(std::is_class_v<Type>);

  // Type properties.
  EXPECT_FALSE(std::is_trivially_copyable_v<Type>);
  EXPECT_FALSE(std::is_abstract_v<Type>);
  EXPECT_TRUE(std::is_polymorphic_v<Type>);
  EXPECT_FALSE(std::is_final_v<Type>);

  // Supported operations.
  EXPECT_FALSE(std::is_default_constructible_v<Type>);

  EXPECT_FALSE(std::is_copy_constructible_v<Type>);

  EXPECT_TRUE(std::is_move_constructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_constructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_constructible_v<Type>);

  EXPECT_FALSE(std::is_copy_assignable_v<Type>);

  EXPECT_TRUE(std::is_move_assignable_v<Type>);
  EXPECT_FALSE(std::is_trivially_move_assignable_v<Type>);
  EXPECT_TRUE(std::is_nothrow_move_assignable_v<Type>);

  EXPECT_TRUE(std::is_destructible_v<Type>);
  EXPECT_TRUE(std::is_nothrow_destructible_v<Type>);
  EXPECT_FALSE(std::is_trivially_destructible_v<Type>);

  EXPECT_TRUE(std::has_virtual_destructor_v<Type>);

  // Type relationships.
  EXPECT_TRUE((std::is_base_of_v<net::IClient, Type>));
}

TEST(ClientTest, InitializeInstance)
{
  net::ConnectionSettings connectionSettings;
  connectionSettings.id = "test-1";
  connectionSettings.host = "127.0.0.1";
  connectionSettings.port = 5555;
  EXPECT_EQ(connectionSettings.id.value(), "test-1");
  EXPECT_EQ(connectionSettings.host, "127.0.0.1");
  EXPECT_EQ(connectionSettings.port, 5555);

  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(std::make_unique<net::ZmqClient>(context, connectionSettings));
}

TEST(ClientTest, InitializeInstanceWithMakeConnectionSettings)
{
  auto connectionSettings = net::MakeConnectionSettings(5555);
  EXPECT_FALSE(connectionSettings.id.has_value());
  EXPECT_EQ(connectionSettings.host, "localhost");
  EXPECT_EQ(connectionSettings.port, 5555);

  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(std::make_unique<net::ZmqClient>(context, connectionSettings));
}
