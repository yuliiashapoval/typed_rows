//
// Created by Yulia Shapoval on 01.07.2026.
//

#include "CipherManager.h"
#include <iostream>

#ifdef __APPLE__
#include <dlfcn.h>
#endif

std::string CipherManager::processWithDLL(const std::string& inputText, int key, bool encryptMode) {
    std::string buffer = inputText;

#ifdef __APPLE__
    void* handle = dlopen("./libcipher.dylib", RTLD_LAZY);

    if (!handle) {
        std::cout << "'libcipher.dylib' не підключено динамічно. Працює симуляція.\n";
        simulatedCipher(buffer, key, encryptMode);
        return buffer;
    }

    CreateCaesarFunc create_caesar = (CreateCaesarFunc)dlsym(handle, "cipher_create_caesar");
    EncryptFunc cipher_encrypt     = (EncryptFunc)dlsym(handle, "cipher_encrypt");
    DecryptFunc cipher_decrypt     = (DecryptFunc)dlsym(handle, "cipher_decrypt");
    DestroyFunc cipher_destroy     = (DestroyFunc)dlsym(handle, "cipher_destroy");
    FreeFunc cipher_free           = (FreeFunc)dlsym(handle, "cipher_free");

    if (create_caesar && cipher_encrypt && cipher_decrypt && cipher_destroy && cipher_free) {

        cipher_t* myCipher = create_caesar(key);

        char* c_str_result = nullptr;

        if (encryptMode) {
            c_str_result = cipher_encrypt(myCipher, buffer.c_str());
        } else {
            c_str_result = cipher_decrypt(myCipher, buffer.c_str());
        }

        if (c_str_result) {
            buffer = std::string(c_str_result);
            cipher_free(c_str_result);
        }

        cipher_destroy(myCipher);

    } else {
        std::cout << "Помилка: У .dylib файлі відсутні необхідні функції АПІ!\n";
    }

    dlclose(handle);
#else
    simulatedCipher(buffer, key, encryptMode);
#endif

    return buffer;
}

void CipherManager::simulatedCipher(std::string& data, int key, bool encryptMode) {
    int shift = encryptMode ? key : -key;
    for (char& c : data) {
        if (c >= ' ' && c <= '~') {
            c = static_cast<char>(((c - ' ' + shift) % 95 + 95) % 95 + ' ');
        }
    }
}