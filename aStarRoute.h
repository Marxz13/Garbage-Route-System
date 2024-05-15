#ifndef ASTARROUTE_H_INCLUDED
#define ASTARROUTE_H_INCLUDED

#include <vector>
#include <queue>
#include <cmath>

#include "garbageLocation.h"

class AStarRoute {
public:
    struct Node {
        int index;
        float gCost; // Cost from start to current node
        float fCost; // Total cost of node (gCost + hCost)

        bool operator>(const Node& other) const;
    };

    static std::vector<int> aStar(int startIdx, int goalIdx, const std::vector<garbageLocation>& locations);
    static void generateRoutes(const std::vector<garbageLocation>& locations, float maxTotalDistance);
    static float heuristic(int from, int to);
    static float pathDistance(const std::vector<int>& path, const std::vector<garbageLocation>& locations);

private:
    static float calculateDistance(int from, int to, const std::vector<garbageLocation>& locations);
};

#endif // ASTARROUTE_H_INCLUDED
