//
// Created by Simay Uygur- 22203328- section1
//

#ifndef HW4_NODE_H
#define HW4_NODE_H

#include "Cubicle.h"

class Node{
public:
    Node(Cubicle* el = nullptr, Node* nex = nullptr);
    ~Node();

    Cubicle *getElement() const;
    Node *getNext() const;
    void setElement(Cubicle *element);
    void setNext(Node *next);


private:
    Cubicle* element;
    Node* next;

};
#endif //HW4_NODE_H
