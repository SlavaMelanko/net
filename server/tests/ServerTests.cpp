#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <RequestHandlerFactory.h>
#include <ZmqServer.h>

TEST(ServerTest, CheckTypeTraits)
{
  using Type = net::ZmqServer;

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
  EXPECT_TRUE((std::is_base_of_v<net::IServer, Type>));
}

TEST(ServerTest, InitializeInstance)
{
  auto requestHandlerFactory = std::make_unique<net::RequestHandlerFactory>();
  EXPECT_TRUE(requestHandlerFactory);
  zmq::context_t context{ 1 };
  EXPECT_TRUE(context);
  EXPECT_NO_THROW(
    std::make_unique<net::ZmqServer>(std::move(requestHandlerFactory), context, "127.0.0.1", 5555));
}
