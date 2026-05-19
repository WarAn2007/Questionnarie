#pragma once
#include "tests.h"

const std::string default_test = "default.dat";
const std::string default_result = "results.txt";

static Test TestManager;
static std::string askFilename(const std::string& label, const std::string& defaultName) {
	std::string name;

	std::cout << label << " (Enter for example '" << defaultName << "'):\n";
	std::cout << ">> ";
	std::getline(std::cin, name);
	return name.empty() ? defaultName : name;
}

int menudisp() {
	int option;
	std::cout << std::endl;
	// Managing tests
	std::cout << "[1] Create Test" << std::endl;
	std::cout << "[2] Take a Test" << std::endl;
	std::cout << "[3] Results of Tests" << std::endl;

	// Managing flashcards
	std::cout << "[4] Create Flashcard" << std::endl;
	std::cout << "[5] Take a Flashcard" << std::endl;
	std::cout << "[6] Results of Flashcards" << std::endl;

	std::cout << "[7] Exit the Program" << std::endl;
	std::cout << "  >> ";

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
	std::string testFile = askFilename("Test file name", default_test);
	TestManager.createTest(testFile);
}


void case2() {
	std::cout << "Taking a test..." << std::endl;
	std::cin.ignore(256, '\n');
	std::string testFile = askFilename("Test file to load", default_test);
	std::string resultsFile = askFilename("Results file to save to", default_result);
	TestManager.takeTest(testFile, resultsFile);
}


void case3() {
	std::cout << "Viewing results of tests..." << std::endl;
	std::cin.ignore(256, '\n');
	std::string resultsFile = askFilename("Results file to view", default_result);
	TestManager.viewResults(resultsFile);
}

void case4() {
	std::cout << "Creating a flashcard..." << std::endl;
}

void case5() {
	std::cout << "Taking a flashcard..." << std::endl;
}


void case6() {
	std::cout << "Viewing results of flashcards..." << std::endl;
}

void case7() {
	std::cout << "Exiting program..." << std::endl;
}
void defcase() {
	std::cout << "Invalid number! Choose again from 1 to 7" << std::endl;
}