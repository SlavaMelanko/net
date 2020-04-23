#include "Randomizer.h"

#include <algorithm>
#include <random>

namespace net::utils {

namespace {

std::string GetCharset(const int literals)
{
  std::string charset;

  if (literals & Randomizer::Digits) {
    charset += "0123456789";
  }
  if (literals & Randomizer::UpperCaseLetters) {
    charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  }
  if (literals & Randomizer::LowerCaseLetters) {
    charset += "abcdefghijklmnopqrstuvwxyz";
  }

  return charset;
}

} // namespace

std::string Randomizer::generateString(const size_t& length, const int literals)
{
  if (length == 0)
    return {};

  std::random_device rd{};
  std::mt19937 rng{ rd() };
  const auto charset = GetCharset(literals);
  std::uniform_int_distribution<> distr{ 0, static_cast<int>(charset.size()) - 1 };

  std::string str(length, 0);
  std::generate_n(
    str.begin(), length, [&]() { return charset.at(static_cast<size_t>(distr(rng))); });

  return str;
}

} // namespace net::utils
