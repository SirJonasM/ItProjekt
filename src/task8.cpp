#include "task8.h"

CTR<AES128> aes128_ctr;
CTR<AES192> aes192_ctr;
CTR<AES256> aes256_ctr;

EAX<AES128> aes128_aex;
EAX<AES192> aes192_aex;
EAX<AES256> aes256_aex;

GCM<AES128> aes128_gcm;    
GCM<AES192> aes192_gcm;
GCM<AES256> aes256_gcm;

void set_keys(){
    byte key[32] = {};
    fillArrayWithRandomData(key, sizeof(key));
    aes128_ctr.setKey(key, aes128_ctr.keySize() );
    aes192_ctr.setKey(key, aes192_ctr.keySize() );
    aes256_ctr.setKey(key, aes256_ctr.keySize() );
    aes128_aex.setKey(key, aes128_aex.keySize() );
    aes192_aex.setKey(key, aes192_aex.keySize() );
    aes256_aex.setKey(key, aes256_aex.keySize() );
    aes128_gcm.setKey(key, aes128_gcm.keySize() );
    aes192_gcm.setKey(key, aes192_gcm.keySize() );
    aes256_gcm.setKey(key, aes256_gcm.keySize() );
}

void performBenchmark() {
    Serial.println("---------- Task 8 Start ----------");
    const int iterations = 100000;
    byte ciphertext[16] = {};
    byte output[16] = {};
    byte plaintext[16] = {};
    // [[[encryption, decryption],[encryption, decryption],[encryption, decryption]], ...]
    //     AES128                   AES192                      AES256
    long times[3][3][2] = {}; 
    for (int i = 0; i < iterations; i++){
        fillArrayWithRandomData(plaintext, sizeof(plaintext));
        set_keys();
        // CTR
        long start = millis();
        aes128_ctr.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[0][0][0] += millis() - start;

        start = millis();
        aes128_ctr.decrypt(output, ciphertext, sizeof(plaintext));
        times[0][0][1]  += millis() - start;

        start = millis();
        aes192_ctr.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[0][1][0]  += millis() - start;
        
        start = millis();
        aes192_ctr.decrypt(output, ciphertext, sizeof(plaintext));
        times[0][1][1]  += millis() - start;

        start = millis();
        aes256_ctr.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[0][2][0]  += millis() - start;
        
        start = millis();
        aes256_ctr.decrypt(output, ciphertext, sizeof(plaintext));
        times[0][2][1]  += millis() - start;

        // AEX
        start = millis();
        aes128_aex.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[1][0][0]  += millis() - start;

        start = millis();
        aes128_aex.decrypt(output, ciphertext, sizeof(plaintext));
        times[1][0][1]  += millis() - start;

        start = millis();
        aes192_aex.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[1][1][0]  += millis() - start;
        
        start = millis();
        aes192_aex.decrypt(output, ciphertext, sizeof(plaintext));
        times[1][1][1]  += millis() - start;

        start = millis();
        aes256_aex.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[1][2][0]  += millis() - start;
        
        start = millis();
        aes256_aex.decrypt(output, ciphertext, sizeof(plaintext));
        times[1][2][1]  += millis() - start;

        // GCM
        start = millis();
        aes128_gcm.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[2][0][0] += millis() - start;

        start = millis();
        aes128_gcm.decrypt(output, ciphertext, sizeof(plaintext));
        times[2][0][1] += millis() - start;

        start = millis();
        aes192_gcm.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[2][1][0] += millis() - start;
        
        start = millis();
        aes192_gcm.decrypt(output, ciphertext, sizeof(plaintext));
        times[2][1][1] += millis() - start;

        start = millis();
        aes256_gcm.encrypt(ciphertext, plaintext, sizeof(plaintext));
        times[2][2][0] += millis() - start;
        
        start = millis();
        aes256_gcm.decrypt(output, ciphertext, sizeof(plaintext));
        times[2][2][1] += millis() - start;
        yield();
    }
    File file = LittleFS.open("/task8.csv", "w");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }

    // Write the header line
    file.println("Mode,AES128 Encrypt,AES128 Decrypt,AES192 Encrypt,AES192 Decrypt,AES256 Encrypt,AES256 Decrypt");

    // Write CTR results
    file.print("CTR,");
    for (int i = 0; i < 3; i++) {
        file.printf("%.6f,%.6f", (double)times[0][i][0] / (double)iterations, (double)times[0][i][1] / (double)iterations); // Encryption time
        if (i < 2) file.print(",");
    }
    file.println();

    // Write AEX results
    file.print("AEX,");
    for (int i = 0; i < 3; i++) {
        file.printf("%.6f,%.6f", (double)times[1][i][0] / (double)iterations, (double)times[1][i][1] / (double)iterations); // Encryption time
        if (i < 2) file.print(",");
    }
    file.println();

    // Write GCM results
    file.print("GCM,");
    for (int i = 0; i < 3; i++) {
        file.printf("%.6f,%.6f", (double)times[2][i][0] /(double)iterations, (double)times[2][i][1] / (double)iterations); // Encryption time
        if (i < 2) file.print(",");
    }

    file.close();
    Serial.println("---------- Task 8 End ----------");
}