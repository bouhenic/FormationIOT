#include "HMAC.h"
#include <Arduino.h> // Pour définir le type byte

void HMAC::calculateHMAC(const byte* key, size_t keyLength,
                         const byte* message, size_t messageLength,
                         byte* outputHMAC) {
    byte keyBlock[blockSize];   // Clé ajustée à la taille du bloc
    byte innerPadding[blockSize];
    byte outerPadding[blockSize];

    // Étendre ou tronquer la clé pour qu'elle corresponde à la taille du bloc
    memset(keyBlock, 0, blockSize);
    if (keyLength > blockSize) {
        SHA256 sha256;
        sha256.update(key, keyLength);
        sha256.finalize(keyBlock, 32); // Résultat du hash pour la clé
    } else {
        memcpy(keyBlock, key, keyLength);
    }

    // Préparer les paddings intérieurs et extérieurs
    for (size_t i = 0; i < blockSize; i++) {
        innerPadding[i] = keyBlock[i] ^ 0x36; // ipad
        outerPadding[i] = keyBlock[i] ^ 0x5C; // opad
    }

    // Calcul du HMAC
    SHA256 innerHasher;
    innerHasher.update(innerPadding, blockSize);
    innerHasher.update(message, messageLength);
    byte innerHash[32];
    innerHasher.finalize(innerHash, 32);

    SHA256 outerHasher;
    outerHasher.update(outerPadding, blockSize);
    outerHasher.update(innerHash, 32);
    outerHasher.finalize(outputHMAC, 32);
}
