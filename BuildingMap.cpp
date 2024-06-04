//
// Created by Simay Uygur- 22203328- section1
//

#include "BuildingMap.h"
#include <fstream>
#include <iostream>

#include "StackLinked.h"
//node ve storage arrayi silmem laızm
//apthnode falan onları da siliyorum


using namespace std;

BuildingMap::~BuildingMap() {


    for(int s=0; s<numberOfCubicles; s++)
    {
        delete allCubicles[s];
    }
    delete[] allCubicles;   // önemli


}

BuildingMap::BuildingMap(const string buildingMapFile) {

    ifstream inputFile(buildingMapFile);   //bunu yazmadan almadı korkunç    tüm path

    int row, column;
    string currentCubicleType;
    string line;

    inputFile >> row >> column ;

    numberOfCubicles = row * column;

    allCubicles = new Cubicle* [numberOfCubicles];

    rows = row;
    columns = column;

    for (int i=0; i< row; ++i){
        inputFile >> line;

        for (int j=0  ; j <column ; ++j){
            currentCubicleType = line.at(j);
            int currentCoordinate = i * column + j;    //bunu düşünmemiştim

            if(i ==0 && j == column-1){
                allCubicles[currentCoordinate] = new Cubicle(Cubicle::CubeType(Cubicle::TOP_RIGHT_CORNER), stoi(currentCubicleType), i, j );
                //top right corner olsun (gerek var mı buna   şimdilik kalsın olmadı silerim
            }
            else if(i == 0){
                allCubicles[currentCoordinate] = new Cubicle(Cubicle::CubeType(Cubicle::TOP_ROW), stoi(currentCubicleType), i, j );
            }
            else if(j == column-1)
            {
                allCubicles[currentCoordinate] = new Cubicle(Cubicle::CubeType(Cubicle::LAST_COLUMN), stoi(currentCubicleType), i, j );
            }
            else
            {
                allCubicles[currentCoordinate] = new Cubicle(Cubicle::CubeType(Cubicle::ORDINARY), stoi(currentCubicleType), i, j );
            }

        }
    }

    Cubicle * curr = nullptr;
    Cubicle* adding = nullptr;


    for (int s = 0; s< numberOfCubicles; ++s)
    {
        curr = allCubicles[s];

        if(curr->getCubeType() == Cubicle::TOP_RIGHT_CORNER){  //unnecessary gibiymiş biraz
            //do nothing
        }
        else{
            if(curr->getCubeType() != Cubicle::LAST_COLUMN   ) // right left için
            {
                if(allCubicles[s+1]->getWallType() %2 == 0)
                {
                    adding = allCubicles[s+1];
                    curr ->addAdjacentToCubicle(adding,1); //righta ekledi yanındakinin sol duvarı yoksa
                    adding ->addAdjacentToCubicle(curr, 3) ; // leftine ekliyorum
                }

            }
            if(curr->getCubeType() != Cubicle::TOP_ROW )  // bottomlar 0 ve 1'de uok
            {

                if( allCubicles[s- column] ->getWallType() <2 ){
                    adding = allCubicles[s- column];
                    curr->addAdjacentToCubicle(adding, 0); // topa ekleyecek
                    adding->addAdjacentToCubicle(curr, 2);  //bottoma ekleyecek
                }
            }
        }
    }

    cout << rows << " rows and " << columns <<" columns have been read." << endl;
    inputFile.close();




}

void BuildingMap::displayAllCubicles() const {

    cout << "The cubicles in the building are:" ;

    Cubicle* curr = nullptr;
    for(int k=0; k< numberOfCubicles; ++k){
        curr = allCubicles[k];

        if( k % columns == 0)
            cout << endl;
        else
            cout << ",";
        cout << curr -> toString();
    }
    cout << endl;


}

void BuildingMap::displayAdjacentCubicles(const int row, const int col) const {
    int index = row * columns + col;
    Cubicle* cur = allCubicles[index];

    cout << "The cubicles adjacent to "<< cur->toString()  << " are:" << endl;

    cout <<  cur->toString() << " -> " ;

    if(cur-> getAdjacentListSize() == 0)
    {
        cout << endl;
        return;
    }
    int count = 0, curSize = cur->getAdjacentListSize();

    if(cur->getTop() != nullptr){
         cout <<  cur->getTop()->toString();
         count++;
         if(count < curSize){
             cout << "," ;
         }
    }
    if(cur->getLeft() != nullptr){
       cout <<cur->getLeft()->toString();
        count++;
        if(count < curSize){
            cout << "," ;
        }
    }
    if(cur->getRight() != nullptr){
        cout <<cur->getRight()->toString();
        count++;
        if(count < curSize){
            cout << "," ;
        }
    }
    if(cur->getBottom() != nullptr){
         cout <<  cur->getBottom()->toString();
    }

    cout << endl;

}

