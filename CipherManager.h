#ifndef CIPHERMANAGER_H
#define CIPHERMANAGER_H

#include <string>
typedef void cipher_t;

typedef cipher_t* (*CreateCaesarFunc)(int key);
typedef char* (*EncryptFunc)(cipher_t* cipher, const char* text);
typedef char* (*DecryptFunc)(cipher_t* cipher, const char* text);
typedef void      (*DestroyFunc)(cipher_t* cipher);
typedef void      (*FreeFunc)(char* str);

class CipherManager {
public:
    std::string processWithDLL(const std::string& inputText, int key, bool encryptMode);

private:
    void simulatedCipher(std::string& data, int key, bool encryptMode);
};

#endif