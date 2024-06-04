//
// Created by Simay Uygur- 22203328- section1
//

#ifndef HW4_CUBICLE_H
#define HW4_CUBICLE_H

#include <string>


class Cubicle
{
public:

    enum CubeType
    {
        TOP_ROW,
        LAST_COLUMN,
        TOP_RIGHT_CORNER,
        ORDINARY
    };


    Cubicle(CubeType cubeType = ORDINARY, int wallType = 0, int row = 0, int column = 0, bool visited = false, Cubicle *top = nullptr, Cubicle *right = nullptr,
            Cubicle *left = nullptr, Cubicle *bottom = nullptr, int adjacentListSize = 0, bool hasVisitedTop = false, bool hasVisitedBottom = false,
            bool hasVisitedRight = false, bool hasVisitedLeft = false);

    int getRow() const;
    int getWallType() const;
    CubeType getCubeType() const;
    virtual ~Cubicle();

    bool isHasVisitedTop() const;
    void setHasVisitedTop(bool hasVisitedTop);
    bool isHasVisitedBottom() const;
    void setHasVisitedBottom(bool hasVisitedBottom);
    bool isHasVisitedRight() const;
    void setHasVisitedRight(bool hasVisitedRight);
    bool isHasVisitedLeft() const;
    void setHasVisitedLeft(bool hasVisitedLeft);
    int getColumn() const;

    std::string toString();

    void addAdjacentToCubicle(Cubicle *cube, int top_right_bottom_left);

    void markAsVisited();
    void markUnvisited();
    bool isVisited() const;

    Cubicle *getTop() const;
    Cubicle *getRight() const;
    Cubicle *getLeft() const;
    Cubicle *getBottom() const;

    int getAdjacentListSize() const;

    bool canVisitTop() const;
    bool canVisitBottom() const;   //visited olup olmamasına bakmıyorlar
    bool canVisitRight() const;
    bool canVisitLeft() const;

    bool visitedRight();
    bool visitedLeft();
    bool visitedUp();
    bool visitedDown();

    bool isAvoidedCubicle(int row, int column , int direction);

private:
    CubeType cubeType;
    int wallType;

    int row;
    int column;

    bool visited;

    Cubicle* top;
    Cubicle* right;
    Cubicle* left;
    Cubicle* bottom;

    int adjacentListSize;

    bool hasVisitedTop;
    bool hasVisitedBottom;
    bool hasVisitedRight;
    bool hasVisitedLeft;


};


#endif //HW4_CUBICLE_H

