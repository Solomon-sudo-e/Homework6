//
// Created by Solomon's PC on 7/12/2024.
//
#include "DogNode.h"
#include <string>
#include <iostream>
#ifndef DOGS_DOUBLY_LINKED_LIST_H
#define DOGS_DOUBLY_LINKED_LIST_H

using namespace std;
class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList &copy_list);
    ~LinkedList();
    bool isEmpty();
    DogNode *getHead();
    DogNode *copyNodes(DogNode* copied_node);
    void insertSorted(DogNode *sort_node);
    void deleteNode(DogNode* node);
    void setHead(DogNode *head_node);
    void printList();
private:
    DogNode *head;
    DogNode *tail;
};


#endif //DOGS_DOUBLY_LINKED_LIST_H
