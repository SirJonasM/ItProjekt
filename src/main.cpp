#include <Arduino.h>
#include <Crypto.h>
#include <AES.h>
#include <string.h>
#include <stdlib.h> // For generating random data

AES128 aes128;
AES192 aes192;
AES256 aes256;

struct TestVector
{
  const char *name;
  byte key[32];
  byte plaintext[16];
  byte ciphertext[16];
};
byte buffer[16]; // Buffer for encryption/decryption

// Define the ECB test vectors from the FIPS specification.
static TestVector const testVectorAES128 = {
    .name = "AES-128-ECB",
    .key = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F},
    .plaintext = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                  0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
    .ciphertext = {0x69, 0xC4, 0xE0, 0xD8, 0x6A, 0x7B, 0x04, 0x30,
                   0xD8, 0xCD, 0xB7, 0x80, 0x70, 0xB4, 0xC5, 0x5A}};
static TestVector const testVectorAES192 = {
    .name = "AES-192-ECB",
    .key = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17},
    .plaintext = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                  0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
    .ciphertext = {0xDD, 0xA9, 0x7C, 0xA4, 0x86, 0x4C, 0xDF, 0xE0,
                   0x6E, 0xAF, 0x70, 0xA0, 0xEC, 0x0D, 0x71, 0x91}};
static TestVector const testVectorAES256 = {
    .name = "AES-256-ECB",
    .key = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
            0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
            0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F},
    .plaintext = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                  0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF},
    .ciphertext = {0x8E, 0xA2, 0xB7, 0xCA, 0x51, 0x67, 0x45, 0xBF,
                   0xEA, 0xFC, 0x49, 0x90, 0x4B, 0x49, 0x60, 0x89}};

void testCipher(BlockCipher *cipher, const struct TestVector *test)
{
  crypto_feed_watchdog();
  Serial.print(test->name);
  Serial.print(" Encryption ... ");
  cipher->setKey(test->key, cipher->keySize());
  cipher->encryptBlock(buffer, test->plaintext);
  if (memcmp(buffer, test->ciphertext, 16) == 0)
    Serial.println("Passed");
  else
    Serial.println("Failed");

  Serial.print(test->name);
  Serial.print(" Decryption ... ");
  cipher->decryptBlock(buffer, test->ciphertext);
  if (memcmp(buffer, test->plaintext, 16) == 0)
    Serial.println("Passed");
  else
    Serial.println("Failed");
}

void perfCipher(BlockCipher *cipher, const struct TestVector *test)
{
  unsigned long start;
  unsigned long elapsed;
  int count;

  crypto_feed_watchdog();

  Serial.print(test->name);
  Serial.print(" Set Key ... ");
  start = micros();
  for (count = 0; count < 10000; ++count)
  {
    cipher->setKey(test->key, cipher->keySize());
  }
  elapsed = micros() - start;
  Serial.print(elapsed / 10000.0);
  Serial.print("us per operation, ");
  Serial.print((10000.0 * 1000000.0) / elapsed);
  Serial.println(" per second");

  Serial.print(test->name);
  Serial.print(" Encrypt ... ");
  start = micros();
  for (count = 0; count < 5000; ++count)
  {
    cipher->encryptBlock(buffer, buffer);
  }
  elapsed = micros() - start;
  Serial.print(elapsed / (5000.0 * 16.0));
  Serial.print("us per byte, ");
  Serial.print((16.0 * 5000.0 * 1000000.0) / elapsed);
  Serial.println(" bytes per second");

  Serial.print(test->name);
  Serial.print(" Decrypt ... ");
  start = micros();
  for (count = 0; count < 5000; ++count)
  {
    cipher->decryptBlock(buffer, buffer);
  }
  elapsed = micros() - start;
  Serial.print(elapsed / (5000.0 * 16.0));
  Serial.print("us per byte, ");
  Serial.print((16.0 * 5000.0 * 1000000.0) / elapsed);
  Serial.println(" bytes per second");

  Serial.println();
}

void setup()
{
  Serial.begin(9600);

  Serial.println();

  Serial.println("State Sizes:");
  Serial.print("AES128 ... ");
  Serial.println(sizeof(AES128));
  Serial.print("AES192 ... ");
  Serial.println(sizeof(AES192));
  Serial.print("AES256 ... ");
  Serial.println(sizeof(AES256));
  Serial.println();

  Serial.println("Test Vectors:");
  testCipher(&aes128, &testVectorAES128);
  testCipher(&aes192, &testVectorAES192);
  testCipher(&aes256, &testVectorAES256);

  Serial.println();

  Serial.println("Performance Tests:");
  perfCipher(&aes128, &testVectorAES128);
  perfCipher(&aes192, &testVectorAES192);
  perfCipher(&aes256, &testVectorAES256);
}

void generateRandomPlaintext(byte *plaintext, size_t length)
{
  for (size_t i = 0; i < length; ++i)
  {
    plaintext[i] = random(0, 256); // Generate a random byte between 0 and 255
  }
}
void compareAESPerformance(BlockCipher *aes128, BlockCipher *aes192, BlockCipher *aes256)
{
  unsigned long start, elapsed;
  int iterations = 100; // Number of times to run the encryption/decryption for benchmarking
  byte randomPlaintext[iterations][16] = {};
  byte output[16];

  // Generate random plaintext for each iteration
  for (int i = 0; i < iterations; ++i)
  {
    generateRandomPlaintext(randomPlaintext[i], sizeof(randomPlaintext[i])); // Pass array directly
  }
  Serial.println("Generated random Plaintext.");

  // Performance test for AES-128
  Serial.println("Testing AES-128");
  aes128->setKey(testVectorAES128.key, aes128->keySize());

  start = micros();
  for (int i = 0; i < iterations; ++i)
  {
    aes128->encryptBlock(output, randomPlaintext[i]);
  }
  elapsed = micros() - start;
  Serial.print("AES-128 Encryption: ");
  Serial.print(elapsed / (iterations * 16.0));
  Serial.println(" us per byte");

  // Performance test for AES-192
  Serial.println("Testing AES-192");
  aes192->setKey(testVectorAES192.key, aes192->keySize());

  start = micros();
  for (int i = 0; i < iterations; ++i)
  {
    aes192->encryptBlock(output, randomPlaintext[i]);
  }
  elapsed = micros() - start;
  Serial.print("AES-192 Encryption: ");
  Serial.print(elapsed / (iterations * 16.0));
  Serial.println(" us per byte");

  // Performance test for AES-256
  Serial.println("Testing AES-256");
  aes256->setKey(testVectorAES256.key, aes256->keySize());

  start = micros();
  for (int i = 0; i < iterations; ++i)
  {
    aes256->encryptBlock(output, randomPlaintext[i]);
  }
  elapsed = micros() - start;
  Serial.print("AES-256 Encryption: ");
  Serial.print(elapsed / (iterations * 16.0));
  Serial.println(" us per byte");
}

void loop()
{
  delay(1000); // Wait 10 seconds between tests
  Serial.println("TEST");
  compareAESPerformance(&aes128, &aes192, &aes256);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(1000);                     // wait for a second
  digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
  delay(1000);
}