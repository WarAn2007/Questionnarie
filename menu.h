#pragma once
#include "tests.h"
#include "flashcardsTest.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
const std::string default_test = "test_example";
const std::string default_result = "result_example";
static FlashCardSet FlashcardManager;
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

int menuForFlashcards() {

    int option;

    cout << "\n===== FLASHCARD MENU =====\n";

    cout << "[1] Create flashcards\n";
    cout << "[2] View flashcards\n";
    cout << "[3] Test flashcards\n";
    cout << "[4] Save set\n";
    cout << "[5] Load set\n";
    cout << "[6] Show sets\n";
    cout << "[7] Exit\n";

    cout << " >> ";

    while (!(cin >> option)) {

        cout << "Invalid input!\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << " >> ";
    }

    return option;
}

void createFlashcardsMenu() {

    cout << "\nCreating flashcards...\n";

    cin.ignore(256, '\n');

    FlashcardManager.createSet();
}

void viewFlashcardsMenu() {

    FlashcardManager.viewSet();
}

void testFlashcardsMenu() {

    FlashcardManager.testSet();
}


void showSetsMenu() {

    FlashcardManager.showSets();
}