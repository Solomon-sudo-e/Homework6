//
// Created by Solomon's PC on 7/12/2024.
//

#include "LinkedList.h"
LinkedList::LinkedList(): head(nullptr), tail(nullptr) {}

LinkedList::LinkedList(const LinkedList &copy_list) {
    head = copyNodes(copy_list.head);
}


// Properly destroying linked list, this was my bane of a seg fault for over 45 mins...
LinkedList::~LinkedList() {
    DogNode* current = head;
    while (current) {
        DogNode* temp = current;
        current = current->getNext();
        delete temp;
    }
    head = tail = nullptr;
}

bool LinkedList::isEmpty() {
    return head == nullptr;
}

DogNode* LinkedList::getHead() {
    return head;
}

void LinkedList::setHead(DogNode* head_node) {
    head = head_node;
}

DogNode* LinkedList::copyNodes(DogNode *copied_node) {
    if(!copied_node) return nullptr;
    DogNode *copiedNode = new DogNode(
            copied_node->getName(), copied_node->getAge(),
            copied_node->getBreed(), copied_node->getSize(),
            copied_node->getEnergy());
    copiedNode->setNext(copyNodes(copied_node->getNext()));
    return copied_node;
}

void LinkedList::printList() {
    DogNode* current = head;
    while(current) {
        cout << current->getName() << ": " << current->getBreed() << " -> ";
        current = current->getNext();
    }
    cout << "nullptr" << endl;
}

int evaluate_score(string name) {
    //I made an array to compare each index, the lower the index the more priority I can give the name for alphabetical order
    char scores[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                       'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                       'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    //Making strings uppercase for more convenient comparisons
    for(int i = 0; i < name.size(); i++) {
        name[i] = toupper(name[i]);
    }
    for(int i = 0; i < 26; i++) {
        if(name[0] == scores[i]) {
            return i;
        }
    }
    cout << "Failed to find score" << endl;
    return -1;
}

void LinkedList::insertSorted(DogNode *sort_node) {
    cout << "Attempting to insert node: " << sort_node->getName() << endl;

    // Getting scores. Lower the score the more priority the DogNode gets.
    int score = evaluate_score(sort_node->getName());
    cout << "Score for " << sort_node->getName() << ": " << score << endl;

    if (!head) {
        // If the list is empty I set the new DogNode as head and tail
        head = tail = sort_node;
        cout << "Inserted as head and tail" << endl;
        return;
    }

    DogNode* current = head;
    int current_score = evaluate_score(current->getName());
    cout << "Current head: " << current->getName() << " with score: " << current_score << endl;

    // Iterate through and check scores
    while (current && score >= current_score) {
        cout << "Comparing with: " << current->getName() << " (score: " << current_score << ")" << endl;

        if (score > current_score) {
            current = current->getNext();
            if (current) {
                current_score = evaluate_score(current->getName());
            }
        } else {
            // Handle score equality by comparing each character after IF prior characters were equal.
            string name_update = sort_node->getName();
            string current_name_update = current->getName();

            int min_len = min(name_update.size(), current_name_update.size());
            bool exact_match = true;

            //Iterating through new strings to compare each name after removing first character.
            for (int i = 1; i < min_len; ++i) {
                char score_char = toupper(name_update[i]);
                char current_score_char = toupper(current_name_update[i]);

                if (score_char != current_score_char) {
                    score = evaluate_score(name_update.substr(i));
                    current_score = evaluate_score(current_name_update.substr(i));
                    exact_match = false;
                    break;
                }
            }
            // Make sure we break the tie and move forward
            if (exact_match) {
                score++;
            } else {
                if (score > current_score) {
                    current = current->getNext();
                    if (current) current_score = evaluate_score(current->getName());
                }
            }
        }
    }

    cout << "Insertion position found" << endl;

    // Insert the DogNode, since im using a doubly linked list I have to keep track of tail and head
    if (!current) {
        // Insert at the tail, !current means nullptr.
        tail->setNext(sort_node);
        sort_node->setPrevious(tail);
        tail = sort_node;
        cout << "Inserted at tail" << endl;
    } else if (current == head) {
        // Insert at the head, best case scenario
        sort_node->setNext(head);
        head->setPrevious(sort_node);
        head = sort_node;
        cout << "Inserted at head" << endl;
    } else {
        // Insert in the middle.
        DogNode* prev = current->getPrevious();
        prev->setNext(sort_node);
        sort_node->setPrevious(prev);
        sort_node->setNext(current);
        current->setPrevious(sort_node);
        cout << "Inserted in middle" << endl;
    }

    cout << "DogNode inserted successfully" << endl;
}

void LinkedList::deleteNode(DogNode* node) {
    if(node == head) {
        head = head->getNext();
        if(head) {
            head->setPrevious(nullptr);
        } else if(node == tail) {
            tail = tail->getPrevious();
            if(tail) {
                tail->setNext(nullptr);
            }
        } else {
            node->getPrevious()->setNext(node->getNext());
            node->getNext()->setPrevious(node->getPrevious());
        }
    }
}