#include <gtest/gtest.h>

#include <Randomizer.h>

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view/all.hpp>

using namespace net::utils;

namespace test {
constexpr size_t length{ 10 };
} // namespace test

TEST(RandomizerTest, ProduceDigitSequence)
{
  std::unique_ptr<ICharSequence> sequence{ std::make_unique<DigitSequence>() };
  const auto digits = sequence->produce();
  EXPECT_EQ(digits.size(), DigitSequence{}.produce().size());
  EXPECT_TRUE(ranges::all_of(digits, isdigit));
}

TEST(RandomizerTest, ProduceLettersSequence)
{
  std::unique_ptr<ICharSequence> sequence{ std::make_unique<LowerCaseLetterSequence>(
    std::make_unique<UpperCaseLetterSequence>()) };
  const auto letters = sequence->produce();
  EXPECT_EQ(letters.size(), LowerCaseLetterSequence{}.produce().size() * 2);
  EXPECT_TRUE(ranges::all_of(letters, isalpha));
}

TEST(RandomizerTest, ProduceSymbolSequence)
{
  std::unique_ptr<ICharSequence> sequence{ std::make_unique<SymbolSequence>() };
  const auto symbols = sequence->produce();
  EXPECT_EQ(symbols.size(), SymbolSequence{}.produce().size());
  EXPECT_TRUE(ranges::all_of(symbols, ispunct));
}

TEST(RandomizerTest, ProduceAlnumSequence)
{
  std::unique_ptr<ICharSequence> sequence{ std::make_unique<AlnumSequence>() };
  const auto alnums = sequence->produce();
  EXPECT_EQ(alnums.size(), AlnumSequence{}.produce().size());
  EXPECT_TRUE(ranges::all_of(alnums, [](const char ch) { return isdigit(ch) || isalnum(ch); }));
}

TEST(RandomizerTest, GenerateStringWithDigits)
{
  const auto str = Randomizer{ std::make_unique<DigitSequence>() }.generate(test::length);
  EXPECT_EQ(str.size(), test::length);
  EXPECT_TRUE(ranges::all_of(str, isdigit));
}

TEST(RandomizerTest, GenerateStringWithLettersAndDigits)
{
  const auto str = Randomizer{}.generate(test::length);
  EXPECT_EQ(str.size(), test::length);
  EXPECT_TRUE(ranges::all_of(str, [](const char ch) { return isdigit(ch) || isalnum(ch); }));
}

TEST(RandomizerTest, GenerateStringIfCharSequenceIsNull)
{
  const auto str = Randomizer{ nullptr }.generate(test::length);
  EXPECT_TRUE(str.empty());
}

TEST(RandomizerTest, GenerateZeroLengthString)
{
  const auto str = Randomizer{}.generate(test::length);
  EXPECT_EQ(str.size(), test::length);
}

TEST(RandomizerTest, GenerateTwoDifferentStrings)
{
  const auto str1 = Randomizer{}.generate(test::length);
  const auto str2 = Randomizer{}.generate(test::length);
  EXPECT_NE(str1, str2);
}
