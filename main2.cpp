#include "City.h"
#include <iostream>

using namespace std;

/**
 * @brief Test function for Phase 2 - Weighted City Graph
 */
void testPhase2()
{
    cout << "=== PHASE 2 TEST: WEIGHTED CITY GRAPH ===" << endl;

    // Create a city
    City city;

    // Test 1: Add locations
    cout << "\nTest 1: Adding locations" << endl;
    city.addLocation(1);
    city.addLocation(2);
    city.addLocation(3);
    city.addLocation(4);
    city.addLocation(5);

    // Test 2: Add roads with distances
    cout << "\nTest 2: Adding weighted roads" << endl;
    city.addRoad(1, 2, 5);  // 5km between 1 and 2
    city.addRoad(1, 3, 10); // 10km between 1 and 3
    city.addRoad(2, 3, 3);  // 3km between 2 and 3
    city.addRoad(2, 4, 7);  // 7km between 2 and 4
    city.addRoad(3, 5, 8);  // 8km between 3 and 5
    city.addRoad(4, 5, 2);  // 2km between 4 and 5

    // Test invalid roads
    cout << "\nTest 3: Testing invalid roads" << endl;
    city.addRoad(1, 6, 5);  // Non-existent node
    city.addRoad(1, 2, 0);  // Zero distance
    city.addRoad(1, 2, -5); // Negative distance
    city.addRoad(1, 1, 5);  // Self-loop

    // Test duplicate road
    city.addRoad(1, 2, 8); // Already exists

    // Test 4: Print weighted graph
    cout << "\nTest 4: Printing weighted graph structure" << endl;
    city.printGraph();

    // Test 5: Get distances
    cout << "\nTest 5: Getting distances between locations" << endl;
    cout << "Distance from 1 to 2: " << city.getDistance(1, 2) << "km" << endl;
    cout << "Distance from 3 to 5: " << city.getDistance(3, 5) << "km" << endl;
    cout << "Distance from 1 to 4: " << city.getDistance(1, 4) << "km" << endl;
    cout << "Distance from 1 to 5: " << city.getDistance(1, 5) << "km (should be -1: no direct road)" << endl;
    cout << "Distance from 6 to 1: " << city.getDistance(6, 1) << "km (should be -1: node doesn't exist)" << endl;

    // Test 6: Verify undirected nature
    cout << "\nTest 6: Verifying undirected graph symmetry" << endl;
    cout << "Distance from 2 to 1: " << city.getDistance(2, 1) << "km (should match 1→2)" << endl;
    cout << "Distance from 5 to 3: " << city.getDistance(5, 3) << "km (should match 3→5)" << endl;

    cout << "\n=== PHASE 2 TEST COMPLETE ===" << endl;
}

int main()
{
    testPhase2();
    return 0;
}