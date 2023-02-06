#pragma once
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace vlq {

class Processor {
public:
  Processor() {
    unsigned int index = 0;
    for (char x : vlqstr) {
      charIndex[x] = index;
      indexChar[index] = x;
      index++;
    }
  };
  Processor(const Processor &src) = default; // copy construct
  Processor(Processor &&src) = default;      // move construct

  /**
   * @brief decode vlq string to int vector
   *
   * @param str vlq string
   * @return std::vector<int> int set
   * @throw std::runtime_error
   */
  std::vector<int> decode(std::string const str) const;

  /**
   * @brief encode int values to vlq string
   *
   * @param values int values
   * @return std::string vlq string
   */
  std::string encode(std::vector<int> const values) const;

private:
  const std::string vlqstr{
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="};
  std::unordered_map<char, unsigned int> charIndex;
  std::unordered_map<unsigned int, char> indexChar;
  std::string encode(int value) const;
};
} // namespace vlq