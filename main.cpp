#include "menu.h"

int main() {
	int option;

	std::cout << "+---------------------------------------+" << std::endl;
	std::cout << "| =======   C++ TEST MANAGER    ======= |" << std::endl;
	std::cout << "+---------------------------------------+" << std::endl;
	std::cout << "\nfiles stored in default directory(default.dat and results.txt, but you can change it in the code)\n";
	do {
		// menudisp() from menu.h, displays menu options and provides with chosen option
		option = menudisp();

		switch (option) {
			
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
			case7(); return 0; // Exit the program

		default:
			defcase(); // Invalid options handler
		}
	} while (option != 7);
}