#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "HashTable.h"
using namespace std;


//Getting a valid filename so that I can use other user files.
string getValidFilename() {
    string filename;
    ifstream file;

    do {
        cout << "Enter the name of the file you would like to read from: ";
        cin >> filename;

        file.open(filename);
        if (!file) {
            cout << "Error: File '" << filename << "' does not exist or cannot be opened. Please try again." << endl;
        }
    } while (!file);

    file.close();
    return filename;
}

//Counting the lines of the file so that I can allocate a proper size for the table.
int countLinesInFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for reading." << endl;
        return -1;
    }

    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            lineCount++;
        }
    }

    file.close();
    return lineCount;
}

//Displaying Menu
void displayMenu() {
    cout << "\nMenu Options:" << endl;
    cout << "1) Read from lotsofdogs" << endl;
    cout << "2) Load your own file" << endl;
    cout << "3) Insert a new dog" << endl;
    cout << "4) Search for a dog" << endl;
    cout << "5) Delete a dog" << endl;
    cout << "6) Print Collisions" << endl;
    cout << "7) Print dogs" << endl;
    cout << "8) Print dogs to file" << endl;
    cout << "9) Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    HashTable* table = nullptr;
    bool finished = false;

    while (!finished) {
        displayMenu();

        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cout << "Invalid choice, please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                delete table;
                table = new HashTable(250000);
                table->read_file("real_dogs.txt");
                break;
            }
            case 2: {
                string filename = getValidFilename();
                int size = countLinesInFile(filename);
                delete table;
                table = new HashTable(size);
                table->read_file(filename);
                break;
            }
            case 3: {
                if (!table) {
                    cout << "Please load a file first." << endl;
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string name;
                cout << "Enter dog name to insert: ";
                getline(cin, name);
                cout << "Name entered: " << name << endl;

                string breed;
                cout << "Enter dog breed: ";
                getline(cin, breed);
                cout << "Breed entered: " << breed << endl;

                float age;
                cout << "Enter dog age: ";
                cin >> age;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Age entered: " << age << endl;

                int size;
                cout << "Enter dog size: ";
                cin >> size;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Size entered: " << size << endl;

                int energy;
                cout << "Enter dog energy level: ";
                cin >> energy;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Energy level entered: " << energy << endl;

                DogNode* newDog = new DogNode(name, age, breed, size, energy);
                if (table->Insert(newDog)) {
                    cout << "Dog inserted successfully." << endl;
                } else {
                    cout << "Failed to insert dog." << endl;
                    delete newDog;
                }
                break;
            }
            case 4: {
                if (!table) {
                    cout << "Please load a file first." << endl;
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string name;
                cout << "Enter dog name to search: ";
                getline(cin, name);
                cout << "Name entered: " << name << endl;

                string breed;
                cout << "Enter dog breed to search: ";
                getline(cin, breed);
                cout << "Breed entered: " << breed << endl;

                cout << "Attempting to search for " << name << " (" << breed << ")" << endl;

                if (table->Search(breed, name)) {
                    cout << "Found dog: " << name << " (" << breed << ")" << endl;
                } else {
                    cout << "Dog not found." << endl;
                }
                break;
            }
            case 5: {
                if (!table) {
                    cout << "Please load a file first." << endl;
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string name;
                cout << "Enter dog name to delete: ";
                getline(cin, name);
                cout << "Name entered: " << name << endl;

                string breed;
                cout << "Enter dog breed to delete: ";
                getline(cin, breed);
                cout << "Breed entered: " << breed << endl;

                cout << "Attempting to delete " << name << " (" << breed << ")" << endl;

                if (table->Delete(name, breed)) {
                    cout << "Dog deleted successfully." << endl;
                } else {
                    cout << "Dog not found or could not be deleted." << endl;
                }
                break;
            }
            case 6:
                if (!table) {
                    cout << "Please load a file first." << endl;
                    break;
                }
                table->print_collision();
                break;
            case 7:
                if (!table) {
                    cout << "Please load a file first." << endl;
                    break;
                }
                table->Print();
                break;
            case 8:
                if (!table) {
                    cout << "Please load a file first." << endl;
                    break;
                }
                table->print_to_file();
                break;
            case 9:
                finished = true;
                break;
        }
    }

    //Not deleting table because my destructor does it automatically now.
    cout << "Thank you for using the program. Goodbye!" << endl;
    return 0;
}

