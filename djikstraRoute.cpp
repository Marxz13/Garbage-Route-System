#include "garbageLocation.h"
#include "routeCost.h"
#include "djikstraRoute.h"
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <functional>
#include <algorithm>
#include <set>

#define INF (std::numeric_limits<float>::max())

// Generate djikstra Route
void DjikstraRoute::generateDijkstraRoute(const std::vector<garbageLocation>& locations, const std::vector<std::vector<std::pair<int, float>>>& graph) {
    int source = 0;  // Usually the central depot or main station

    for (size_t i = 1; i < locations.size(); i++) {
        // Run Dijkstra from the source to all other nodes to find shortest path to i
        std::vector<float> distOutbound(locations.size(), std::numeric_limits<float>::max());
        std::vector<int> prevOutbound(locations.size(), -1);
        dijkstra(graph, source, distOutbound, prevOutbound);

        // Check if collection is needed and the destination is within allowable distance
        if (locations[i].wasteLevel > 40 && distOutbound[i] < 20) {

            // Initialize a new RouteCost object to track total costs for the round trip
            routeCost::RouteCost cost;

            // Specifically set the segment distance from S to location i
            cost.setSegmentDistance(distOutbound[i]);

            std::cout << "-------*" << "Location " << locations[i].garbageLocation_name << "*-------" << std::endl;
            std::cout << "Route to location:\n";
            printPath(i, prevOutbound, locations, cost, distOutbound);
            std::cout << "\n";

            // Run Dijkstra from location i back to the source for the return journey
            std::vector<float> distReturn(locations.size(), std::numeric_limits<float>::max());
            std::vector<int> prevReturn(locations.size(), -1);
            dijkstra(graph, i, distReturn, prevReturn);

            std::cout << "Return route:\n";
            printPath(source, prevReturn, locations, cost, distReturn);
            std::cout << std::endl;

            std::ofstream outFile("DijkstraRoute.txt", std::ios::app);
            // Print the total costs for this round trip
            cost.printCosts(outFile);
            std::cout << std::endl; // Separate different location reports with a newline
        }
    }
}

// Implements Dijkstra's algorithm to compute the shortest paths from a source node to all other nodes in a graph.
void DjikstraRoute::dijkstra(const std::vector<std::vector<std::pair<int, float>>>& graph, int src, std::vector<float>& dist, std::vector<int>& prev) {
    int n = graph.size(); // Number of nodes in the graph
    dist.assign(n, INF); // Initialize the distance to each node as infinity
    prev.assign(n, -1); // Initialize the previous node for each node as -1 (undefined)
    dist[src] = 0; // Set the distance from the source to itself to zero

    // Priority queue to store the nodes to explore, sorted by distance from the source
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<std::pair<float, int>>> pq;
    pq.push({0, src}); // Push the source node onto the queue with distance 0

    // Loop until there are no more nodes to process
    while (!pq.empty()) {
        auto [d, u] = pq.top(); // Get the node with the smallest distance
        pq.pop(); // Remove this node from the queue

        if (d > dist[u]) // If the recorded distance is greater than the current distance, skip processing
            continue;

        // Iterate through each adjacent node
        for (auto& edge : graph[u]) {
            int v = edge.first; // Node at the end of the edge
            float weight = edge.second; // Weight of the edge
            if (dist[u] + weight < dist[v]) { // If the new distance to node v is shorter, update it
                dist[v] = dist[u] + weight;
                prev[v] = u; // Record the previous node
                pq.push({dist[v], v}); // Push the updated distance to the priority queue
            }
        }
    }
}

// Prints the optimal path from the source to a target node and calculates the transportation costs based on distances.
void DjikstraRoute::printPath(int target, const std::vector<int>& prev, const std::vector<garbageLocation>& locations, routeCost::RouteCost& cost, const std::vector<float>& dist) {
    if (prev[target] == -1) {
        std::cout << " No path";
        return;
    }
    std::vector<int> path;
    for (int v = target; v != -1; v = prev[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); i++) {
        if (i > 0) std::cout << " -> ";
        std::cout << locations[path[i]].garbageLocation_name;
        if (i > 0) {
            cost.updateCosts(dist[path[i]] - dist[path[i - 1]]);
        }
    }
}
