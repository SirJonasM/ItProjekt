#include "task7.h"

void compareAESPerformanceTask7(BlockCipher *aes128, BlockCipher *aes192, BlockCipher *aes256, const int iterations) {
    unsigned long start;
    byte randomPlaintext[16] = {};
    byte randomKey[32] = {};
    byte decryption[16];
    byte encryption[16];

    File file = LittleFS.open("/task6.csv", "w");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }
    file.println("AES-128-Encryption,AES-128-Decryption,AES-192-Encryption,AES-192-Decryption,AES-256-Encryption,AES-256-Decryption,");
    for (int i = 0; i < iterations; ++i) {
        fillArrayWithRandomData(randomPlaintext, sizeof(randomPlaintext));
        fillArrayWithRandomData(randomKey, sizeof(randomKey));
        aes128->setKey(randomKey, aes128->keySize());
        aes192->setKey(randomKey, aes192->keySize());
        aes256->setKey(randomKey, aes256->keySize());
        start = micros();
        aes128->encryptBlock(encryption, randomPlaintext);
        start = micros() - start;
        file.printf("%lu,", start);

        start = micros();
        aes128->decryptBlock(decryption, encryption);
        start = micros() - start;
        file.printf("%lu,", start);

        start = micros();
        aes192->encryptBlock(encryption, randomPlaintext);
        start = micros() - start;
        file.printf("%lu,", start);

        start = micros();
        aes192->decryptBlock(decryption, encryption);
        start = micros() - start;
        file.printf("%lu,", start);

        start = micros();
        aes256->encryptBlock(encryption, randomPlaintext);
        start = micros() - start;
        file.printf("%lu,", start);

        start = micros();
        aes256->decryptBlock(decryption, encryption);
        start = micros() - start;
        file.printf("%lu,", start);
    }
    file.close();
}