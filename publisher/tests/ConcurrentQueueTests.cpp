#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <ConcurrentQueue.h>

TEST(ConcurrentQueueTest, ProduceAndConsume)
{
  constexpr int numberIterations = 100;
  net::ConcurrentQueue<int> queue;

  std::thread producer([&]() {
    for (int i = 0; i != numberIterations; ++i) {
      std::this_thread::sleep_for(std::chrono::milliseconds(i % 10));
      EXPECT_TRUE(queue.enqueue(i));
    }
  });

  std::thread consumer([&]() {
    for (int i = 0; i != numberIterations; ++i) {
      int item;
      EXPECT_NO_THROW(queue.wait_dequeue(item));
      EXPECT_EQ(item, i);
    }
  });

  producer.join();
  consumer.join();

  EXPECT_TRUE(queue.empty());
}