void BuildingMap::displayBuildingMap() const {
    cout << "The building map is as follows:" << endl;
    Cubicle* cur = nullptr;

    for(int i = 0; i < numberOfCubicles; i++)
    {
        cur = allCubicles[i];
        cout <<  cur->toString() << " -> " ;
        int count = 0, curSize = cur->getAdjacentListSize();

        if(cur->getTop() != nullptr){
            cout <<  cur->getTop()->toString();
            count++;
            if(count < curSize){
                cout << "," ;
            }
        }
        if(cur->getLeft() != nullptr){
            cout <<cur->getLeft()->toString();
            count++;
            if(count < curSize){
                cout << "," ;
            }
        }
        if(cur->getRight() != nullptr){
            cout <<cur->getRight()->toString();
            count++;
            if(count < curSize){
                cout << "," ;
            }
        }
        if(cur->getBottom() != nullptr){
            cout <<  cur->getBottom()->toString();
            count++;
        }
        cout << endl;
    }
    /*
    for(int i=0; i<rows; i++){
        for(int y=0; y< columns ; y++)
        {
            displayAdjacentCubicles(i,y);   // çok kolaymış
        }
    }
    */
}

void BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol) {

    StackLinked* stack = new StackLinked();
    int currIndex = startRow * columns + startCol;
    stack->push(allCubicles[currIndex]);

    int numPaths = 0;
    Cubicle* curCubicle = nullptr;
    clearAllVisitedFlags();  //unutma    bi tekrar bak

    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow << "," <<  endCol << ") are:" << endl;

    while (!stack->empty())
    {
        curCubicle = stack->top();
        curCubicle->markAsVisited();

        if(curCubicle -> getRow() == endRow && curCubicle -> getColumn() == endCol ){

            curCubicle->markUnvisited();

            stack->reverseStack();
            stack->display();
            stack->reverseStack();

            stack->pop();
            numPaths++;

        }
        else if( (curCubicle->visitedRight() || curCubicle->isHasVisitedRight()) && (curCubicle->visitedLeft() || curCubicle->isHasVisitedLeft()) && (curCubicle->visitedUp() || curCubicle->isHasVisitedTop())&& (curCubicle->visitedDown() || curCubicle->isHasVisitedBottom()))
        {

            curCubicle->markUnvisited();  // gerekli mi bilmiyorum

            curCubicle->setHasVisitedBottom(false);
            curCubicle->setHasVisitedLeft(false);
            curCubicle->setHasVisitedRight(false);
            curCubicle->setHasVisitedTop(false);

            stack->pop();
        }
        else
        {
            if(curCubicle->canVisitTop() && !curCubicle->isHasVisitedTop() && !curCubicle->visitedUp())
            {
                stack->push(curCubicle->getTop());
                curCubicle->setHasVisitedTop(true);
                curCubicle->getTop()->setHasVisitedBottom(true);
            }
            else if(curCubicle->canVisitLeft() && !curCubicle->isHasVisitedLeft() && !curCubicle->visitedLeft())
            {
                stack->push(curCubicle->getLeft());
                curCubicle->setHasVisitedLeft(true);
                curCubicle->getLeft()->setHasVisitedRight(true);
            }
            else if(curCubicle->canVisitRight() && !curCubicle->isHasVisitedRight() && !curCubicle->visitedRight())
            {
                stack->push(curCubicle->getRight());
                curCubicle->setHasVisitedRight(true);
                curCubicle->getRight()->setHasVisitedLeft(true);
            }
            else if(curCubicle->canVisitBottom() && !curCubicle->isHasVisitedBottom() && !curCubicle->visitedDown())
            {
                stack->push(curCubicle->getBottom());
                curCubicle->setHasVisitedBottom(true);
                curCubicle->getBottom()->setHasVisitedTop(true);
            }
            else
            {
                curCubicle->markUnvisited();
                if(curCubicle->getRight())
                    curCubicle->getRight()->markUnvisited();

                if(curCubicle->getLeft())
                    curCubicle->getLeft()->markUnvisited();

                if(curCubicle->getTop())
                    curCubicle->getTop()->markUnvisited();

                if(curCubicle->getBottom())
                    curCubicle->getBottom()->markUnvisited();

                curCubicle->setHasVisitedBottom(false);
                curCubicle->setHasVisitedLeft(false);
                curCubicle->setHasVisitedRight(false);
                curCubicle->setHasVisitedTop(false);

                stack-> pop();

            }
        }
    }

    if(numPaths == 0)
        cout << "None" << endl;

    delete stack;
}



