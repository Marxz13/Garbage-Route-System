#include "garbageLocation.h"
#include "optimizedRoute.h"
#include "djikstraRoute.h"
#include "aStarRoute.h"
#include "menuPrint.h"

#include <stdlib.h>
#include <iostream>
#include <limits>
#include <queue>
#include <algorithm>

#define INF (std::numeric_limits<float>::max())  // Define infinity as the maximum value a float can hold

using namespace std;

// Function to convert a distance matrix to an adjacency list representation
vector<vector<pair<int, float>>> createGraph(float dist[][9], int n) {
    vector<vector<pair<int, float>>> graph(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (dist[i][j] != INF && i != j) { // Exclude self loops and infinite distances
                graph[i].push_back({j, dist[i][j]});
            }
        }
    }
    return graph;
}

int main()
{
    MenuPrint menu;  // Initialize the menu interface

    int totalLocations = 9;  // Total number of locations including the start point 'S'
    // Randomly determine which locations are affected by high traffic today
    vector<int> affected = garbageLocation::randomizeAffectedLocations(2, totalLocations);

    // Update traffic conditions based on weather and time
    garbageLocation::updateTrafficConditions(affected);
    // Initialize garbage location vectors with predefined properties
    vector<garbageLocation> locations = garbageLocation::initialize_garbageLocation_vector();

    int option;
    do {
        // Display affected locations for user verification
        cout << "High-Traffic Locations Today:";
        for (int loc : affected) {
            cout << garbageLocation::indexToName(loc) << " ";
        }
        cout << "\n";
        cout << "\n";
        // Print current waste levels at all locations
        garbageLocation::printWasteLevels(locations);
        cout << "\n";
        // Show main menu and capture user selection
        menu.printMainMenu();
        cin >> option;
        switch(option){
            case 1:{
                system("cls"); // Clear screen
                int mrpm;
                menu.printMultipleRouteMenu();
                cin >> mrpm;
                switch(mrpm){
                    case 1:{
                        system("cls");
                        float dist[9][9];  // Distance matrix
                        int next[9][9];    // Next hop matrix
                        cout << "Floyd-Warshall | 60% Garbage Level | <40km" << endl;
                        for (int i = 0; i < 9; ++i) {
                            for (int j = 0; j < 9; ++j) {
                                dist[i][j] = garbageLocation::distanceMatrix[i][j];
                                if (i != j && dist[i][j] != INF) {
                                    next[i][j] = j;
                                } else {
                                    next[i][j] = -1;
                                }
                            }
                        }
                        // Compute shortest paths using Floyd-Warshall algorithm
                        OptimizedRoute::floydWarshall(dist, next);
                        // Generate routes based on the Floyd-Warshall algorithm output
                        OptimizedRoute::generatefloydWarshall(locations, dist, next);
                        cout << "\n";
                        if (!menu.printReturn()) {
                            option = false;
                        }
                        break;
                    }
                    case 2:{
                        system("cls");
                        float dist[9][9];
                        int next[9][9];
                        cout <<"Generated Djikstra | 40% Garbage Level | <20Km" << endl;
                        for (int i = 0; i < 9; ++i) {
                            for (int j = 0; j < 9; ++j) {
                                dist[i][j] = garbageLocation::distanceMatrix[i][j];
                                if (i != j && dist[i][j] != INF) {
                                    next[i][j] = j;
                                } else {
                                    next[i][j] = -1;
                                }
                            }
                        }
                        // Create a graph from the distance matrix for Dijkstra's algorithm
                        vector<vector<pair<int, float>>> graph = createGraph(dist, 9);
                        // Generate routes using Dijkstra's algorithm
                        DjikstraRoute::generateDijkstraRoute(locations, graph);
                        cout << "\n";
                        if (!menu.printReturn()) {
                            option = false;
                        }
                        break;
                    }
                }
                break;
            }
            case 2:{
                system("cls");
                // Generate routes using A* algorithm with a garbage threshold of 50%
                AStarRoute::generateRoutes(locations, 50);
                if (!menu.printReturn()) {
                    option = false;
                }
                break;
            }
            case 3:{
                system("cls");
                // Print the graphical representation of the network
                garbageLocation::printGraph();
                cout << "\n";
                if (!menu.printReturn()) {
                    option = false;
                }
                break;
            }

        }
    } while(option != 9);
    cout << "Exiting..." << endl;  // Exit message
    return 0;
}
