#include "mergesort.h"

struct PointerInfo {
  int *data;
  int *slot1;
  int *slot2;
  int **available;
};

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

static void mergesort_rec(int *data, int *buffer, size_t len, PointerInfo &pi) {
  size_t sizer = 1;
  while (sizer < len) {
    int *group_iterator = data;
    int *group_iterator2 = group_iterator + sizer;
    int *available = *pi.available;

    // TODO: First group should merge the available

    while (group_iterator2 - data < len) { // There is still a pair
      if ((group_iterator2 + sizer) - data < len) {
        // Is the last group not the full size
        merge(group_iterator, group_iterator2, available, sizer,
              len - (size_t)group_iterator2 - (size_t)data);
      } else {
        merge(group_iterator, group_iterator2, available, sizer, sizer);
      }
      group_iterator += 2 * sizer;
      group_iterator2 += sizer;
      available = group_iterator;
    }

    // Availability rotator
    if (*pi.available == pi.slot1) {
      pi.available = &pi.slot2;
    } else if (*pi.available == pi.slot2) {
      pi.available = &pi.data;
    } else if (*pi.available == pi.data) {
      pi.av
    }

    sizer <<= 1; // Double grouping size
  }
}

void mergesort(int *data, size_t n) {
  // Base Case / Edge Case
  if (n == 1) {
    return;
  }

  // Initialization for the mergesort
  int *buffer = new int[2 * n];
  PointerInfo pi = {data, buffer, buffer + n};
  pi.available = &pi.slot1;

  mergesort_rec(data, buffer, n, pi);

  // Replace the data by the sorted buffer data
  for (size_t i = 0; i < n; i++) {
    data[i] = buffer[i];
  }

  delete[] buffer;
}
