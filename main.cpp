#include "menu.h"
#include <iostream>
#include <string>
using namespace std;
void testMode() {
	int option2;
	do {
		// menudisp() from menu.h, displays menu options and provides with chosen option
		option2 = menudisp();

		switch (option2) {

		case 1:
			case1(); break;// Create Test

		case 2:
			case2(); break; // Take a test

		case 3:
			case3(); break; // View results of tests

		case 4:
			case4(); break; // Create a Flashcard

		case 5:
			case5(); break; // Take a Flashcard

		case 6:
			case6(); break; // View results of flashcards

		case 7:
			case7();
			return; // Exit the program

		default:
			defcase(); // Invalid options handler
		}
	} while (option2 != 7);
}

void flashcardsMode() {
	int option3;
	do {
		option3 = menuForFlashcards();
		switch (option3) {
		case 1: {
			string setName;
			cout << "Enter set name: ";
			cin.ignore();
			getline(cin, setName);
			vector<FlashCard> flashcards = createFlashcards();
			saveSet(flashcards, setName);
			break;
		}

		case 2: {
			showSets();
			break;
		}

		case 3: {
			showSets();
			string setName;
			cout << "\nEnter set name to open: ";
			cin.ignore();
			getline(cin, setName);
			vector<FlashCard> flashcards = loadSet(setName);
			viewSet(flashcards);
			break;
		}

		case 4: {

			showSets();
			string setName;
			cout << "\nEnter set name to test: "; \
				cin.ignore();
			getline(cin, setName);
			vector<FlashCard> flashcards = loadSet(setName);
			testSet(flashcards);
			break;
		}
		case 5:
			return;
		default:
			cout << "Invalid choice!\n";
		}
	} while (option3 != 5);
}


int main() {
	int option1;

	std::cout << "+---------------------------------------+" << std::endl;
	std::cout << "| =======   C++ TEST MANAGER    ======= |" << std::endl;
	std::cout << "+---------------------------------------+" << std::endl;
	std::cout << "\nfiles stored in default directory(default.dat and results.txt, but you can change it in the code)\n";

	do {
		MainMenu();
		cin >> option1;
		switch (option1) {
		case 1:
			testMode();
			break;
		case 2:
			flashcardsMode();
			break;
		}

	} while (option1 != 3);
}