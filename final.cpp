#include <iostream>
#include "Citydj.h"
#include "Driver.h"
#include "Rider.h"
#include "Trip.h"
#include "DispatchEngine.h"

using namespace std;

void printSeparator()
{
    cout << "\n========================================\n"
         << endl;
}

void setupCity(City &city)
{
    // Add locations (nodes)
    cout << "\n=== Setting up City Graph ===" << endl;
    city.addLocation(0); // Location 0
    city.addLocation(1); // Location 1
    city.addLocation(2); // Location 2
    city.addLocation(3); // Location 3
    city.addLocation(4); // Location 4
    city.addLocation(5); // Location 5

    // Add roads (edges)
    city.addRoad(0, 1, 5);  // Distance 5 between 0 and 1
    city.addRoad(0, 2, 10); // Distance 10 between 0 and 2
    city.addRoad(1, 3, 3);  // Distance 3 between 1 and 3
    city.addRoad(2, 3, 7);  // Distance 7 between 2 and 3
    city.addRoad(3, 4, 4);  // Distance 4 between 3 and 4
    city.addRoad(4, 5, 6);  // Distance 6 between 4 and 5

    // Set zones
    city.setZone(0, 1); // Location 0 in Zone 1
    city.setZone(1, 1); // Location 1 in Zone 1
    city.setZone(2, 2); // Location 2 in Zone 2
    city.setZone(3, 2); // Location 3 in Zone 2
    city.setZone(4, 3); // Location 4 in Zone 3
    city.setZone(5, 3); // Location 5 in Zone 3

    cout << "City setup complete!" << endl;
}

int main()
{
    cout << "========================================" << endl;
    cout << "   RIDE-SHARING SYSTEM - SEMESTER PROJECT   " << endl;
    cout << "========================================" << endl;

    // Create city
    City city;
    setupCity(city);

    // Create dispatch engine
    DispatchEngine engine(&city);

    // Display city information
    city.printGraph();
    city.printZones();

    printSeparator();

    // Create drivers
    cout << "\n=== Registering Drivers ===" << endl;
    Driver *driver1 = new Driver(101, 0, 1); // ID 101, at location 0, zone 1
    Driver *driver2 = new Driver(102, 2, 2); // ID 102, at location 2, zone 2
    Driver *driver3 = new Driver(103, 4, 3); // ID 103, at location 4, zone 3

    engine.registerDriver(driver1);
    engine.registerDriver(driver2);
    engine.registerDriver(driver3);

    // Create riders
    cout << "\n=== Creating Riders ===" << endl;
    Rider *rider1 = new Rider(201, 0, 4); // ID 201, from location 0 to 4
    Rider *rider2 = new Rider(202, 1, 5); // ID 202, from location 1 to 5

    // Display initial status
    engine.printStatus();
    engine.printAvailableDrivers();

    printSeparator();

    // Test 1: Handle trip request
    cout << "\n=== Test 1: Trip Request ===" << endl;
    int distance1 = city.getShortestDistance(rider1->getPickupLocation(), rider1->getDropoffLocation());
    cout << "Distance from " << rider1->getPickupLocation() << " to "
         << rider1->getDropoffLocation() << ": " << distance1 << " km" << endl;

    Trip *trip1 = engine.handleTripRequest(*rider1, distance1);
    trip1->printInfo();

    printSeparator();

    // Test 2: Assign driver to trip
    cout << "\n=== Test 2: Assign Driver ===" << endl;
    if (engine.assignDriverToTrip(trip1->getId(), driver1->getId()))
    {
        cout << "Driver assigned successfully!" << endl;
    }

    driver1->printInfo();
    trip1->printInfo();
    engine.printAvailableDrivers();

    printSeparator();

    // Test 3: Start the trip
    cout << "\n=== Test 3: Start Trip ===" << endl;
    if (engine.startTrip(trip1->getId()))
    {
        cout << "Trip started successfully!" << endl;
    }

    trip1->printInfo();
    driver1->printInfo();

    printSeparator();

    // Test 4: Complete the trip
    cout << "\n=== Test 4: Complete Trip ===" << endl;
    if (engine.completeTrip(trip1->getId()))
    {
        cout << "Trip completed successfully!" << endl;
    }

    trip1->printInfo();
    driver1->printInfo();

    printSeparator();

    // Test 5: Cancel a trip
    cout << "\n=== Test 5: Cancel Trip ===" << endl;

    // Create another trip
    int distance2 = city.getShortestDistance(rider2->getPickupLocation(), rider2->getDropoffLocation());
    Trip *trip2 = engine.handleTripRequest(*rider2, distance2);
    engine.assignDriverToTrip(trip2->getId(), driver2->getId());

    cout << "Before cancellation:" << endl;
    trip2->printInfo();
    driver2->printInfo();

    // Cancel the trip
    if (engine.cancelTrip(trip2->getId()))
    {
        cout << "Trip cancelled successfully!" << endl;
    }

    cout << "After cancellation:" << endl;
    trip2->printInfo();
    driver2->printInfo();

    printSeparator();

    // Test 6: Find shortest path
    cout << "\n=== Test 6: Shortest Path Finding ===" << endl;
    City::ShortestPathResult result = city.dijkstra(0);
    result.printDistances();

    // Get specific path
    int path[10];
    int pathLength = city.getShortestPath(0, 5, path);
    if (pathLength > 0)
    {
        cout << "\nShortest path from 0 to 5: ";
        for (int i = 0; i < pathLength; i++)
        {
            cout << path[i];
            if (i < pathLength - 1)
                cout << " -> ";
        }
        cout << endl;
    }

    printSeparator();

    // Final status
    cout << "\n=== Final System Status ===" << endl;
    engine.printStatus();
    engine.printAvailableDrivers();
    engine.printActiveTrips();

    // Show trip state diagram
    Trip::printStateDiagram();

    // Cleanup
    cout << "\n=== Cleaning up ===" << endl;

    // Note: In a real system, you'd want to properly manage memory
    // This is simplified for demonstration
    delete driver1;
    delete driver2;
    delete driver3;
    delete rider1;
    delete rider2;
    // Note: DispatchEngine should handle deleting trips it created

    cout << "\n========================================" << endl;
    cout << "   PROGRAM COMPLETED SUCCESSFULLY!   " << endl;
    cout << "========================================" << endl;

    return 0;
}