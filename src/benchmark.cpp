#include "mergesort.h"
#include <iostream>

#define LENGTH 100000000
// #define LENGTH 2147483648

int main() {
  int *data = new int[LENGTH];

  for (size_t i = 0; i < LENGTH; i++) {
    data[i] = LENGTH - i;
  }

  std::cout << "Commencing with sort" << std::endl;
  mergesort(data, LENGTH);

  delete[] data;

  return 0;
}
