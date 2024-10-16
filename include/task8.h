#ifndef TASK8_H
#define TASK8_H

#include <Arduino.h>
#include <Crypto.h>
#include <AES.h>
#include <CTR.h>
#include <EAX.h>
#include <GCM.h>
#include <XTS.h>
#include "testdata.h"
#include "util.h"
#include "LittleFS.h"

void performBenchmark();

#endif