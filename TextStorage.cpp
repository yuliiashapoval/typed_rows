#include "TextStorage.h"

TextStorage::~TextStorage() {
    clear();
}

void TextStorage::clear() {
    for (Line* line : lines) {
        delete line; // Очищення пам'яті, щоб не було витоків
    }
    lines.clear();
}

void TextStorage::addLine(Line* newLine) {
    lines.push_back(newLine);
}

void TextStorage::printAll() const {
    if (lines.empty()) {
        std::cout << "Редактор порожній" << std::endl;
        return;
    }
    std::cout << "\nПоточний текст" << std::endl;
    for (size_t i = 0; i < lines.size(); ++i) {
        std::cout << i << ". ";
        lines[i]->print();
    }
    std::cout << std::endl;
}

void TextStorage::deleteLine(size_t index) {
    if (index < lines.size()) {
        delete lines[index];
        lines.erase(lines.begin() + index);
        std::cout << "Рядок видалено успішно!\n";
    } else {
        std::cout << "Некоректний індекс рядка\n";
    }
}

std::string TextStorage::getAllSerialized() const {
    std::string result = "";
    for (Line* line : lines) {
        result += line->serialize() + "\n"; 
    }
    return result;
}

std::vector<Line*> TextStorage::getSnapshot() const {
    std::vector<Line*> snapshot;
    for (Line* line : lines) {
        snapshot.push_back(line->clone());
    }
    return snapshot;
}

void TextStorage::restoreSnapshot(const std::vector<Line*>& snapshot) {
    clear();
    for (Line* line : snapshot) {
        lines.push_back(line->clone());
    }
}