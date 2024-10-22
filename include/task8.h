#ifndef TASK8_H
#define TASK8_H

#include <AES.h>
#include <Arduino.h>
#include <CTR.h>
#include <Crypto.h>
#include <EAX.h>
#include <GCM.h>
#include <XTS.h>

#include "LittleFS.h"
#include "testdata.h"
#include "util.h"

void performBenchmark();

#endif