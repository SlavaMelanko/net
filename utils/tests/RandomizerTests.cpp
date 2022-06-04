#include <gtest/gtest.h>

#include <Randomizer.h>

#include <range/v3/algorithm/all_of.hpp>
#include <range/v3/view/all.hpp>

using namespace net::utils;

namespace test {
constexpr size_t length{ 10 };
} // namespace test

TEST(RandomizerTest, ProduceEmptyCharSequnce)
{
  std::unique_ptr<ICharSequence> sequnce = std::make_unique<CharSequenceDecorator>();
  EXPECT_TRUE(sequnce->produce().empty());
}

TEST(RandomizerTest, ProduceDigitSequnce)
{
  std::unique_ptr<ICharSequence> sequnce =
    std::make_unique<DigitSequence>(std::make_unique<CharSequenceDecorator>());
  const auto digits = sequnce->produce();
  EXPECT_EQ(digits.size(), DigitSequence{}.produce().size());
  EXPECT_TRUE(ranges::all_of(digits, isdigit));
}

TEST(RandomizerTest, ProduceLettersSequnce)
{
  std::unique_ptr<ICharSequence> sequnce = std::make_unique<LowerCaseLetterSequence>(
    std::make_unique<UpperCaseLetterSequence>(std::make_unique<CharSequenceDecorator>()));
  const auto letters = sequnce->produce();
  EXPECT_EQ(letters.size(), LowerCaseLetterSequence{}.produce().size() * 2);
  EXPECT_TRUE(ranges::all_of(letters, isalpha));
}

TEST(RandomizerTest, ProduceSymbolSequnce)
{
  std::unique_ptr<ICharSequence> sequnce =
    std::make_unique<SymbolSequence>(std::make_unique<CharSequenceDecorator>());
  const auto symbols = sequnce->produce();
  EXPECT_EQ(symbols.size(), SymbolSequence{}.produce().size());
  EXPECT_TRUE(ranges::all_of(symbols, ispunct));
}

TEST(RandomizerTest, ProduceAlnumSequnce)
{
  std::unique_ptr<ICharSequence> sequnce = std::make_unique<AlnumSequence>();
  const auto alnums = sequnce->produce();
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
