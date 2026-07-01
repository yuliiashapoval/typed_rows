#ifndef TEXTSTORAGE_H
#define TEXTSTORAGE_H

#include <vector>
#include "Line.h"

class TextStorage {
private:
    std::vector<Line*> lines;
public:
    ~TextStorage();
    void clear();
    void addLine(Line* newLine);
    void printAll() const;
    void deleteLine(size_t index);
    std::string getAllSerialized() const;
    std::vector<Line*> getSnapshot() const;
    void restoreSnapshot(const std::vector<Line*>& snapshot);
};

#endif