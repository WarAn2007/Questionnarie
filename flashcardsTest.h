#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FlashCardSet {

public:

    // ---------------- CREATE SET ----------------
    void createSet() {

        string setName;

        cout << "Enter set name: ";
        cin.ignore();
        getline(cin, setName);

        string filename = setName + ".txt";

        ofstream file(filename);

        if (!file) {
            cout << "Error creating file!\n";
            return;
        }

        int number;

        cout << "How many flashcards? ";
        cin >> number;
        cin.ignore();

        for (int i = 0; i < number; i++) {

            string question, answer;

            cout << "\nQuestion #" << i + 1 << ": ";
            getline(cin, question);

            cout << "Answer #" << i + 1 << ": ";
            getline(cin, answer);

            file << question << endl;
            file << answer << endl;
        }

        file.close();

        ofstream list("sets.txt", ios::app);
        list << setName << endl;
        list.close();

        cout << "Set saved!\n";
    }

    // ---------------- SHOW SETS ----------------
    void showSets() {

        ifstream file("sets.txt");

        if (!file) {
            cout << "No sets available!\n";
            return;
        }

        cout << "\n===== SETS =====\n";

        string name;
        int index = 1;

        while (getline(file, name)) {
            cout << index++ << ". " << name << endl;
        }

        file.close();
    }

    // ---------------- VIEW SET ----------------
    void viewSet() {

        showSets();

        int choice;
        cout << "\nChoose set number: ";
        cin >> choice;
        cin.ignore();

        ifstream file("sets.txt");

        string setName;
        int current = 1;

        while (getline(file, setName)) {

            if (current == choice) break;

            current++;
        }

        file.close();

        if (setName == "") {
            cout << "Invalid choice!\n";
            return;
        }

        string filename = setName + ".txt";

        ifstream setFile(filename);

        if (!setFile) {
            cout << "File not found!\n";
            return;
        }

        cout << "\n===== " << setName << " =====\n";

        string question, answer;

        while (getline(setFile, question) && getline(setFile, answer)) {

            cout << "\nQ: " << question << endl;
            cout << "A: " << answer << endl;
            cout << "-------------------\n";
        }

        setFile.close();
    }

    // ---------------- TEST SET ----------------
    void testSet() {

        showSets();

        int choice;
        cout << "\nChoose set number: ";
        cin >> choice;
        cin.ignore();

        ifstream file("sets.txt");

        string setName;
        int current = 1;

        while (getline(file, setName)) {

            if (current == choice) break;

            current++;
        }

        file.close();

        if (setName == "") {
            cout << "Invalid choice!\n";
            return;
        }

        string filename = setName + ".txt";

        ifstream setFile(filename);

        if (!setFile) {
            cout << "File not found!\n";
            return;
        }

        cout << "\n===== TEST: " << setName << " =====\n";

        string question, answer;

        while (getline(setFile, question) && getline(setFile, answer)) {

            cout << "\nQ: " << question << endl;

            cout << "Press ENTER...";
            cin.get();

            cout << "A: " << answer << endl;
            cout << "-------------------\n";
        }

        setFile.close();
    }
};