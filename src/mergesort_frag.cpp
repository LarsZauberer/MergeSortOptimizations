#include "mergesort.h"
#include "utils.h"
// #include <iostream>
#include <stdlib.h>

static void merge(int *left, int *right, int *sorted, size_t llen,
                  size_t rlen) {
  size_t i = 0;
  size_t j = 0;
  size_t k = 0;

  while (i < llen && j < rlen) {
    if (left[i] < right[j]) {
      sorted[k++] = left[i++];
    } else {
      sorted[k++] = right[j++];
    }
  }

  while (i < llen) {
    sorted[k++] = left[i++];
  }

  while (j < rlen) {
    sorted[k++] = right[j++];
  }
}

static void mergesort_rec(int *data, int *buffer, size_t len) {
  // Base Case
  if (len <= 1) {
    *buffer = *data;
    return;
  }

  size_t mid = len / 2;

  int *left_original = data;
  int *right_original = data + mid;

  // Buffer placement:
  // my_buffer | left | right | ...
  int *my_buffer = buffer;
  int *left_buffer = buffer + len;
  int *right_buffer = left_buffer + mid;

  mergesort_rec(left_original, buffer + len, mid);
  mergesort_rec(right_original, left_buffer + mid, len - mid);

  merge(left_buffer, right_buffer, my_buffer, mid, len - mid);
}

void mergesort(int *data, size_t n) {
  // Initialization for the mergesort

  // We have (n-1) * 2 + 1 recursions
  // Each recursion needs a unique buffer where the sorted data is. The sorted
  // data is at max n long. The left and right is just one of those unique
  // buffers from a fork and they can be saved as pointer on the stack. If we
  // optimize further, every split halfes the size needed, hence we have n + 2 *
  // n/2 + 4 * n/4 + ... We can simplify this expression to n + n + ... = n *
  // floor(log_2(n)) since we have floor(log_2(n)) levels.

  int *buffer =
      new int[(binarydigits(n) + 1) * n]; // FIX: Can be optimized even more
  mergesort_rec(data, buffer, n);

  // Replace the data by the sorted buffer data
  for (size_t i = 0; i < n; i++) {
    data[i] = buffer[i];
  }

  delete[] buffer;
}
