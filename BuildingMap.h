//
// Created by Simay Uygur- 22203328- section1
//

#ifndef HW4_BUILDINGMAP_H
#define HW4_BUILDINGMAP_H

#include <string>
#include "Cubicle.h"



using namespace std;

class BuildingMap {
public:
    BuildingMap(const string buildingMapFile);
    ~BuildingMap();

    void displayAllCubicles() const;
    void displayAdjacentCubicles(const int row, const int col) const;
    void displayBuildingMap() const;
    void findPaths(const int startRow, const int startCol, const int endRow, const int endCol);
    void findPaths(const int startRow, const int startCol, const int endRow, const int endCol,
                   const int avoidRow, const int avoidCol);


    //my methods
    int getNumberOfCubicles() const;

private:
    Cubicle** allCubicles;

    int rows;
    int columns;

    int numberOfCubicles;



    void clearAllVisitedFlags();
};


#endif //HW4_BUILDINGMAP_H
