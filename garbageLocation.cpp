#include "garbageLocation.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <limits>
#include <vector>
#include <ctime>
#include <random>


#define INF (std::numeric_limits<float>::max())
#include <numeric>

void garbageLocation::printGraph() {
    std::string line1  = "S-----5-----A---8---B ";
    std::string line2  = "|           |      /| ";
    std::string line3  = "|           |     / 6 ";
    std::string line4  = "|           |    /  | ";
    std::string line5  = "5           6   4   G ";
    std::string line6  = "|           |  /   /  ";
    std::string line7  = "|           | /   /   ";
    std::string line8  = "|           |/   /    ";
    std::string line9  = "D-->2-E->2--C   9     ";
    std::string line10 = "^           |  /      ";
    std::string line11 = "|           2 /       ";
    std::string line12 = "^           |/        ";
    std::string line13 = "6-<-<-<-<-<-F         ";

    // Print each line
    std::cout << line1 << std::endl;
    std::cout << line2 << std::endl;
    std::cout << line3 << std::endl;
    std::cout << line4 << std::endl;
    std::cout << line5 << std::endl;
    std::cout << line6 << std::endl;
    std::cout << line7 << std::endl;
    std::cout << line8 << std::endl;
    std::cout << line9 << std::endl;
    std::cout << line10 << std::endl;
    std::cout << line11 << std::endl;
    std::cout << line12 << std::endl;
    std::cout << line13 << std::endl<< std::endl;
}
garbageLocation::garbageLocation(std::string name) : garbageLocation_name(name) {
    // Implementation
    if (name == "S") {
        wasteLevel = 0;
    } else {
        wasteLevel = (std::round(rand() % 100));
    }
}

float garbageLocation::distanceMatrix[9][9] = {
    //S   A    B    C    D    E    F    G    H
    {0,   5,  INF, INF,  5 , INF, INF, INF, INF }, // S
    {5,   0,   8 ,  6 , INF, INF, INF, INF, INF }, // A
    {INF, 8,   0 ,  4 , INF, INF, INF,  6 , INF }, // B
    {INF, 6,   4 ,  0 , INF, INF,  2 , INF, INF }, // C
    {5 , INF, INF, INF,  0 ,  2,  INF, INF, INF }, // D
    {INF,INF, INF,  2,  INF,  0,  INF, INF, INF }, // E
    {INF,INF, INF,  2 ,  6,  INF,  0,  9 ,   4  }, // F
    {INF,INF,  6,  INF, INF, INF,  9,  0 ,  INF }, // G
    {INF,INF, INF, INF, INF, INF,  4, INF,   0  }, // H
};

std::vector<garbageLocation> garbageLocation::initialize_garbageLocation_vector() {
    srand(time(NULL)); // Initialize random seed
    std::vector<garbageLocation> garbageLocations;
    garbageLocations.push_back(garbageLocation("S")); // Assuming S is the station
    garbageLocations.push_back(garbageLocation("A"));
    garbageLocations.push_back(garbageLocation("B"));
    garbageLocations.push_back(garbageLocation("C"));
    garbageLocations.push_back(garbageLocation("D"));
    garbageLocations.push_back(garbageLocation("E"));
    garbageLocations.push_back(garbageLocation("F"));
    garbageLocations.push_back(garbageLocation("G"));

    return garbageLocations;
}
void garbageLocation::printWasteLevels(const std::vector<garbageLocation>& garbageLocations) {
    for (const auto& location : garbageLocations) {
        std::cout << "Location " << location.garbageLocation_name << " has garbage level: " << location.wasteLevel << std::endl;
    }
}
float garbageLocation::calculateDistance(int from, int to) {
    float baseDistance = garbageLocation::distanceMatrix[from][to];
    if (baseDistance == INF) return INF;
    return baseDistance;
}
// In garbageLocation.cpp or where you implement the methods
std::string garbageLocation::indexToName(int index) {
    static const std::string names[9] = {"S", "A", "B", "C", "D", "E", "F", "G", "H"};
    if (index >= 0 && index < 9) {
        return names[index];
    }
    return "Invalid index";
}

void garbageLocation::updateTrafficConditions(const std::vector<int>& locations) {
    float trafficMultiplier = 1.25f;
    for (int from : locations) {
        for (int to = 0; to < 9; ++to) {
            if (from != to && distanceMatrix[from][to] != INF) {
                distanceMatrix[from][to] *= trafficMultiplier;
            }
        }
    }
}
std::vector<int> garbageLocation::randomizeAffectedLocations(int numLocations, int totalLocations) {
    std::vector<int> locations(totalLocations);
    std::iota(locations.begin(), locations.end(), 0);

    std::random_device rd;
    std::mt19937 g(rd());

    for (int i = 0; i < numLocations; ++i) {
        std::uniform_int_distribution<> dis(i, totalLocations - 1);
        int j = dis(g);
        std::swap(locations[i], locations[j]);
    }

    locations.resize(numLocations);

    return locations;
}
