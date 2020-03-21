#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <Randomizer.h>

#include <algorithm>

TEST(RandomizerTests, GenerateUpperCaseString)
{
  constexpr size_t length = 10;
  constexpr int literals = utils::Randomizer::UpperCaseLetters;
  const auto str = utils::Randomizer::generateString(length, literals);
  EXPECT_EQ(str.size(), length);
  EXPECT_TRUE(std::all_of(str.begin(), str.end(), ::isupper));
}

TEST(RandomizerTests, GenerateLowerCaseString)
{
  constexpr size_t length = 10;
  constexpr int literals = utils::Randomizer::LowerCaseLetters;
  const auto str = utils::Randomizer::generateString(length, literals);
  EXPECT_EQ(str.size(), 10);
  EXPECT_TRUE(std::all_of(str.begin(), str.end(), ::islower));
}

TEST(RandomizerTests, GenerateDigitsString)
{
  constexpr size_t length = 10;
  constexpr int literals = utils::Randomizer::Digits;
  const auto str = utils::Randomizer::generateString(length, literals);
  EXPECT_EQ(str.size(), length);
  EXPECT_TRUE(std::all_of(str.begin(), str.end(), ::isdigit));
}

TEST(RandomizerTests, GenerateZeroLengthString)
{
  constexpr size_t length = 0;
  const auto str = utils::Randomizer::generateString(length);
  EXPECT_EQ(str.size(), length);
}

TEST(RandomizerTests, GenerateDifferentStrings)
{
  constexpr size_t length = 10;
  const auto str1 = utils::Randomizer::generateString(length);
  const auto str2 = utils::Randomizer::generateString(length);
  EXPECT_NE(str1, str2);
}
