#include "utils.h"

size_t binarydigits(size_t val) {
  size_t res = 0;
  while (val != 0) {
    res++;
    val >>= 1;
  }
  return res;
}
