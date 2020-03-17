#pragma once

#include <string>

namespace utils {

class Randomizer
{
public:
  enum Literals
  {
    UpperCaseLetters = 0b0001,
    LowerCaseLetters = 0b0010,
    Numbers = 0b0100,

    Letters = UpperCaseLetters | LowerCaseLetters,
    Alnum = Letters | Numbers
  };

  static std::string generateString(const size_t& length, const int charset = Literals::Alnum);
};

} // namespace utils
