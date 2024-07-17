#ifndef HASH_H
#define HASH_H
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "LinkedList.h"
using namespace std;

//-----------------------------------------------------------
// Define the HashTable class interface
//-----------------------------------------------------------
class HashTable
{
public:
    // Constructors
    HashTable(int size);
    HashTable(const HashTable & ht);
    ~HashTable();

    // Methods
    bool Insert(DogNode *dog);
    bool Search(string name, string breed);
    bool Delete(string name, string breed);
    void Print();
    void Print(ofstream & dout);
    void print_collision();
    void read_file(string filename);
    void print_to_file();

private:
    // Private methods
    size_t Hash(string key);
    size_t Hash2(string key);
    size_t Hash3(string key);

    // Private data
    int Size;
    LinkedList *table;
    int collision_counter;
};

#endif