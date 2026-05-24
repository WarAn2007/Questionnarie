#include "menu.h"
using namespace std;
void MainMenu() {
	cout << "Choose mode: " << endl;
	cout << "1. Test Mode" << endl;
	cout << "2. Flashcard mode " << endl;
}
void testMode() {
	int option2;
	do {
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

		case 1:
			createFlashcardsMenu();
			break;

		case 2:
			viewFlashcardsMenu();
			break;

		case 3:
			testFlashcardsMenu();
			break;

		case 4:
			cout << "Exit to main menu...\n";
			break;

		default:

			cout << "Invalid number! Choose again from 1 to 4\n";

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	} while (option3 != 4);
}
void menu() {

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