void
BuildingMap::findPaths(const int startRow, const int startCol, const int endRow, const int endCol, const int avoidRow,
                       const int avoidCol) {


    StackLinked* stack = new StackLinked();
    int currIndex = startRow * columns + startCol;
    stack->push(allCubicles[currIndex]);

    int numPaths = 0;
    Cubicle* curCubicle = nullptr;
    clearAllVisitedFlags();

    cout << "Paths from (" << startRow << "," << startCol << ") to (" << endRow
    << "," <<  endCol << ") "<< "avoiding "<< "(" << avoidRow << "," << avoidCol
    << ")"<<" are:"<< endl;

    while (!stack->empty())
    {
        curCubicle = stack->top();
        curCubicle->markAsVisited();

        if(curCubicle -> getRow() == endRow && curCubicle -> getColumn() == endCol ){

            curCubicle->markUnvisited();

            stack->reverseStack();
            stack->display();
            stack->reverseStack();

            stack->pop();
            numPaths++;

        }
        else if( (curCubicle->visitedRight() || curCubicle->isHasVisitedRight()) && (curCubicle->visitedLeft() || curCubicle->isHasVisitedLeft()) && (curCubicle->visitedUp() || curCubicle->isHasVisitedTop())&& (curCubicle->visitedDown() || curCubicle->isHasVisitedBottom()))
        {

            curCubicle->markUnvisited();  // gerekli mi bilmiyorum


            curCubicle->setHasVisitedBottom(false);
            curCubicle->setHasVisitedLeft(false);
            curCubicle->setHasVisitedRight(false);
            curCubicle->setHasVisitedTop(false);

            stack->pop();
        }
        else
        {
            if(curCubicle->canVisitTop() && !curCubicle->isHasVisitedTop() && !curCubicle->visitedUp() && !curCubicle->isAvoidedCubicle(avoidRow,avoidCol,0) )
            {
                stack->push(curCubicle->getTop());
                curCubicle->setHasVisitedTop(true);
                curCubicle->getTop()->setHasVisitedBottom(true);
            }
            else if(curCubicle->canVisitLeft() && !curCubicle->isHasVisitedLeft() && !curCubicle->visitedLeft() && !curCubicle->isAvoidedCubicle(avoidRow,avoidCol,2) )
            {
                stack->push(curCubicle->getLeft());
                curCubicle->setHasVisitedLeft(true);
                curCubicle->getLeft()->setHasVisitedRight(true);
            }
            else if(curCubicle->canVisitRight() && !curCubicle->isHasVisitedRight() && !curCubicle->visitedRight() && !curCubicle->isAvoidedCubicle(avoidRow,avoidCol,3) )
            {
                stack->push(curCubicle->getRight());
                curCubicle->setHasVisitedRight(true);
                curCubicle->getRight()->setHasVisitedLeft(true);
            }
            else if(curCubicle->canVisitBottom() && !curCubicle->isHasVisitedBottom() && !curCubicle->visitedDown() && !curCubicle->isAvoidedCubicle(avoidRow,avoidCol,1) )
            {
                stack->push(curCubicle->getBottom());
                curCubicle->setHasVisitedBottom(true);
                curCubicle->getBottom()->setHasVisitedTop(true);
            }
            else
            {
                curCubicle->markUnvisited();
                if(curCubicle->getRight())
                    curCubicle->getRight()->markUnvisited();

                if(curCubicle->getLeft())
                    curCubicle->getLeft()->markUnvisited();

                if(curCubicle->getTop())
                    curCubicle->getTop()->markUnvisited();

                if(curCubicle->getBottom())
                    curCubicle->getBottom()->markUnvisited();

                curCubicle->setHasVisitedBottom(false);
                curCubicle->setHasVisitedLeft(false);
                curCubicle->setHasVisitedRight(false);
                curCubicle->setHasVisitedTop(false);

                stack-> pop();

            }
        }
    }

    if(numPaths == 0)
        cout << "None" << endl;

    delete stack; // gerekli mi
}

int BuildingMap::getNumberOfCubicles() const {
    return numberOfCubicles;
}


void BuildingMap::clearAllVisitedFlags() {

    for(int i = 0; i< numberOfCubicles; i++)
    {
        allCubicles[i]->markUnvisited();
        allCubicles[i]->setHasVisitedTop(false);
        allCubicles[i]->setHasVisitedBottom(false);
        allCubicles[i]->setHasVisitedRight(false);
        allCubicles[i]->setHasVisitedLeft(false);
    }
}
