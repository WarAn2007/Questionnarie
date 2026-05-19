#pragma once

#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>

// -- Question type tags ------------------------------------------------------

enum QuestionType {
    single_choice = 1,
    multiple_choice = 2,
    true_false = 3
};

// -- Helper: parse "1 2 3" into a bool[4] ------------------------------------

static void parseAnswers(const std::string& line, bool out[4]) {
    for (int i = 0; i < 4; i++) out[i] = false;
    for (size_t i = 0; i < line.size(); i++)
        if (line[i] >= '1' && line[i] <= '4')
            out[line[i] - '1'] = true;
}

// -- Abstract base class -----------------------------------------------------
class Question {
protected:
    char text[256];
public:
    Question() { std::memset(text, 0, sizeof(text)); }
    virtual ~Question() {}

    virtual void inputFromUser() = 0;
    virtual void display(int num) const = 0;
    virtual bool checkAnswer() = 0;
    virtual void writeToFile(std::ofstream& f) const = 0;
    virtual void readFromFile(std::ifstream& f) = 0;
    virtual QuestionType getType() const = 0;
};

// -- Single choice -----------------------------------------------------------

class SingleChoice : public Question {
    char options[4][128];
    int  correctIndex;

public:
    SingleChoice() : correctIndex(0) {
        std::memset(options, 0, sizeof(options));
    }

    void inputFromUser() override {
        std::cout << "  Question text: ";
        std::string t;
        std::getline(std::cin, t);
        strncpy_s(text, t.c_str(), 255);
        text[255] = '\0';

        for (int j = 0; j < 4; j++) {
            std::cout << "  Option " << (j + 1) << ": ";
            std::string opt;
            std::getline(std::cin, opt);
            strncpy_s(options[j], opt.c_str(), 127);
            options[j][127] = '\0';
        }

        int ans = 0;
        while (ans < 1 || ans > 4) {
            std::cout << "  Correct answer (1-4): ";
            std::cin >> ans;
            std::cin.ignore(256, '\n');
        }
        correctIndex = ans - 1;
    }

    void display(int num) const override {
        std::cout << "\n" << num << ") " << text << "\n";
        for (int j = 0; j < 4; j++)
            std::cout << "   " << (j + 1) << ". " << options[j] << "\n";
    }

    bool checkAnswer() override {
        int ans = 0;
        while (ans < 1 || ans > 4) {
            std::cout << "Your answer: ";
            std::cin >> ans;
            std::cin.ignore(256, '\n');
        }
        return (ans - 1) == correctIndex;
    }

    void writeToFile(std::ofstream& f) const override {
        f.write(text, sizeof(text));
        f.write(reinterpret_cast<const char*>(options), sizeof(options));
        f.write(reinterpret_cast<const char*>(&correctIndex), sizeof(int));
    }

    void readFromFile(std::ifstream& f) override {
        f.read(text, sizeof(text));
        f.read(reinterpret_cast<char*>(options), sizeof(options));
        f.read(reinterpret_cast<char*>(&correctIndex), sizeof(int));
    }

    QuestionType getType() const override { return single_choice; }
};

// -- Multiple choice ---------------------------------------------------------

class MultipleChoice : public Question {
    char options[4][128];
    bool correctAnswers[4];

public:
    MultipleChoice() {
        std::memset(options, 0, sizeof(options));
        std::memset(correctAnswers, 0, sizeof(correctAnswers));
    }

    void inputFromUser() override {
        std::cout << "  Question text: ";
        std::string t;
        std::getline(std::cin, t);
        strncpy_s(text, t.c_str(), 255);
        text[255] = '\0';

        for (int j = 0; j < 4; j++) {
            std::cout << "  Option " << (j + 1) << ": ";
            std::string opt;
            std::getline(std::cin, opt);
            strncpy_s(options[j], opt.c_str(), 127);
            options[j][127] = '\0';
        }

        std::cout << "  Correct answers, space-separated (e.g. 1 3): ";
        std::string line;
        std::getline(std::cin, line);
        parseAnswers(line, correctAnswers);
    }

    void display(int num) const override {
        std::cout << "\n" << num << ") " << text << "\n";
        for (int j = 0; j < 4; j++)
            std::cout << "   " << (j + 1) << ". " << options[j] << "\n";
    }

    bool checkAnswer() override {
        std::cout << "Your answers (space-separated, e.g. 1 3): ";
        std::string line;
        std::getline(std::cin, line);
        bool userAnswers[4] = {};
        parseAnswers(line, userAnswers);
        for (int j = 0; j < 4; j++)
            if (userAnswers[j] != correctAnswers[j]) return false;
        return true;
    }

    void writeToFile(std::ofstream& f) const override {
        f.write(text, sizeof(text));
        f.write(reinterpret_cast<const char*>(options), sizeof(options));
        f.write(reinterpret_cast<const char*>(correctAnswers), sizeof(correctAnswers));
    }

    void readFromFile(std::ifstream& f) override {
        f.read(text, sizeof(text));
        f.read(reinterpret_cast<char*>(options), sizeof(options));
        f.read(reinterpret_cast<char*>(correctAnswers), sizeof(correctAnswers));
    }

    QuestionType getType() const override { return multiple_choice; }
};

// -- True / False ------------------------------------------------------------

class TrueFalse : public Question {
    bool correctAnswer;   // true = "True" is correct

public:
    TrueFalse() : correctAnswer(false) {}

    void inputFromUser() override {
        std::cout << "  Question text: ";
        std::string t;
        std::getline(std::cin, t);
        strncpy_s(text, t.c_str(), 255);
        text[255] = '\0';

        int ans = -1;
        while (ans != 0 && ans != 1) {
            std::cout << "  Correct answer (1 = True, 0 = False): ";
            std::cin >> ans;
            std::cin.ignore(256, '\n');
        }
        correctAnswer = (ans == 1);
    }

    void display(int num) const override {
        std::cout << "\n" << num << ") " << text << "\n";
        std::cout << "   (1 for True, 0 for False)\n";
    }

    bool checkAnswer() override {
        std::cout << "Your answer: ";
        int ans;
        std::cin >> ans;
        std::cin.ignore(256, '\n');
        return (ans == 1) == correctAnswer;
    }

    void writeToFile(std::ofstream& f) const override {
        f.write(text, sizeof(text));
        f.write(reinterpret_cast<const char*>(&correctAnswer), sizeof(bool));
    }

    void readFromFile(std::ifstream& f) override {
        f.read(text, sizeof(text));
        f.read(reinterpret_cast<char*>(&correctAnswer), sizeof(bool));
    }

    QuestionType getType() const override { return true_false; }
};

// -- Factory: create the right derived object from a type tag ----------------

static Question* makeQuestion(QuestionType type) {
    if (type == single_choice)   return new SingleChoice();
    if (type == multiple_choice) return new MultipleChoice();
    if (type == true_false)      return new TrueFalse();
    return nullptr;
}