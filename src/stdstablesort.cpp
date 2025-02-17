#include "mergesort.h"
#include <algorithm>
#include <vector>

void mergesort(int *data, size_t n) {
  std::vector<int> data_vec(data, data + n);

  std::stable_sort(data_vec.begin(), data_vec.end());
}
