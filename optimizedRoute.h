#ifndef OPTIMIZEDROUTE_H
#define OPTIMIZEDROUTE_H

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>
#include <algorithm>
#include "routeCost.h"
#include "garbageLocation.h"  // Assuming the garbageLocation class is defined in this or another file
#define INF (std::numeric_limits<float>::max())

class OptimizedRoute {
public:
    static void optimizedRoute();
    static void floydWarshall(float dist[][9], int next[][9]);
    static void printPath(int next[][9], int start, int end);
    static void generatefloydWarshall(const std::vector<garbageLocation>& locations, const float dist[][9], int next[][9]);
    static void printAndCalculatePath(int next[][9], int start, int end, const float dist[][9], routeCost::RouteCost& cost, std::ofstream& outFile) ;

};

#endif // OPTIMIZEDROUTE_H
