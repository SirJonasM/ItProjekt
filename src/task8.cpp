#include "task8.h"

CTR<AES128> aes128_ctr;
CTR<AES192> aes192_ctr;
CTR<AES256> aes256_ctr;

EAX<AES128> aes128_eax;
EAX<AES192> aes192_eax;
EAX<AES256> aes256_eax;

GCM<AES128> aes128_gcm;
GCM<AES192> aes192_gcm;
GCM<AES256> aes256_gcm;

XTS<AES128> aes128_xts;
XTS<AES192> aes192_xts;
XTS<AES256> aes256_xts;
const size_t BUFFER_SIZE = 32768;
size_t size = 16;
byte PLAINTEXT_BUFFER[BUFFER_SIZE] = {};
const byte key[32] = {0x01, 0x02, 0x03, 0x4, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x016, 0x017, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};
const byte iV[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};
const byte tweak[32] = {0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01};

void setup_ciphers() {
    aes128_ctr.setKey(key, aes128_ctr.keySize());
    aes128_ctr.setKey(key, aes128_ctr.keySize());
    aes192_ctr.setKey(key, aes192_ctr.keySize());
    aes256_ctr.setKey(key, aes256_ctr.keySize());
    aes128_eax.setKey(key, aes128_eax.keySize());
    aes192_eax.setKey(key, aes192_eax.keySize());
    aes256_eax.setKey(key, aes256_eax.keySize());
    aes128_gcm.setKey(key, aes128_gcm.keySize());
    aes192_gcm.setKey(key, aes192_gcm.keySize());
    aes256_gcm.setKey(key, aes256_gcm.keySize());
    aes128_xts.setKey(key, aes128_xts.keySize());
    aes128_xts.setTweak(tweak, aes128_xts.tweakSize());
    aes128_xts.setSectorSize(size);
    aes192_xts.setKey(key, aes128_xts.keySize());
    aes192_xts.setTweak(tweak, aes128_xts.tweakSize());
    aes192_xts.setSectorSize(size);
    aes256_xts.setKey(key, aes128_xts.keySize());
    aes256_xts.setTweak(tweak, aes128_xts.tweakSize());
    aes256_xts.setSectorSize(size);
}

void setup_iVs() {
    aes128_ctr.setIV(iV, aes128_ctr.ivSize());
    aes128_ctr.setIV(iV, aes128_ctr.ivSize());
    aes192_ctr.setIV(iV, aes192_ctr.ivSize());
    aes256_ctr.setIV(iV, aes256_ctr.ivSize());
    aes128_eax.setIV(iV, aes128_eax.ivSize());
    aes192_eax.setIV(iV, aes192_eax.ivSize());
    aes256_eax.setIV(iV, aes256_eax.ivSize());
    aes128_gcm.setIV(iV, aes128_gcm.ivSize());
    aes192_gcm.setIV(iV, aes192_gcm.ivSize());
    aes256_gcm.setIV(iV, aes256_gcm.ivSize());
}
struct Times {
    unsigned long Ctr128Decrypt;
    unsigned long Ctr128Encrypt;
    unsigned long Ctr192Decrypt;
    unsigned long Ctr192Encrypt;
    unsigned long Ctr256Decrypt;
    unsigned long Ctr256Encrypt;

    unsigned long Eax128Decrypt;
    unsigned long Eax128Encrypt;
    unsigned long Eax192Decrypt;
    unsigned long Eax192Encrypt;
    unsigned long Eax256Decrypt;
    unsigned long Eax256Encrypt;

    unsigned long Gcm128Decrypt;
    unsigned long Gcm128Encrypt;
    unsigned long Gcm192Decrypt;
    unsigned long Gcm192Encrypt;
    unsigned long Gcm256Decrypt;
    unsigned long Gcm256Encrypt;

    unsigned long Xts128Decrypt;
    unsigned long Xts128Encrypt;
    unsigned long Xts192Decrypt;
    unsigned long Xts192Encrypt;
    unsigned long Xts256Decrypt;
    unsigned long Xts256Encrypt;

    size_t byte_length;
};

