#include "Rider.h"
#include <iostream>

using namespace std;

/**
 * @brief Test function for Phase 5 - Rider Class
 */
void testPhase5()
{
    cout << "=== PHASE 5 TEST: RIDER CLASS ===" << endl;

    // Test 1: Create riders using different constructors
    cout << "\nTest 1: Creating riders" << endl;

    // Default constructor
    Rider rider1;
    cout << "Default rider created." << endl;

    // Parameterized constructor
    Rider rider2(201, 5, 10);  // ID 201, pickup at 5, dropoff at 10
    Rider rider3(202, 8, 15);  // ID 202, pickup at 8, dropoff at 15
    Rider rider4(203, 12, 12); // ID 203, pickup = dropoff (warning)

    // Test with negative IDs (should show warnings)
    Rider rider5(-1, 1, 2); // Invalid ID

    // Test 2: Test getter methods
    cout << "\nTest 2: Testing getter methods" << endl;
    cout << "Rider 2 ID: " << rider2.getId() << endl;
    cout << "Rider 2 Pickup: " << rider2.getPickupLocation() << endl;
    cout << "Rider 2 Dropoff: " << rider2.getDropoffLocation() << endl;
    cout << "Rider 2 Has Active Trip: " << (rider2.hasActiveTripStatus() ? "Yes" : "No") << endl;

    // Test 3: Test setter methods
    cout << "\nTest 3: Testing setter methods" << endl;

    // Change pickup location
    rider2.setPickupLocation(7);
    cout << "Rider 2 new pickup: " << rider2.getPickupLocation() << endl;

    // Change dropoff location
    rider2.setDropoffLocation(12);
    cout << "Rider 2 new dropoff: " << rider2.getDropoffLocation() << endl;

    // Test invalid inputs
    rider2.setPickupLocation(-5);  // Should show error
    rider2.setDropoffLocation(-1); // Should show error

    // Test 4: Test trip status management
    cout << "\nTest 4: Testing trip status management" << endl;

    cout << "Initial active trip status for rider 3: "
         << (rider3.hasActiveTripStatus() ? "Active" : "Inactive") << endl;

    // Start a trip
    rider3.setActiveTripStatus(true);
    cout << "After starting trip: "
         << (rider3.hasActiveTripStatus() ? "Active" : "Inactive") << endl;

    // Complete trip
    rider3.setActiveTripStatus(false);
    cout << "After completing trip: "
         << (rider3.hasActiveTripStatus() ? "Active" : "Inactive") << endl;

    // Test 5: Update trip request
    cout << "\nTest 5: Testing trip request update" << endl;
    rider3.updateTripRequest(20, 25);
    cout << "New pickup: " << rider3.getPickupLocation() << endl;
    cout << "New dropoff: " << rider3.getDropoffLocation() << endl;

    // Test 6: Validate trip requests
    cout << "\nTest 6: Validating trip requests" << endl;

    // Valid request
    Rider validRider(301, 1, 5);
    cout << "Valid rider trip valid: " << (validRider.validateTripRequest() ? "Yes" : "No") << endl;

    // Invalid: same pickup and dropoff
    Rider invalidRider1(302, 5, 5);
    cout << "Same locations valid: " << (invalidRider1.validateTripRequest() ? "Yes" : "No") << endl;

    // Invalid: negative location
    Rider invalidRider2(303, -1, 5);
    cout << "Negative location valid: " << (invalidRider2.validateTripRequest() ? "Yes" : "No") << endl;

    // Invalid: active trip already
    Rider invalidRider3(304, 1, 5);
    invalidRider3.setActiveTripStatus(true);
    cout << "With active trip valid: " << (invalidRider3.validateTripRequest() ? "Yes" : "No") << endl;

    // Test 7: Print rider information
    cout << "\nTest 7: Printing rider information" << endl;
    rider2.printInfo();
    validRider.printInfo();

    // Test 8: Estimate trip distance
    cout << "\nTest 8: Estimating trip distances" << endl;

    Rider riderA(401, 10, 30);
    cout << "Rider " << riderA.getId() << " distance: " << riderA.estimateTripDistance() << endl;

    Rider riderB(402, 5, 5);
    cout << "Rider " << riderB.getId() << " distance: " << riderB.estimateTripDistance() << endl;

    Rider riderC(403, 100, 50);
    cout << "Rider " << riderC.getId() << " distance: " << riderC.estimateTripDistance() << endl;

    // Test 9: Test multiple riders
    cout << "\nTest 9: Testing multiple riders" << endl;
    Rider riders[3] = {
        Rider(501, 1, 10),
        Rider(502, 2, 20),
        Rider(503, 3, 30)};

    for (int i = 0; i < 3; i++)
    {
        cout << "Rider " << riders[i].getId()
             << " wants to go from " << riders[i].getPickupLocation()
             << " to " << riders[i].getDropoffLocation() << endl;
    }

    cout << "\n=== PHASE 5 TEST COMPLETE ===" << endl;
}

int main()
{
    testPhase5();
    return 0;
}