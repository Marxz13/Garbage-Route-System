#include "AStarRoute.h"
#include "routeCost.h"
#include <algorithm>
#include <iostream>
#include <cfloat>
#include <unordered_set>

bool AStarRoute::Node::operator>(const Node& other) const {
    return this->fCost > other.fCost;
}

float AStarRoute::heuristic(int from, int to) {
    return std::abs(from - to);
}
float AStarRoute::pathDistance(const std::vector<int>& path, const std::vector<garbageLocation>& locations) {
    float totalDistance = 0.0;
    for (size_t i = 1; i < path.size(); i++) {
        totalDistance += garbageLocation::calculateDistance(path[i-1], path[i]);
    }
    return totalDistance;
}
std::vector<int> AStarRoute::aStar(int startIdx, int goalIdx, const std::vector<garbageLocation>& locations) {
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> openSet;
    std::vector<float> gCosts(locations.size(), FLT_MAX);
    std::vector<int> cameFrom(locations.size(), -1);
    std::vector<bool> closedSet(locations.size(), false);

    gCosts[startIdx] = 0;
    openSet.push({startIdx, 0, heuristic(startIdx, goalIdx)});

    while (!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if (current.index == goalIdx) {
            std::vector<int> path;
            for (int at = goalIdx; at != startIdx; at = cameFrom[at]) {
                path.push_back(at);
            }
            path.push_back(startIdx);
            std::reverse(path.begin(), path.end());
            return path;
        }

        closedSet[current.index] = true;

        for (int i = 0; i < locations.size(); i++) {
            if (closedSet[i] || garbageLocation::calculateDistance(current.index, i) == INF) continue;

            float tentativeGCost = current.gCost + garbageLocation::calculateDistance(current.index, i);
            if (tentativeGCost >= gCosts[i]) continue;

            cameFrom[i] = current.index;
            gCosts[i] = tentativeGCost;
            float fCost = tentativeGCost + heuristic(i, goalIdx);
            openSet.push({i, tentativeGCost, fCost});
        }
    }

    return {}; // return empty path if no path is found
}

void AStarRoute::generateRoutes(const std::vector<garbageLocation>& locations, float maxTotalDistance) {
    std::ofstream outFile("AStarRoute.txt", std::ios::app);  // File to write the routes and costs

    std::vector<int> eligibleLocations;
    const int startIdx = 0; // Assuming 'S' is always at index 0
    routeCost::RouteCost costs; // Create an instance of RouteCost to track the costs

    // Identify eligible locations
    for (int i = 1; i < locations.size(); i++) {
        if (locations[i].wasteLevel > 50) {
            eligibleLocations.push_back(i);
        }
    }

    // Attempt to create a path that visits all eligible locations
    std::vector<int> tour;
    std::unordered_set<int> visited;
    float currentDistance = 0;
    int currentLocation = startIdx;

    while (!eligibleLocations.empty()) {
        float minDistance = FLT_MAX;
        int nextLocation = -1;
        std::vector<int> path;

        // Find the nearest unvisited eligible location using a modified A* that considers already visited nodes
        for (int loc : eligibleLocations) {
            std::vector<int> tempPath = AStarRoute::aStar(currentLocation, loc, locations);
            float pathDistance = AStarRoute::pathDistance(tempPath, locations);
            if (pathDistance < minDistance && currentDistance + pathDistance < maxTotalDistance) {
                minDistance = pathDistance;
                nextLocation = loc;
                path = tempPath;
            }
        }

        if (nextLocation == -1) break; // No feasible path found within distance constraints

        // Add path to tour and update costs
        if (tour.empty()) {
            tour = path;
        } else {
            path.erase(path.begin()); // Remove the duplicate start node
            tour.insert(tour.end(), path.begin(), path.end());
        }

        // Update the current location, distance, and costs
        currentLocation = nextLocation;
        currentDistance += minDistance;
        costs.updateCosts(minDistance);
        visited.insert(nextLocation);
        costs.setSegmentDistance(currentDistance);
        eligibleLocations.erase(std::remove(eligibleLocations.begin(), eligibleLocations.end(), nextLocation), eligibleLocations.end());
    }

    // Add return to start if possible and update costs
    std::vector<int> returnPath = AStarRoute::aStar(currentLocation, startIdx, locations);
    float returnDistance = AStarRoute::pathDistance(returnPath, locations);
    if (currentDistance + returnDistance <= maxTotalDistance) {
        returnPath.erase(returnPath.begin()); // Remove the duplicate start node
        tour.insert(tour.end(), returnPath.begin(), returnPath.end());
        currentDistance += returnDistance;
        costs.updateCosts(returnDistance);
    } else {
        outFile << "Cannot return to start within distance limit." << std::endl;
        std::cout << "Cannot return to start within distance limit." << std::endl;
    }

    // Write and print the route information
    outFile << "--->50%---|" << "A* Route" << "|---" << maxTotalDistance << "Km---" << std::endl;
    outFile << "Route: ";
    std::cout << "--->50%---|" << "A* Route" << "|---" << maxTotalDistance << "Km---" << std::endl;
    std::cout << "Route: ";
    for (int i = 0; i < tour.size(); i++) {
        if (i > 0) {
            outFile << " -> ";
            std::cout << " -> ";
        }
        outFile << locations[tour[i]].garbageLocation_name;
        std::cout << locations[tour[i]].garbageLocation_name;
    }
    outFile << std::endl;
    std::cout << std::endl;

    // Print the total costs for the route
    costs.printCosts( outFile);
    outFile.close();  // Close the file after writing all details
}
