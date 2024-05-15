#include "optimizedRoute.h"
#include "routeCost.h"
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

void OptimizedRoute::floydWarshall(float dist[][9], int next[][9]) {
    const int V = 9; // Number of vertices
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

void OptimizedRoute::printAndCalculatePath(int next[][9], int start, int end, const float dist[][9], routeCost::RouteCost& cost, std::ofstream& outFile) {
    if (next[start][end] == -1) {
        std::cout << " No path";
        outFile << " No path";
        return;
    }
    int u = start;
    std::cout << "S";
    outFile << "S";
    while (u != end) {
        int v = next[u][end];
        std::cout << " -> " << garbageLocation::indexToName(v);
        outFile << " -> " << garbageLocation::indexToName(v);
        cost.updateCosts(dist[u][v]);  // Update costs for this segment of the journey
        u = v;
    }
}

void OptimizedRoute::generatefloydWarshall(const std::vector<garbageLocation>& locations, const float dist[][9], int next[][9]) {
    std::ofstream outFile("FloydWarshallRoute.txt", std::ios::app);
    for (size_t i = 1; i < locations.size(); ++i) {
        if (locations[i].wasteLevel > 60 && dist[0][i] < 40) {  // Check waste level and distance criteria
            std::cout << "-------*" << "Location " << locations[i].garbageLocation_name << "*-------" << std::endl;
            outFile << "-------*" << "Location " << locations[i].garbageLocation_name << "*-------" << std::endl;

            // Initialize a new RouteCost object to track total costs for the round trip
            routeCost::RouteCost cost;

            // Specifically set the segment distance from S to the initial location
            cost.setSegmentDistance(dist[0][i]);

            // Calculate and print the path from S to location i
            std::cout << "Start: \n";
            outFile << "Start: \n";
            printAndCalculatePath(next, 0, i, dist, cost, outFile);
            std::cout << std::endl;
            outFile << std::endl;

            // Calculate and print the return path from location i to S
            std::cout << "Return\n";
            outFile << "Return\n";
            printAndCalculatePath(next, i, 0, dist, cost, outFile);
            std::cout << std::endl;
            outFile << std::endl;

            // Print the total costs after both trips are completed
            cost.printCosts(outFile);
            std::cout << "\n";
            outFile << "\n";
        }
    }
    outFile.close(); // Close the file after writing all details
}

