#include "Citydj.h"
#include <iostream>

using namespace std;

/**
 * @brief Test function for Phase 7 - Dijkstra Algorithm
 */
void testPhase7()
{
    cout << "=== PHASE 7 TEST: DIJKSTRA ALGORITHM ===" << endl;

    // Create a city with complex road network
    City city;

    // Test 1: Setup city graph
    cout << "\nTest 1: Setting up city graph" << endl;

    // Add locations (0-9 for simplicity)
    for (int i = 0; i < 10; i++)
    {
        city.addLocation(i);
    }

    // Create a complex road network (weighted graph)
    city.addRoad(0, 1, 4);  // 0-1: 4km
    city.addRoad(0, 7, 8);  // 0-7: 8km
    city.addRoad(1, 2, 8);  // 1-2: 8km
    city.addRoad(1, 7, 11); // 1-7: 11km
    city.addRoad(2, 3, 7);  // 2-3: 7km
    city.addRoad(2, 8, 2);  // 2-8: 2km
    city.addRoad(2, 5, 4);  // 2-5: 4km
    city.addRoad(3, 4, 9);  // 3-4: 9km
    city.addRoad(3, 5, 14); // 3-5: 14km
    city.addRoad(4, 5, 10); // 4-5: 10km
    city.addRoad(5, 6, 2);  // 5-6: 2km
    city.addRoad(6, 7, 1);  // 6-7: 1km
    city.addRoad(6, 8, 6);  // 6-8: 6km
    city.addRoad(7, 8, 7);  // 7-8: 7km

    // Set zones for locations
    city.setZone(0, 0); // Zone 0: Downtown
    city.setZone(1, 0);
    city.setZone(2, 0);
    city.setZone(3, 1); // Zone 1: Suburb A
    city.setZone(4, 1);
    city.setZone(5, 1);
    city.setZone(6, 2); // Zone 2: Suburb B
    city.setZone(7, 2);
    city.setZone(8, 2);
    city.setZone(9, 3); // Zone 3: Isolated area (no roads)

    // Print graph structure
    city.printGraph();

    // Test 2: Dijkstra from source 0
    cout << "\nTest 2: Dijkstra from source location 0" << endl;
    City::ShortestPathResult result1 = city.dijkstra(0);
    result1.printDistances();

    // Test specific distances
    cout << "\nSpecific distances from location 0:" << endl;
    cout << "0 -> 4: " << result1.getDistanceTo(4) << " km" << endl;
    cout << "0 -> 8: " << result1.getDistanceTo(8) << " km" << endl;
    cout << "0 -> 9: " << result1.getDistanceTo(9) << " km (should be -1, no path)" << endl;

    // Test 3: Dijkstra from source 2
    cout << "\nTest 3: Dijkstra from source location 2" << endl;
    City::ShortestPathResult result2 = city.dijkstra(2);
    result2.printDistances();

    // Test 4: Get path from 0 to 4
    cout << "\nTest 4: Getting shortest path from 0 to 4" << endl;
    int *path1 = new int[city.getNodeCount()];
    int pathLength1 = result1.getPathTo(4, path1);

    if (pathLength1 > 0)
    {
        cout << "Shortest path from 0 to 4 (" << result1.getDistanceTo(4) << " km): ";
        for (int i = 0; i < pathLength1; i++)
        {
            cout << path1[i];
            if (i < pathLength1 - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }
    else
    {
        cout << "No path exists from 0 to 4!" << endl;
    }

    // Test 5: Get path from 0 to 8
    cout << "\nTest 5: Getting shortest path from 0 to 8" << endl;
    int *path2 = new int[city.getNodeCount()];
    int pathLength2 = result1.getPathTo(8, path2);

    if (pathLength2 > 0)
    {
        cout << "Shortest path from 0 to 8 (" << result1.getDistanceTo(8) << " km): ";
        for (int i = 0; i < pathLength2; i++)
        {
            cout << path2[i];
            if (i < pathLength2 - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
    }

    // Test 6: Convenience methods
    cout << "\nTest 6: Testing convenience methods" << endl;
    cout << "Shortest distance from 0 to 5: " << city.getShortestDistance(0, 5) << " km" << endl;
    cout << "Shortest distance from 5 to 0: " << city.getShortestDistance(5, 0) << " km (should be same)" << endl;
    cout << "Shortest distance from 0 to 9: " << city.getShortestDistance(0, 9) << " km (no path)" << endl;

    // Test 7: Get path using convenience method
    cout << "\nTest 7: Getting path using convenience method (3 to 7)" << endl;
    int *path3 = new int[city.getNodeCount()];
    int pathLength3 = city.getShortestPath(3, 7, path3);

    if (pathLength3 > 0)
    {
        cout << "Shortest path from 3 to 7: ";
        for (int i = 0; i < pathLength3; i++)
        {
            cout << path3[i];
            if (i < pathLength3 - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Total distance: " << city.getShortestDistance(3, 7) << " km" << endl;
    }

    // Test 8: Different source nodes
    cout << "\nTest 8: Testing different source nodes" << endl;

    int sources[] = {1, 5, 7};
    for (int i = 0; i < 3; i++)
    {
        int source = sources[i];
        cout << "\nDistances from location " << source << ":" << endl;

        City::ShortestPathResult result = city.dijkstra(source);
        for (int dest = 0; dest < 9; dest++)
        {
            int dist = result.getDistanceTo(dest);
            if (dist != -1)
            {
                cout << "  to " << dest << ": " << dist << " km" << endl;
            }
        }
    }

    // Test 9: Invalid nodes
    cout << "\nTest 9: Testing with invalid nodes" << endl;
    City::ShortestPathResult invalidResult = city.dijkstra(100); // Non-existent node
    cout << "Dijkstra with non-existent source returned result with "
         << invalidResult.nodeCount << " nodes." << endl;

    // Test 10: Verify algorithm correctness with known paths
    cout << "\nTest 10: Verifying algorithm correctness" << endl;

    // Known path: 0 -> 1 = 4km (direct)
    cout << "0 -> 1 direct: " << city.getDistance(0, 1) << " km" << endl;
    cout << "0 -> 1 shortest: " << city.getShortestDistance(0, 1) << " km" << endl;

    // Known path: 0 -> 4 should be 0-7-6-5-4 or 0-1-2-5-4
    int *testPath = new int[city.getNodeCount()];
    int testPathLength = city.getShortestPath(0, 4, testPath);

    if (testPathLength > 0)
    {
        cout << "Shortest path 0 -> 4 (" << city.getShortestDistance(0, 4) << " km): ";
        for (int i = 0; i < testPathLength; i++)
        {
            cout << testPath[i];
            if (i < testPathLength - 1)
            {
                cout << " -> ";
            }
        }
        cout << endl;

        // Calculate total distance manually
        int manualDistance = 0;
        for (int i = 0; i < testPathLength - 1; i++)
        {
            manualDistance += city.getDistance(testPath[i], testPath[i + 1]);
        }
        cout << "Manual calculation of path distance: " << manualDistance << " km" << endl;
    }

    // Clean up
    delete[] path1;
    delete[] path2;
    delete[] path3;
    delete[] testPath;

    cout << "\n=== PHASE 7 TEST COMPLETE ===" << endl;
}

int main()
{
    testPhase7();
    return 0;
}