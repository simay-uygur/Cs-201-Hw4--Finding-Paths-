//
// Created by Simay Uygur- 22203328- section1
//

#include "Cubicle.h"


Cubicle::~Cubicle() {
    top = nullptr;
    right = nullptr;
    left = nullptr;
    bottom = nullptr;
    adjacentListSize = 0;

}

Cubicle::CubeType Cubicle::getCubeType() const {
    return cubeType;
}

int Cubicle::getWallType() const {
    return wallType;
}

int Cubicle::getRow() const {
    return row;
}

int Cubicle::getColumn() const {
    return column;
}

std::string Cubicle::toString() {
    return "(" + std::to_string(row) + "," + std::to_string(column) + ")";
}

void Cubicle::addAdjacentToCubicle( Cubicle *cube, int top_right_bottom_left) {

    if(top_right_bottom_left == 0 && top == nullptr)  //it is top
    {
        top = cube;
    }
    else if(top_right_bottom_left == 1 && right == nullptr){
        right = cube;
    }
    else if(top_right_bottom_left == 2 && bottom == nullptr)
    {
        bottom = cube;
    }
    else if (top_right_bottom_left == 3 && left == nullptr)
    {
        left = cube;
    }
    else {
        return;
    }
    adjacentListSize++;

}

void Cubicle::markAsVisited() {
    visited = true;
}

bool Cubicle::isVisited() const {
    return visited;
}

Cubicle *Cubicle::getTop() const {
    return top;
}

Cubicle *Cubicle::getRight() const {
    return right;
}

Cubicle *Cubicle::getLeft() const {
    return left;
}

Cubicle *Cubicle::getBottom() const {
    return bottom;
}

int Cubicle::getAdjacentListSize() const {
    return adjacentListSize;
}

bool Cubicle::canVisitTop() const {
    return top!= nullptr;
}

bool Cubicle::canVisitBottom() const {
    return bottom != nullptr;
}

bool Cubicle::canVisitRight() const {
    return right != nullptr;
}

bool Cubicle::canVisitLeft() const {
    return left != nullptr;
}

void Cubicle::markUnvisited() {
    visited = false;
}

bool Cubicle::isHasVisitedTop() const {
    return hasVisitedTop;
}

void Cubicle::setHasVisitedTop(bool hasVisitedTop) {
    Cubicle::hasVisitedTop = hasVisitedTop;
}

bool Cubicle::isHasVisitedBottom() const {
    return hasVisitedBottom;
}

void Cubicle::setHasVisitedBottom(bool hasVisitedBottom) {
    Cubicle::hasVisitedBottom = hasVisitedBottom;
}

bool Cubicle::isHasVisitedRight() const {
    return hasVisitedRight;
}

void Cubicle::setHasVisitedRight(bool hasVisitedRight) {
    Cubicle::hasVisitedRight = hasVisitedRight;
}

bool Cubicle::isHasVisitedLeft() const {
    return hasVisitedLeft;
}

void Cubicle::setHasVisitedLeft(bool hasVisitedLeft) {
    Cubicle::hasVisitedLeft = hasVisitedLeft;
}

bool Cubicle::visitedRight() {
    if (right== nullptr)
        return true;
    return right->isVisited();
}

bool Cubicle::visitedLeft() {
    if (left== nullptr)
        return true;
    return left->isVisited();
}

bool Cubicle::visitedUp() {
    if (top== nullptr)
        return true;
    return top->isVisited();
}

bool Cubicle::visitedDown() {
    if (bottom== nullptr)
        return true;
    return bottom->isVisited();
}

bool Cubicle::isAvoidedCubicle(int row, int column, int direction) {
    //0 : top olsun 1: bottom 2:left 3:right
    if(direction == 0)
    {
        if(top)
        {
            return top->getRow() == row && top->getColumn() == column;
        }
        return false;
    }
    else if(direction == 1)
    {
        if(bottom)
        {
            return bottom->getRow() == row && bottom->getColumn() == column;
        }
        return  false;
    }
    else if(direction == 2)
    {
        if(left)
        {
            return left->getRow() == row && left->getColumn() == column;
        }
        return false;
    }
    else if(direction == 3)
    {
        if(right)
        {
            return right->getRow() == row && right->getColumn() == column;
        }
        return false;
    }
    return false;

}

Cubicle::Cubicle(Cubicle::CubeType cubeType, int wallType, int row, int column, bool visited, Cubicle *top,
                 Cubicle *right, Cubicle *left, Cubicle *bottom, int adjacentListSize, bool hasVisitedTop,
                 bool hasVisitedBottom, bool hasVisitedRight, bool hasVisitedLeft) : cubeType(cubeType),
                                                                                     wallType(wallType), row(row),
                                                                                     column(column), visited(visited),
                                                                                     top(top), right(right), left(left),
                                                                                     bottom(bottom),
                                                                                     adjacentListSize(adjacentListSize),
                                                                                     hasVisitedTop(hasVisitedTop),
                                                                                     hasVisitedBottom(hasVisitedBottom),
                                                                                     hasVisitedRight(hasVisitedRight),
                                                                                     hasVisitedLeft(hasVisitedLeft) {}




