#ifndef HMAC_H
#define HMAC_H

#include <Arduino.h> // Pour définir le type byte
#include <SHA256.h>
#include <string.h> // Pour memcpy et memset

class HMAC {
public:
    static void calculateHMAC(const byte* key, size_t keyLength,
                              const byte* message, size_t messageLength,
                              byte* outputHMAC);

private:
    static const size_t blockSize = 64; // Taille du bloc SHA-256
};

#endif
