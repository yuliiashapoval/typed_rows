#include <iostream>
#include <fstream>
#include <string>
#include "CipherManager.h"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        return "";
    }
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

void writeFile(const std::string& path, const std::string& data) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << data;
    }
}

int main() {
    int operation;
    std::string inputPath, outputPath;
    int key;

    std::cout << "Оберіть операцію (1 - Шифрувати, 2 - Дешифрувати): ";
    std::cin >> operation;
    std::cin.ignore();

    std::cout << "Введіть шлях до початкового файлу: ";
    std::getline(std::cin, inputPath);

    std::cout << "Введіть шлях до кінцевого файлу: ";
    std::getline(std::cin, outputPath);

    std::cout << "Введіть цифровий ключ: ";
    std::cin >> key;

    std::string fileContent = readFile(inputPath);
    if (fileContent.empty()) {
        std::cout << "Помилка: Не вдалося відкрити або прочитати файл за шляхом: " << inputPath << "\n";
        return 1;
    }

    CipherManager manager;
    bool isEncrypt = (operation == 1);

    std::cout << "\nОбробка даних через зовнішню бібліотеку...\n";
    std::string resultText = manager.processWithDLL(fileContent, key, isEncrypt); // [cite: 29, 32, 61]

    writeFile(outputPath, resultText); // [cite: 30]

    std::cout << "Успішно! Результат збережено у: " << outputPath << "\n";

    return 0;
}
