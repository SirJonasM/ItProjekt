#ifndef TESTDATA_H
#define TESTDATA_H

#include <Arduino.h>
#include <Crypto.h>

// Define the TestVector struct
struct TestVector
{
  const char *name;
  byte key[32];
  byte plaintext[16];
  byte ciphertext[16];
};

// Extern declarations for the test vectors
extern TestVector const testVectorAES128;
extern TestVector const testVectorAES192;
extern TestVector const testVectorAES256;

#endif // TESTVECTORS_H
