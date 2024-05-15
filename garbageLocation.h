#ifndef GARBAGELOCATION_H_INCLUDED
#define GARBAGELOCATION_H_INCLUDED

#include <vector>
#include <string>
#define INF (std::numeric_limits<float>::max())
class garbageLocation
{
public:
    float wasteLevel;

    std::string garbageLocation_name;
    bool visited;
    int collectionHour;
    static const int numLocations = 9; // Including 'S'
    static float distanceMatrix[9][9]; // Declaration
    garbageLocation(std::string name); // Constructor declaration

    static void printGraph();
    bool isWithinMaxDistance(int from, float maxDistance)const;
    static std::vector<garbageLocation> initialize_garbageLocation_vector();
    static float trafficMultiplier();
    static void printWasteLevels(const std::vector<garbageLocation>& garbageLocations);
    static float calculateDistance(int from, int to);
    static std::string indexToName(int index);

    static void updateTrafficConditions(const std::vector<int>& locations);
    static std::vector<int>randomizeAffectedLocations(int numLocations, int totalLocations);
};

#endif // GARBAGELOCATION_H_INCLUDED
