#include "mergesort.h"

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

static int *mergesort_rec(int *data, size_t len) {
  if (len <= 1) {
    return data;
  }

  size_t mid = len / 2;

  int *left_original = data;
  int *right_original = data + mid;

  int *left = mergesort_rec(left_original, mid);
  int *right = mergesort_rec(right_original, len - mid);

  int *sorted = new int[len];

  merge(left, right, sorted, mid, len - mid);

  if (mid > 1)
    delete[] left;
  if (len - mid > 1)
    delete[] right;

  return sorted;
}

void mergesort(int *data, size_t len) {
  // Edge case where the one element is returned as an address
  if (len == 1) {
    return;
  }

  int *sorted = mergesort_rec(data, len);

  for (size_t i = 0; i < len; i++) {
    data[i] = sorted[i];
  }

  delete[] sorted;
  return;
}
