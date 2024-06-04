//
// Created by Simay Uygur- 22203328- section1
//

#include "StackLinked.h"
#include <iostream>

StackLinked::StackLinked(Node *head, int numElements) : head(head), numElements(numElements) {

}

StackLinked::~StackLinked() {
    // ya da clear metodunu çağırabilirim
    Node* cur = head;

    while(cur != nullptr)
    {
        Node* temp = cur;
        cur = cur -> getNext();
        delete temp;
    }

    //delete head; // gerek var mı bilmiyorum

    numElements = 0;
}

void StackLinked::push(Cubicle *cube) {

    Node* cur = new Node(cube);

    cur -> setNext(head);
    head = cur;
    numElements++;
}

Cubicle* StackLinked::pop() {
    if(empty())
    {
        return nullptr;
    }

    Node* removed = head;
    Cubicle* cub = removed -> getElement();

    head = head -> getNext();
    delete removed;
    numElements--;
    return cub;
}

int StackLinked::size() {
    return numElements;
}

bool StackLinked::empty() {
    return numElements == 0;
}

Cubicle* StackLinked::top() {
    return head -> getElement();
}

void StackLinked::clear() {
    while (!empty()) {
        pop();
    }
}

StackLinked& StackLinked::operator=(const StackLinked& other) {
    if (this != &other) {

        if (!empty()) {
            clear();
        }

        Node* otherNode = other.head;

        while (otherNode) {
            Cubicle* cub = otherNode->getElement();
            push(cub);

            otherNode = otherNode->getNext();
        }
    }
    return *this;
}


void StackLinked::display() const {
    Node* cur = head;
    while(cur->getNext() != nullptr) {
        std::cout << cur->getElement()->toString() << " -> ";
        cur = cur->getNext();
    }
    std::cout << cur->getElement()->toString()<< std::endl;
}

void StackLinked::reverseStack() {

    StackLinked* newStack = new StackLinked();
    StackLinked* similarOldStack = new StackLinked();

    while (!this->empty())
    {
        newStack->push(this->pop());
    }// num aynı kalacak

    while (!newStack->empty())
    {
        similarOldStack->push(newStack->pop());
    }
    while (!similarOldStack->empty())
    {
        this->push(similarOldStack->pop());
    }
    // oldu bence
    delete newStack;
    delete similarOldStack;

}
