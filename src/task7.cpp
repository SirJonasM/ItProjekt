#include "task7.h"

void compareAESPerformanceTask7(BlockCipher *aes128, BlockCipher *aes192, BlockCipher *aes256, const int iterations) {
    unsigned long start;
    unsigned long encryption128 = 0;
    unsigned long encryption192 = 0;
    unsigned long encryption256 = 0;
    unsigned long decryption128 = 0;
    unsigned long decryption192 = 0;
    unsigned long decryption256 = 0;
    byte randomPlaintext[16] = {};
    byte randomKey[32] = {};
    byte decryption[16];
    byte encryption[16];

    File file = LittleFS.open("/data.csv", "w");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.println("------------- TASK 7 -------------");
    for (int i = 0; i < iterations; ++i) {
        fillArrayWithRandomData(randomPlaintext, sizeof(randomPlaintext)); 
        fillArrayWithRandomData(randomKey, sizeof(randomKey));
        aes128->setKey(randomKey, aes128->keySize());
        aes192->setKey(randomKey, aes192->keySize());
        aes256->setKey(randomKey, aes256->keySize());
        
        start = micros();
        aes128->encryptBlock(encryption, randomPlaintext);
        encryption128 += micros() - start;
        
        start = micros();
        aes128->decryptBlock(decryption, encryption);
        decryption128 += micros() - start;
    
        start = micros();
        aes192->encryptBlock(encryption, randomPlaintext);
        encryption192 += micros() - start;
        
        start = micros();
        aes192->decryptBlock(decryption, encryption);
        decryption192 += micros() - start;

        start = micros();
        aes256->encryptBlock(encryption, randomPlaintext);
        encryption256 += micros() - start;
        
        start = micros();
        aes256->decryptBlock(decryption, encryption);
        decryption256 += micros() - start;
    }
    
    // Calculate average time
    float avg128encryption = (float)encryption128 / iterations;
    float avg128decryption = (float)decryption128 / iterations;

    float avg192encryption = (float)encryption192 / iterations;
    float avg192decryption = (float)decryption192 / iterations;

    float avg256encryption = (float)encryption256 / iterations;
    float avg256decryption = (float)decryption256 / iterations;

    // Print average time
    Serial.printf("AES-128 Average Time: %.6f ms per Decryption and Encryption\n", avg128encryption / 1000.0);
    Serial.printf("AES-128 Average Time: %.6f ms per Decryption and Encryption\n", avg128decryption / 1000.0);

    Serial.printf("AES-192 Average Time: %.6f ms per Decryption and Encryption\n", avg192encryption / 1000.0);
    Serial.printf("AES-192 Average Time: %.6f ms per Decryption and Encryption\n", avg192decryption / 1000.0);

    Serial.printf("AES-256 Average Time: %.6f ms per Decryption and Encryption\n", avg256encryption / 1000.0);
    Serial.printf("AES-256 Average Time: %.6f ms per Decryption and Encryption\n", avg256decryption / 1000.0);

    // Format the AES-128 result and write it to the file
    file.printf("AES-128, %.6f, %.6f\n", avg128encryption / 1000.0, avg128decryption / 1000.0);

    // Format the AES-192 result and write it to the file
    file.printf("AES-192, %.6f, %.6f\n", avg192encryption / 1000.0, avg192decryption / 1000.0);

    // Format the AES-256 result and write it to the file
    file.printf("AES-256, %.6f, %.6f\n", avg256encryption / 1000.0, avg256decryption / 1000.0);

    file.close();

    Serial.println("------------- End -------------");
}