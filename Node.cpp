//
// Created by Simay Uygur- 22203328- section1
//

#include "Node.h"


Node::Node(Cubicle* el, Node* nex): element(el),  next(nex){}

Node::~Node(){
    element = nullptr;
    next = nullptr;
}

Cubicle *Node::getElement() const {
    return element;
}

Node *Node::getNext() const {
    return next;
}

void Node::setElement(Cubicle *element) {
    Node::element = element;
}

void Node::setNext(Node *next) {
    Node::next = next;
}


