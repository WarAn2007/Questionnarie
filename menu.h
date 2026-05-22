#pragma once
#include "tests.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const std::string default_test = "test_example";
const std::string default_result = "result_example";

static Test TestManager;

static std::string askFilename(const std::string& label, const std::string& defaultName, const std::string& extension) {
    std::string name;

    std::cout << label << " (Enter for example '" << defaultName << "'):\n";
    std::cout << ">> ";
    std::getline(std::cin, name);
	name = name + extension;
    return name.empty() ? defaultName : name;
}

int menudisp() {
    int option;
    std::cout << std::endl;
    // Managing tests
    std::cout << "[1] Create Test" << std::endl;
    std::cout << "[2] Take a Test" << std::endl;
    std::cout << "[3] Results of Tests" << std::endl;
	std::cout << "[4] Exit to Main Menu" << std::endl;
    std::cout << " >> ";

    while (!(std::cin >> option)) {
        std::cout << "Invalid input data type. Please enter integers only!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  >> ";
    }

    return option;
}

int menuForFlashcards() {
    int option;

    cout << "\n===== FLASHCARD APP =====\n";

    cout << "1. Create new set\n";
    cout << "2. Show all sets\n";
    cout << "3. View set\n";
    cout << "4. Test set\n";
    cout << "5. Exit\n";

    cout << "Choose: ";
    while (!(std::cin >> option)) {
        std::cout << "Invalid input data type. Please enter integers only!" << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  >> ";
    }
    return option;


}

void case1() {
    std::cout << "\nCreating Test...\n";
    std::cin.ignore(256, '\n');
    std::string testFile = askFilename("Test file name", default_test, ".dat");
    TestManager.createTest(testFile);
}


void case2() {
    std::cout << "Taking a Test..." << std::endl;
    std::cin.ignore(256, '\n');
    std::string testFile = askFilename("Test file to load", default_test, ".dat");
    std::string resultsFile = askFilename("Results file to save to", default_result, ".txt");
    TestManager.takeTest(testFile, resultsFile);
}


void case3() {
    std::cout << "Viewing results of tests..." << std::endl;
    std::cin.ignore(256, '\n');
    std::string resultsFile = askFilename("Results file to view", default_result, ".txt");
    TestManager.viewResults(resultsFile);
}
void case4() {
    std::cout << "Exiting from Test Mode..." << std::endl;
}

//Diana's part
void MainMenu() {
    cout << "1. Test" << endl;
    cout << "2. Flashcards" << endl;
	cout << "3. Exit" << endl;
	cout << " >> ";
}

void saveSet(vector<FlashCard>& flashcards, string setName) {

    string filename = setName + ".txt";

    ofstream file(filename);

    if (!file) {
        cout << "Error creating file!\n";
        return;
    }

    for (int i = 0; i < flashcards.size(); i++) {
        file << flashcards[i].getQuestion() << endl;
        file << flashcards[i].getAnswer() << endl;
    }

    file.close();

    ofstream listOfFiles("sets.txt", ios::app);

    if (listOfFiles) {
        listOfFiles << setName << endl;
    }

    listOfFiles.close();

    cout << "Set saved successfully!\n";
}

// Load set
vector<FlashCard> loadSet(string setName) {

    vector<FlashCard> flashcards;

    string filename = setName + ".txt";

    ifstream file(filename);

    if (!file) {
        cout << "Set not found!\n";
        return flashcards;
    }

    string question;
    string answer;

    while (getline(file, question) && getline(file, answer)) {

        FlashCard f(question, answer);

        flashcards.push_back(f);
    }

    file.close();

    return flashcards;
}

void showSets() {

    ifstream file("sets.txt");

    if (!file) {
        cout << "No sets available!\n";
        return;
    }

    cout << "\n===== AVAILABLE SETS =====\n";

    string setName;
    int counter = 1;

    while (getline(file, setName)) {
        cout << counter << ". " << setName << endl;
        counter++;
    }

    file.close();
}


vector<FlashCard> createFlashcards() {

    vector<FlashCard> flashcards;

    int number;

    cout << "How many flashcards do you want to create? ";
    cin >> number;
    cin.ignore();

    for (int i = 0; i < number; i++) {

        FlashCard f;

        string question;
        string answer;

        cout << "\nEnter question #" << i + 1 << ": ";
        getline(cin, question);

        cout << "Enter answer #" << i + 1 << ": ";
        getline(cin, answer);

        f.setQuestion(question);
        f.setAnswer(answer);

        flashcards.push_back(f);
    }

    return flashcards;
}

// View set
void viewSet(vector<FlashCard>& flashcards) {

    if (flashcards.empty()) {
        cout << "Set is empty!\n";
        return;
    }

    cout << "\n===== FLASHCARDS =====\n";

    for (int i = 0; i < flashcards.size(); i++) {

        cout << "\nCard #" << i + 1 << endl;

        cout << "Q: " << flashcards[i].getQuestion() << endl;

        cout << "A: " << flashcards[i].getAnswer() << endl;

        cout << "-------------------------\n";
    }
}

// Test mode
void testSet(vector<FlashCard>& flashcards) {

    if (flashcards.empty()) {
        cout << "Set is empty!\n";
        return;
    }

    cout << "\n===== TEST MODE =====\n";

    for (int i = 0; i < flashcards.size(); i++) {

        cout << "\nQ: " << flashcards[i].getQuestion() << endl;

        cout << "Press ENTER to show answer...";
        cin.get();

        cout << "A: " << flashcards[i].getAnswer() << endl;

        cout << "=========================\n";
    }
}

