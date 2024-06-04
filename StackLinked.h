//
// Created by Simay Uygur- 22203328- section1
//

#ifndef HW4_STACKLINKED_H
#define HW4_STACKLINKED_H

#include "Cubicle.h"
#include "Node.h"

class StackLinked{

public:
    StackLinked(Node *head = nullptr, int numElements = 0);
    virtual ~StackLinked();

    void push(Cubicle* cube);
    Cubicle* pop();
    Cubicle* top();
    int size();
    bool empty();
    void clear();
    StackLinked& operator=(const StackLinked& other) ;
    void display() const;

    void reverseStack();
private:
    Node* head;
    int numElements;
};

#endif //HW4_STACKLINKED_H
