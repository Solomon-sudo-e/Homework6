//
// Created by Solomon's PC on 7/12/2024.
//

#ifndef DOGS_DOGNODE_H
#define DOGS_DOGNODE_H
#include <string>

using namespace std;
class DogNode {
public:
    DogNode();
    DogNode(const string &nname, const double &nage, const string &nbreed, const double &nsize, const double &namount_of_energy);
    ~DogNode();
    DogNode* getNext();
    DogNode* getPrevious();
    string getName();
    float getAge();
    string getBreed();
    int getSize();
    int getEnergy();
    string getKey();
    void setNext(DogNode *new_next);
    void setPrevious(DogNode *new_previous);
    void setName(string nname);
    void setAge(float nage);
    void setBreed(string nbreed);
    void setSize(int nsize);
    void setEnergy(int nenergy);
    void setKey();
private:
    string name;
    float age;
    string breed;
    int size;
    int amount_of_energy;
    string key = name + breed;
    DogNode* next;
    DogNode* previous;
};


#endif //DOGS_DOGNODE_H
