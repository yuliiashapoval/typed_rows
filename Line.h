#ifndef LINE_H
#define LINE_H

#include <iostream>
#include <string>

class Line {
public:
    virtual ~Line() {}
    virtual void print() const = 0;
    virtual std::string serialize() const = 0;
    virtual Line* clone() const = 0;
};

class TextLine : public Line {
private:
    std::string text;
public:
    TextLine(const std::string& t) : text(t) {}
    void print() const override { std::cout << "Текст: " << text << std::endl; }

    std::string serialize() const override { return "TEXT:" + text; }
    Line* clone() const override { return new TextLine(*this); }
};

class ChecklistLine : public Line {
private:
    std::string task;
    bool isChecked;
public:
    ChecklistLine(const std::string& t, bool checked) : task(t), isChecked(checked) {}
    void print() const override {
        std::string status = isChecked ? "[ x ] " : "[   ] ";
        std::cout << status << task << std::endl;
    }

    std::string serialize() const override {
        return "CHECK:" + std::string(isChecked ? "1" : "0") + "|" + task;
    }
    Line* clone() const override { return new ChecklistLine(*this); }
};

class ContactLine : public Line {
private:
    std::string firstName;
    std::string lastName;
    std::string email;
public:
    ContactLine(const std::string& fn, const std::string& ln, const std::string& e)
        : firstName(fn), lastName(ln), email(e) {}
    void print() const override {
        std::cout << "Контакт: " << firstName << " " << lastName << ", E-mail: " << email << std::endl;
    }

    std::string serialize() const override {
        return "CONTACT:" + firstName + "|" + lastName + "|" + email;
    }
    Line* clone() const override { return new ContactLine(*this); }
};

#endif
