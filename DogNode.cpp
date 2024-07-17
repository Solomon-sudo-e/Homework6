//
// Created by Solomon's PC on 7/12/2024.
//

#include "DogNode.h"
DogNode::DogNode(): name("na"), age(0), breed("na"), size(0), amount_of_energy(0), key("na"), next(nullptr), previous(nullptr) {}

DogNode::DogNode(const string &nname, const double &nage, const string &nbreed, const double &nsize, const double &namount_of_energy)
    : name(nname), age(nage), breed(nbreed), size(nsize), amount_of_energy(namount_of_energy), key(name+breed), next(nullptr), previous(nullptr) {}
DogNode::~DogNode() {
}
DogNode* DogNode::getNext() {
    return next;
}
DogNode* DogNode::getPrevious() {
    return previous;
}
string DogNode::getName() {
    return name;
}
float DogNode::getAge() {
    return age;
}
string DogNode::getBreed() {
    return breed;
}
int DogNode::getSize() {
    return size;
}
int DogNode::getEnergy() {
    return amount_of_energy;
}

string DogNode::getKey() {
    return key;
}
void DogNode::setNext(DogNode *new_next) {
    next = new_next;
}
void DogNode::setPrevious(DogNode *new_previous) {
    previous = new_previous;
}
void DogNode::setName(string nname) {
    name = nname;
}
void DogNode::setAge(float nage) {
    age = nage;
}
void DogNode::setBreed(string nbreed) {
    breed = nbreed;
}
void DogNode::setSize(int nsize) {
    size = nsize;
}
void DogNode::setEnergy(int nenergy) {
    amount_of_energy = nenergy;
}

//Most important method for my nodes. I call this anytime I make a new node to generate a key.
void DogNode::setKey() {
    key = name + breed;
}

