#include "../src/vlq.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

const std::unordered_map<std::string, std::vector<int>>
    testcases({{"AAAA", {0, 0, 0, 0}},
               {"AAgBC", {0, 0, 16, 1}},
               {"D", {-1}},
               {"B", {-2147483648}},
               {"+/////D", {2147483647}}});

TEST(vlqTest, testDecode) {
  vlq::Processor processor;
  for (auto &kv : testcases) {
    auto result = processor.decode(kv.first);
    ASSERT_TRUE(std::equal(result.cbegin(), result.cend(), kv.second.cbegin(),
                           kv.second.cend()));
  }
}

TEST(vlqTest, testEncode) {
  vlq::Processor processor;
  for (auto &kv : testcases) {
    auto result = processor.encode(kv.second);
    ASSERT_EQ(result, kv.first);
  }
}

TEST(vlqTest, testException) {
  vlq::Processor processor;
  ASSERT_ANY_THROW(processor.decode("&&"));
}
