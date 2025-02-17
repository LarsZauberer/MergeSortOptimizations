#include "mergesort.h"
#include "utils.h"
#include <catch2/catch_message.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <climits>
#include <cmath>
#include <iostream>
#include <string>

template <typename T> void print_array(T *arr, size_t len) {
  using namespace std;
  cout << "[";
  for (size_t i = 0; i < len - 1; i++) {
    cout << arr[i] << ", ";
  }
  cout << arr[len - 1] << "]" << endl;
}

template <typename T> std::string array_to_string(T *arr, size_t len) {
  using namespace std;

  string res = "[";
  for (size_t i = 0; i < len - 1; i++) {
    res.append(std::to_string(arr[i]) + ", ");
  }
  res.append(std::to_string(arr[len - 1]) + "]");

  return res;
}

TEST_CASE("Ten reverse") {
  const size_t length = GENERATE(1, 2, 3, 4, 5, 10, 11);
  int *data = (int *)malloc(sizeof(int) * length);
  REQUIRE(data != NULL);

  // std::cout << "Data Before: " << data << std::endl;

  for (size_t i = 0; i < length; i++) {
    data[i] = length - i;
  }

  mergesort(data, length);

  // print_array(data, length);
  CAPTURE(array_to_string(data, length));

  CAPTURE(length);
  for (size_t i = 0; i < length; i++) {
    CHECK(data[i] == (int)i + 1);
  }

  // std::cout << "Data After: " << data << std::endl;
  free(data);
}

TEST_CASE("Test CeilLog2") {
  const size_t inp = GENERATE(1, 2, 3, 4, 5, 6, 7, 8, 9);
  const size_t out = binarydigits(inp);
  const size_t should = floor(log2(inp) + 1);

  CAPTURE(inp);

  CHECK(out == should);
}
