#ifndef ROUTECOST_H_INCLUDED
#define ROUTECOST_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
class routeCost {
private:
    static constexpr float FUEL_COST_PER_KM = 1.0f; // Cost of fuel per kilometer
    static constexpr float FUEL_EFFICIENCY = 3.0f; // Kilometers per liter (this implies 8 km/L)
    static constexpr float MAINTENANCE_COST_PER_KM = 0.70f; // Maintenance cost per kilometer
    static constexpr float LABOR_COST_PER_HOUR = 5.0f; // Labor cost per hour
    static constexpr float AVERAGE_SPEED = 20.0f; // Average speed in km/h

public:
    struct RouteCost {
        float totalDistance = 0;
        float fuelCost = 0;
        float maintenanceCost = 0;
        float laborCost = 0;
        float totalTime = 0; // in hours
        float segmentDistance = 0;
        // Update travel costs based on the distance of each leg
        void updateCosts(float distance) {
            totalDistance += distance;
            float travelTime = distance / AVERAGE_SPEED;
            float fuelConsumption = (distance / FUEL_EFFICIENCY) * FUEL_COST_PER_KM;

            fuelCost += fuelConsumption;
            maintenanceCost += distance * MAINTENANCE_COST_PER_KM;
            totalTime += travelTime;
            laborCost += travelTime * LABOR_COST_PER_HOUR;
        }
        void setSegmentDistance(float distance) {
            segmentDistance = distance;
        }
        // Get the specific segment distance
        float getSegmentDistance() const {
            return segmentDistance;
        }

        // Update costs specifically for collection at stops
        void updateCollectionCosts(float stopTime) {
            totalTime += stopTime;  // Increment total time by stop time
            laborCost += stopTime * LABOR_COST_PER_HOUR;  // Increment labor cost for stop time
        }

        void printCosts( std::ofstream& outFile) const {
            std::cout << "Distance from Station: " << segmentDistance << " km\n";
            std::cout << "Total Distance Inc Return: " << totalDistance << " km\n";
            std::cout << "Total Fuel Cost: $" << std::fixed << std::setprecision(2) << fuelCost << "\n";
            std::cout << "Total Maintenance Cost: $" << std::fixed << std::setprecision(2) << maintenanceCost << "\n";
            std::cout << "Total Labor Cost: $" << std::fixed << std::setprecision(2) << laborCost << "\n";
            std::cout << "Total Time: " << std::fixed << std::setprecision(2) << totalTime << " hours\n";

        outFile << "Distance from Station: " << segmentDistance << " km\n"
                << "Total Distance Inc Return: " << totalDistance << " km\n"
                << "Total Fuel Cost: $" << std::fixed << std::setprecision(2) << fuelCost << "\n"
                << "Total Maintenance Cost: $" << std::fixed << std::setprecision(2) << maintenanceCost << "\n"
                << "Total Labor Cost: $" << std::fixed << std::setprecision(2) << laborCost << "\n"
                << "Total Time: " << std::fixed << std::setprecision(2) << totalTime << " hours\n";
            }
        };
    };


#endif // ROUTECOST_H_INCLUDED
