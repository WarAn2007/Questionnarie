#include "menu.h"

using namespace std;

void testMode() {
	int option2;
	do {
		// menudisp() from menu.h, displays menu options and provides with chosen option
		option2 = menudisp();

		switch (option2) {

		case 1: case1(); break;// Create Test

		case 2: case2(); break; // Take a test

		case 3: case3(); break; // View results of tests

		case 4: case4(); break; // Exit to main menu

		default:
			std::cout << "Invalid number! Choose again from 1 to 4" << std::endl; // Invalid options handler
			cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	} while (option2 != 4);
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
	std::cout << "\nFiles stored in Tests and Flashcards(.dat) and Results(.txt)\n";

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

		case 3:
			cout << "Exiting program..." << endl;
			return 0;
		default:
			cout << "Invalid choice! Please choose again from 1 to 3." << endl;
		}

	} while (option1 != 3);
}