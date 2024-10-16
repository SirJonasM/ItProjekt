#ifndef TASK6_H
#define TASK6_H

#include <Arduino.h>
#include <Crypto.h>
#include <AES.h>
#include <string.h>
#include <stdlib.h> 
#include "testdata.h"
#include "util.h"

void compareAESPerformanceTask6(BlockCipher *aes128, BlockCipher *aes192, BlockCipher *aes256, const int iterations);

#endif