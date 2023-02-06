#include "vlq.hpp"
#include <sstream>
#include <stdexcept>
#include <vector>

using namespace vlq;
std::vector<int> Processor::decode(std::string const str) const {
  std::vector<int> result;
  unsigned int shift = 0;
  unsigned int value = 0;
  for (char x : str) {
    // unsigned int index = charIndex.at(x);
    if (charIndex.find(x) != charIndex.end()) {
      unsigned int index = charIndex.at(x);
      const unsigned int hasContinuationBit = index & 32;
      index &= 31;
      value += (index << shift);
      if (hasContinuationBit) {
        shift += 5;
      } else {
        const unsigned int neg = value & 1;
        value >>= 1;
        if (neg) {
          result.push_back(value == 0 ? -0x80000000 : -value);
        } else {
          result.push_back(value);
        }
        value = 0;
        shift = 0;
      }
    } else {
      throw std::runtime_error("cannot find correct char index");
    }
  }

  return std::move(result);
}

std::string Processor::encode(const std::vector<int> values) const {
  std::stringstream result;
  for (int value : values) {
    result << this->encode(value);
  }
  return result.str();
}

std::string Processor::encode(int value) const {
  std::stringstream result;
  long long int lValue = 0;

  if (value < 0) {
    value = ((-value) << 1) | 1;
  } else {
    value = value << 1;
  }
  lValue |= value;
  lValue &= 0x00000000ffffffff;
  do {
    int clamped = lValue & 31;
    lValue = lValue >> 5;
    if (lValue > 0) {
      clamped |= 32;
    }
    result << indexChar.at(clamped);
  } while (lValue > 0);

  return result.str();
}
