#include "util.h"

void fillArrayWithRandomData(byte *buffer, size_t length) {
  for (size_t i = 0; i < length; ++i) {
    buffer[i] = random(0, 256); // Generate a random byte between 0 and 255
  }
}