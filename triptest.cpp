#include "Trip.h"
#include <iostream>

using namespace std;

/**
 * @brief Test function for Phase 6 - Trip State Machine
 */
void testPhase6()
{
    cout << "=== PHASE 6 TEST: TRIP STATE MACHINE ===" << endl;

    // Display state diagram
    Trip::printStateDiagram();

    // Test 1: Create trips
    cout << "\nTest 1: Creating trips" << endl;
    Trip trip1(1001, 201, 5, 10, 15); // 15km trip
    Trip trip2(1002, 202, 8, 20, 25); // 25km trip

    // Test invalid trip
    Trip trip3(-1, -1, -5, -5, 0); // All invalid inputs

    // Test 2: Print trip information
    cout << "\nTest 2: Printing trip information" << endl;
    trip1.printInfo();
    trip2.printInfo();

    // Test 3: Test fare calculation
    cout << "\nTest 3: Testing fare calculation" << endl;
    cout << "Trip 1 fare: " << trip1.getFare() << endl;
    cout << "Trip 2 fare: " << trip2.getFare() << endl;

    // Update distance and check fare recalculation
    trip1.setDistance(20);
    cout << "Trip 1 updated fare: " << trip1.getFare() << endl;

    // Test 4: Valid state transitions (happy path)
    cout << "\nTest 4: Valid state transitions (complete trip lifecycle)" << endl;

    Trip happyTrip(1003, 203, 1, 10, 12);
    cout << "\nStarting happy path for Trip 1003:" << endl;

    // 1. Assign driver
    cout << "\n1. Assigning driver..." << endl;
    if (happyTrip.assignDriver(301))
    {
        cout << "Driver assigned successfully!" << endl;
    }

    // 2. Start trip
    cout << "\n2. Starting trip..." << endl;
    if (happyTrip.startTrip())
    {
        cout << "Trip started successfully!" << endl;
    }

    // 3. Complete trip
    cout << "\n3. Completing trip..." << endl;
    if (happyTrip.completeTrip())
    {
        cout << "Trip completed successfully!" << endl;
    }

    happyTrip.printInfo();

    // Test 5: Invalid state transitions
    cout << "\nTest 5: Testing invalid state transitions" << endl;

    Trip testTrip(1004, 204, 2, 8, 10);

    // Try invalid: start trip before assigning driver
    cout << "\n1. Trying to start trip before assigning driver..." << endl;
    testTrip.startTrip();

    // Try invalid: assign driver after cancellation
    cout << "\n2. Cancelling trip then trying to assign driver..." << endl;
    testTrip.cancelTrip();
    testTrip.assignDriver(302);

    // Try invalid: complete cancelled trip
    cout << "\n3. Trying to complete cancelled trip..." << endl;
    testTrip.completeTrip();

    // Try invalid: transition from completed state
    cout << "\n4. Creating completed trip and trying to cancel..." << endl;
    Trip completedTrip(1005, 205, 3, 9, 8);
    completedTrip.assignDriver(303);
    completedTrip.startTrip();
    completedTrip.completeTrip();
    completedTrip.cancelTrip(); // Should fail

    // Test 6: Cancellation scenarios
    cout << "\nTest 6: Testing cancellation scenarios" << endl;

    // Cancel in REQUESTED state
    cout << "\n1. Cancelling in REQUESTED state..." << endl;
    Trip cancelTrip1(1006, 206, 4, 12, 10);
    cancelTrip1.cancelTrip();

    // Cancel in ASSIGNED state
    cout << "\n2. Cancelling in ASSIGNED state..." << endl;
    Trip cancelTrip2(1007, 207, 5, 15, 12);
    cancelTrip2.assignDriver(304);
    cancelTrip2.cancelTrip();

    // Cancel in ONGOING state
    cout << "\n3. Cancelling in ONGOING state..." << endl;
    Trip cancelTrip3(1008, 208, 6, 18, 15);
    cancelTrip3.assignDriver(305);
    cancelTrip3.startTrip();
    cancelTrip3.cancelTrip();

    // Test 7: Check active and final states
    cout << "\nTest 7: Checking active and final states" << endl;

    Trip activeTrip(1009, 209, 7, 14, 8);
    cout << "New trip active: " << (activeTrip.isActive() ? "Yes" : "No") << endl;
    cout << "New trip final: " << (activeTrip.isFinalState() ? "Yes" : "No") << endl;

    activeTrip.assignDriver(306);
    cout << "After assignment active: " << (activeTrip.isActive() ? "Yes" : "No") << endl;

    activeTrip.startTrip();
    cout << "After start active: " << (activeTrip.isActive() ? "Yes" : "No") << endl;

    activeTrip.completeTrip();
    cout << "After completion active: " << (activeTrip.isActive() ? "Yes" : "No") << endl;
    cout << "After completion final: " << (activeTrip.isFinalState() ? "Yes" : "No") << endl;

    // Test 8: State string conversions
    cout << "\nTest 8: Testing state string conversions" << endl;
    cout << "REQUESTED: " << Trip::stateToString(REQUESTED) << endl;
    cout << "ASSIGNED: " << Trip::stateToString(ASSIGNED) << endl;
    cout << "ONGOING: " << Trip::stateToString(ONGOING) << endl;
    cout << "COMPLETED: " << Trip::stateToString(COMPLETED) << endl;
    cout << "CANCELLED: " << Trip::stateToString(CANCELLED) << endl;

    // Test 9: Multiple trips with different states
    cout << "\nTest 9: Multiple trips simulation" << endl;

    Trip trips[5] = {
        Trip(1010, 210, 1, 5, 8),
        Trip(1011, 211, 2, 6, 10),
        Trip(1012, 212, 3, 7, 12),
        Trip(1013, 213, 4, 8, 15),
        Trip(1014, 214, 5, 9, 20)};

    // Process each trip differently
    trips[0].assignDriver(310); // Only assigned
    trips[1].assignDriver(311);
    trips[1].startTrip(); // Started but not completed
    trips[2].assignDriver(312);
    trips[2].startTrip();
    trips[2].completeTrip(); // Completed
    trips[3].cancelTrip();   // Cancelled immediately
    // trips[4] stays in REQUESTED

    cout << "\nFinal states of all trips:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "Trip " << trips[i].getId() << ": "
             << Trip::stateToString(trips[i].getState()) << endl;
    }

    cout << "\n=== PHASE 6 TEST COMPLETE ===" << endl;
}

int main()
{
    testPhase6();
    return 0;
}