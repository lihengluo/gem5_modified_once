#include <openssl/aes.h>
#include <cstring>
#include <iostream>

void encrypt(const unsigned char* plaintext, const unsigned char* key, unsigned char* ciphertext) {
    AES_KEY aesKey;
    AES_set_encrypt_key(key, 128, &aesKey);
    AES_encrypt(plaintext, ciphertext, &aesKey);
}

void decrypt(const unsigned char* ciphertext, const unsigned char* key, unsigned char* plaintext) {
    AES_KEY aesKey;
    AES_set_decrypt_key(key, 128, &aesKey);
    AES_decrypt(ciphertext, plaintext, &aesKey);
}

int main() {
    const unsigned char key[] = "0123456789abcdef"; // 128-bit key (16 bytes)
    const unsigned char plaintext[] = "This is the plaintext message.";

    unsigned char ciphertext[AES_BLOCK_SIZE];
    unsigned char decrypted_text[AES_BLOCK_SIZE];

    encrypt(plaintext, key, ciphertext);
    std::cout << "Ciphertext: ";
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        printf("%02x", ciphertext[i]);
    }
    std::cout << std::endl;

    decrypt(ciphertext, key, decrypted_text);
    std::cout << "Decrypted text: " << decrypted_text << std::endl;

    return 0;
}