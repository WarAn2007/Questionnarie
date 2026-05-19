#pragma once
#include "questions.h"

class Test {
public:


    void createTest(const std::string& filename) {
        int n = 0;
        std::cout << "How many questions? ";
        std::cin >> n;
        std::cin.ignore(256, '\n');
        if (n <= 0) { std::cout << "Must be at least 1.\n"; return; }

		std::vector<Question*> questions; // storage of questions in memory

        for (int i = 0; i < n; i++) {
            int typeChoice = 0;

            std::cout << "\n--- Question " << (i + 1) << " ---\n";
            while (typeChoice < 1 || typeChoice > 3) {
                std::cout << "  Type: [1] Single choice  [2] Multiple choice  [3] True/False\n  >> ";
                while (!(std::cin >> typeChoice)) {
                    std::cout << "Invalid input data type. Please enter integers only!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << ">> ";
                }
                std::cin.ignore(256, '\n');
            }
            
            Question* q = makeQuestion(static_cast<QuestionType>(typeChoice));
            q->inputFromUser();
            questions.push_back(q);
        }

        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cout << "Error: could not create '" << filename << "'.\n";
            freeAll(questions);
            return;
        }

        file.write(reinterpret_cast<char*>(&n), sizeof(int));
        for (Question* q : questions) {
            int type = static_cast<int>(q->getType());
            file.write(reinterpret_cast<char*>(&type), sizeof(int));
            q->writeToFile(file);
        }
        file.close();
        freeAll(questions);
        std::cout << "\nTest saved to '" << filename << "' (" << n << " question(s)).\n";
    }

    void takeTest(const std::string& filename, const std::string& resultsFile) {
        std::vector<Question*> questions;
        if (!loadFromFile(filename, questions)) return;

        std::cout << "Enter your name: ";
        std::string name;
        std::getline(std::cin, name);
        if (name.empty()) name = "Anonymous";

        int correct = 0;
        int total = static_cast<int>(questions.size());

        for (int i = 0; i < total; i++) {
            questions[i]->display(i + 1);
            if (questions[i]->checkAnswer()) {
                std::cout << "Correct! +1\n";
                correct++;
            }
            else {
                std::cout << "Wrong!   +0\n";
            }
        }

        double pct = total > 0 ? 100.0 * correct / total : 0.0;
        std::cout << "\n==== Results ====\n";
        std::cout << "Total Questions: " << total << "\n";
        std::cout << "Correct Answers: " << correct << "\n";
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "Percentage:      " << pct << "%\n";

        std::ofstream results(resultsFile, std::ios::app);
        if (results) {
            results << "=== Test Result ===\n";
            results << "Name:      " << name << "\n";
            results << "Test file: " << filename << "\n";
            results << "Questions: " << total << "\n";
            results << "Correct:   " << correct << "\n";
            results << std::fixed << std::setprecision(2);
            results << "Score:     " << pct << "%\n\n";
            results.close();
            std::cout << "Results appended to '" << resultsFile << "'.\n";
        }
        else {
            std::cout << "Warning: could not write to '" << resultsFile << "'.\n";
        }

        freeAll(questions);
    }

    void viewResults(const std::string& resultsFile) {
        std::ifstream file(resultsFile);
        if (!file) {
            std::cout << "No results found in '" << resultsFile << "'. Take a test first!\n";
            return;
        }
        std::cout << "\n========== All Test Results ==========\n";
        std::string line;
        while (std::getline(file, line)) std::cout << line << "\n";
        std::cout << "======================================\n";
        file.close();
    }

private:
    bool loadFromFile(const std::string& filename, std::vector<Question*>& out) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cout << "Error: could not open '" << filename << "'. Create the test first.\n";
            return false;
        }
        int n = 0;
        file.read(reinterpret_cast<char*>(&n), sizeof(int));
        if (n <= 0) { std::cout << "This test file contains no questions.\n"; return false; }

        for (int i = 0; i < n; i++) {
            int typeInt = 0;
            file.read(reinterpret_cast<char*>(&typeInt), sizeof(int));
            Question* q = makeQuestion(static_cast<QuestionType>(typeInt));
            if (!q) { std::cout << "Error: unknown question type in file.\n"; freeAll(out); return false; }
            q->readFromFile(file);
            out.push_back(q);
        }
        file.close();
        return true;
    }

    void freeAll(std::vector<Question*>& questions) {
        for (Question* q : questions) delete q;
        questions.clear();
    }
};