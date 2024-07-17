#include "HashTable.h"
#include "LinkedList.h"
//-----------------------------------------------------------
// Constructor
//-----------------------------------------------------------
HashTable::HashTable(int size)
{
    //Multiplying by 4 to hopefully have less collisions.
    Size = size * 4;
    table = new LinkedList[Size];

    collision_counter = 0;
}

//-----------------------------------------------------------
// Copy constructor
//-----------------------------------------------------------
HashTable::HashTable(const HashTable & ht)
{
    Size = ht.Size;
    table = new LinkedList[Size];

    for (int index = 0; index < Size; index++)
    {
        table[index] = ht.table[index];
    }
    collision_counter = ht.collision_counter;
}

//-----------------------------------------------------------
// Destructor
//-----------------------------------------------------------
HashTable::~HashTable()
{
    cout << "Destructor called" << endl;
    for (int i = 0; i < Size; i++) {
        DogNode* current = table[i].getHead();
        while (current) {
            DogNode* temp = current;
            current = current->getNext();
            delete temp;
        }
    }
    delete[] table;
    cout << "Destructor completed" << endl;
}

//-----------------------------------------------------------
// Insert method
//-----------------------------------------------------------
bool HashTable::Insert(DogNode *dog)
{
    // Find desired key
    size_t index = Hash(dog->getKey());
    if(!table[index].isEmpty()) {
        collision_counter++;
    }

    table[index].insertSorted(dog);
    return true;
}

//-----------------------------------------------------------
// Search method
//-----------------------------------------------------------
bool HashTable::Search(string breed, string name) {
    cout << "Entering Search function" << endl;
    // I search by name and breed as my key.
    string key = name + breed;
    cout << "Search key: " << key << endl;
    //This should give me the exact index. I use size_t because if I get a non-ascii character I was recieving
    //negative numbers. With size_t I can avoid negative numbers.
    size_t index = Hash(key);
    cout << "Searching at index: " << index << endl;

    DogNode* node = table[index].getHead();
    while (node != nullptr) {
        cout << "Checking node: " << node->getName() << " (" << node->getBreed() << ")" << endl;
        if (node->getBreed() == breed && node->getName() == name) {
            cout << "Dog found!" << endl;
            return true;
        }
        node = node->getNext();
    }
    cout << "Dog not found" << endl;
    return false;
}

//-----------------------------------------------------------
// Delete method
//-----------------------------------------------------------
bool HashTable::Delete(string name, string breed)
{
    // Finds key, should be exactly the same place, just like the search function.
    size_t index = Hash(name + breed);
    DogNode* node = table[index].getHead();

    while(node != nullptr) {
        if(node->getBreed() == breed) {
            if(node->getName() == name) {
                table[index].deleteNode(node);
                return true;
            } else {
                node = node->getNext();
            }
        } else {
            node = node->getNext();
        }
    }
    return false;
}

//-----------------------------------------------------------
// Primary hash function
//-----------------------------------------------------------
size_t HashTable::Hash(string key)
{
    size_t num = 42;
    for (int i = 0; i < int(key.length()); i++)
        num = (num * 17 + key[i]) % Size;
    cout << "Hashing key: " << key << ", result: " << num << endl;
    return num;
}

//-----------------------------------------------------------
// Secondary hash function
//-----------------------------------------------------------
size_t HashTable::Hash2(string key)
{
    size_t num = 63;
    for (int i = 0; i < int(key.length()); i++)
        num = (num * 17 + key[i]) % Size;
    cout << "Hashing key: " << key << ", result: " << num << endl;
    return num;
}

size_t HashTable::Hash3(string key)
{
    size_t num = 57;
    for (int i = 0; i < int(key.length()); i++)
        num = (num * 17 + key[i]) % Size;
    cout << "Hashing key: " << key << ", result: " << num << endl;
    return num;
}

//-----------------------------------------------------------
// Print function for debugging
//-----------------------------------------------------------
void HashTable::Print()
{
    for (int index = 0; index < Size; index++) {
        if (!table[index].isEmpty()) {
            table[index].printList();
        }
        cout << endl;
    }
}

void HashTable::print_collision() {
    cout << "Number of collisions: " << collision_counter << endl;
}

void HashTable::read_file(string filename) {
    ifstream infile;
    infile.open(filename);
    int i = 0;
    string read_name, read_age, read_breed, read_sizeInPounds, read_amountOfEnergy;
    while(!infile.eof()) {
        getline(infile, read_name, ',');
        getline(infile, read_age, ',');
        getline(infile, read_breed, ',');
        getline(infile, read_sizeInPounds, ',');
        getline(infile, read_amountOfEnergy, '\n');
        i++;
        try {
            DogNode *node = new DogNode;
            node->setName(read_name);
            node->setAge(stof(read_age));
            node->setBreed(read_breed);
            node->setSize(stoi(read_sizeInPounds));
            node->setEnergy(stoi(read_amountOfEnergy));
            node->setKey();
            Insert(node);
            cout << "Insert " << i << " " << node->getName() << " with key " << node->getKey() << " and collision count is: " << collision_counter << endl;
        }
        catch(exception e) {
            cout << "Error on line " << i << ": " << e.what() << endl;
            cout << "Data: " << read_name << "," << read_age << "," << read_breed << "," << read_sizeInPounds << "," << read_amountOfEnergy << endl;
        }

    }
    infile.close();
}

void HashTable::print_to_file() {
    string filename = "hashtable.txt";
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << " for writing." << endl;
        return;
    }

    for (int i = 0; i < Size; i++) {
        if (!table[i].isEmpty()) {
            outFile << "Bucket " << i << ": ";
            DogNode* current = table[i].getHead();
            while (current) {
                outFile << current->getName() << " (" << current->getBreed() << ") -> ";
                current = current->getNext();
            }
            outFile << "nullptr" << endl;
        }
    }

    outFile << "Total collisions: " << collision_counter << endl;
    outFile.close();

    cout << "Hash table has been written to " << filename << endl;
}
