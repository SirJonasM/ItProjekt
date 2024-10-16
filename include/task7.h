#ifndef TASK7_H
#define TASK7_H

#include <Arduino.h>
#include <Crypto.h>
#include <AES.h>
#include <string.h>
#include <stdlib.h> 
#include "testdata.h"
#include "util.h"
#include "LittleFS.h"


void compareAESPerformanceTask7(BlockCipher *aes128, BlockCipher *aes192, BlockCipher *aes256, const int iterations);

#endif