void bench(Times *times, size_t size) {
    setup_ciphers();
    setup_iVs();
    // CTR
    long start = micros();
    aes128_ctr.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Ctr128Encrypt = micros() - start;
    yield();

    start = micros();
    aes128_ctr.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Ctr128Decrypt = micros() - start;
    yield();

    start = micros();
    aes192_ctr.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Ctr192Encrypt = micros() - start;
    yield();

    start = micros();
    aes192_ctr.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Ctr192Decrypt = micros() - start;
    yield();

    start = micros();
    aes256_ctr.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Ctr256Encrypt = micros() - start;
    yield();

    start = micros();
    aes256_ctr.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Ctr256Decrypt = micros() - start;
    yield();

    // Eax
    start = micros();
    aes128_eax.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Eax128Encrypt = micros() - start;
    yield();

    start = micros();
    aes128_eax.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Eax128Decrypt = micros() - start;
    yield();

    start = micros();
    aes192_eax.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Eax192Encrypt = micros() - start;
    yield();

    start = micros();
    aes192_eax.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Eax192Decrypt = micros() - start;
    yield();

    start = micros();
    aes256_eax.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Eax256Encrypt = micros() - start;
    yield();

    start = micros();
    aes256_eax.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Eax256Decrypt = micros() - start;
    yield();

    // GCM
    start = micros();
    aes128_gcm.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Gcm128Encrypt = micros() - start;
    yield();

    start = micros();
    aes128_gcm.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Gcm128Decrypt = micros() - start;
    yield();

    start = micros();
    aes192_gcm.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Gcm192Encrypt = micros() - start;
    yield();

    start = micros();
    aes192_gcm.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Gcm192Decrypt = micros() - start;
    yield();

    start = micros();
    aes256_gcm.encrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Gcm256Encrypt = micros() - start;
    yield();

    start = micros();
    aes256_gcm.decrypt(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER, size);
    times->Gcm256Decrypt = micros() - start;
    yield();

    // XTS
    start = micros();
    aes128_xts.encryptSector(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER);
    times->Xts128Encrypt = micros() - start;
    yield();

    start = micros();
    aes128_xts.decryptSector(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER);
    times->Xts128Decrypt = micros() - start;
    yield();

    start = micros();
    aes192_xts.encryptSector(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER);
    times->Xts192Encrypt = micros() - start;
    yield();

    start = micros();
    aes192_xts.decryptSector(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER);
    times->Xts192Decrypt = micros() - start;
    yield();

    start = micros();
    aes256_xts.encryptSector(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER);
    times->Xts256Encrypt = micros() - start;
    yield();

    start = micros();
    aes256_xts.decryptSector(PLAINTEXT_BUFFER, PLAINTEXT_BUFFER);
    times->Xts256Decrypt = micros() - start;

    yield();
}
void printProgressBar(int progress, int total) {
    int barWidth = 50;  // Width of the progress bar

    Serial.print("\r[");
    int pos = barWidth * progress / total;  // Calculate filled portion
    for (int i = 0; i < barWidth; i++) {
        if (i < pos)
            Serial.print("=");
        else
            Serial.print(" ");
    }
    Serial.print("] ");
    Serial.print((progress * 100) / total);  // Print percentage
    Serial.print(" %");
}
void performBenchmark() {
    File file = LittleFS.open("/task8.csv", "w");
    if (!file) {
        Serial.println("Failed to open file for reading");
        return;
    }
    file.println("Mode,AES128 Encrypt,AES128 Decrypt,AES192 Encrypt,AES192 Decrypt,AES256 Encrypt,AES256 Decrypt,Buffer Length");
    for (; size<=32768; size*=2){
        for (int i = 0; i < 10; i++) {
            Times times = Times{};
            fillArrayWithRandomData(PLAINTEXT_BUFFER, size);
            bench(&times, size);
            file.printf("CTR,%lu,%lu,%lu,%lu,%lu,%lu,%zu\n", times.Ctr128Encrypt, times.Ctr128Decrypt, times.Ctr192Encrypt, times.Ctr192Decrypt, times.Ctr256Encrypt, times.Ctr256Decrypt,size);
            file.printf("Eax,%lu,%lu,%lu,%lu,%lu,%lu,%zu\n", times.Eax128Encrypt, times.Eax128Decrypt, times.Eax192Encrypt, times.Eax192Decrypt, times.Eax256Encrypt, times.Eax256Decrypt,size);
            file.printf("GCM,%lu,%lu,%lu,%lu,%lu,%lu,%zu\n", times.Gcm128Encrypt, times.Gcm128Decrypt, times.Gcm192Encrypt, times.Gcm192Decrypt, times.Gcm256Encrypt, times.Gcm256Decrypt,size);
            file.printf("XTS,%lu,%lu,%lu,%lu,%lu,%lu,%zu\n", times.Xts128Encrypt, times.Xts128Decrypt, times.Xts192Encrypt, times.Xts192Decrypt, times.Xts256Encrypt, times.Xts256Decrypt,size);
            yield();
            // printProgressBar(i, iterations);
        }
    }
    file.close();
}


// 16, 32, 64, 128, 256, 512, 1024, 2056, 4112, 8224 