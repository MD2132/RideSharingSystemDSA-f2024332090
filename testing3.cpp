#include "City.h"
#include <iostream>

using namespace std;

/**
 * @brief Test function for Phase 3 - City Graph with Zones
 */
void testPhase3()
{
    cout << "=== PHASE 3 TEST: CITY GRAPH WITH ZONES ===" << endl;

    // Create a city
    City city;

    // Test 1: Add locations
    cout << "\nTest 1: Adding locations" << endl;
    city.addLocation(1);
    city.addLocation(2);
    city.addLocation(3);
    city.addLocation(4);
    city.addLocation(5);
    city.addLocation(6);
    city.addLocation(7);

    // Test 2: Add roads with distances
    cout << "\nTest 2: Adding weighted roads" << endl;
    city.addRoad(1, 2, 5);
    city.addRoad(1, 3, 10);
    city.addRoad(2, 3, 3);
    city.addRoad(2, 4, 7);
    city.addRoad(3, 5, 8);
    city.addRoad(4, 5, 2);
    city.addRoad(5, 6, 6);
    city.addRoad(6, 7, 4);

    // Test 3: Set zones for locations
    cout << "\nTest 3: Setting zones for locations" << endl;
    city.setZone(1, 0); // Downtown
    city.setZone(2, 0); // Downtown
    city.setZone(3, 0); // Downtown
    city.setZone(4, 1); // Suburb A
    city.setZone(5, 1); // Suburb A
    city.setZone(6, 2); // Suburb B
    city.setZone(7, 2); // Suburb B

    // Test invalid zone operations
    cout << "\nTest 4: Testing invalid zone operations" << endl;
    city.setZone(8, 0);  // Non-existent location
    city.setZone(1, -1); // Invalid zone ID

    // Test 5: Get zone information
    cout << "\nTest 5: Getting zone information" << endl;
    cout << "Zone of location 1: " << city.getZone(1) << endl;
    cout << "Zone of location 4: " << city.getZone(4) << endl;
    cout << "Zone of location 8 (non-existent): " << city.getZone(8) << endl;
    cout << "Zone of location 3: " << city.getZone(3) << endl;

    // Test 6: Print graph with zones
    cout << "\nTest 6: Printing graph with zones" << endl;
    city.printGraph();

    // Test 7: Print zones overview
    cout << "\nTest 7: Printing zones overview" << endl;
    city.printZones();

    // Test 8: Get locations in specific zones
    cout << "\nTest 8: Getting locations in specific zones" << endl;

    // Test Zone 0
    int *zone0Locations = new int[city.getNodeCount()];
    int zone0Count = city.getLocationsInZone(0, zone0Locations);
    cout << "Locations in Zone 0: ";
    for (int i = 0; i < zone0Count; i++)
    {
        cout << zone0Locations[i];
        if (i < zone0Count - 1)
            cout << ", ";
    }
    cout << endl;

    // Test Zone 1
    int *zone1Locations = new int[city.getNodeCount()];
    int zone1Count = city.getLocationsInZone(1, zone1Locations);
    cout << "Locations in Zone 1: ";
    for (int i = 0; i < zone1Count; i++)
    {
        cout << zone1Locations[i];
        if (i < zone1Count - 1)
            cout << ", ";
    }
    cout << endl;

    // Test Zone 2
    int *zone2Locations = new int[city.getNodeCount()];
    int zone2Count = city.getLocationsInZone(2, zone2Locations);
    cout << "Locations in Zone 2: ";
    for (int i = 0; i < zone2Count; i++)
    {
        cout << zone2Locations[i];
        if (i < zone2Count - 1)
            cout << ", ";
    }
    cout << endl;

    // Test non-existent zone
    int *zone3Locations = new int[city.getNodeCount()];
    int zone3Count = city.getLocationsInZone(3, zone3Locations);
    cout << "Locations in Zone 3 (non-existent): " << zone3Count << endl;

    // Clean up
    delete[] zone0Locations;
    delete[] zone1Locations;
    delete[] zone2Locations;
    delete[] zone3Locations;

    // Test 9: Add new location without zone
    cout << "\nTest 9: Adding location without assigning zone" << endl;
    city.addLocation(8);
    cout << "Zone of new location 8 (should be -1): " << city.getZone(8) << endl;

    cout << "\n=== PHASE 3 TEST COMPLETE ===" << endl;
}

int main()
{
    testPhase3();
    return 0;
}