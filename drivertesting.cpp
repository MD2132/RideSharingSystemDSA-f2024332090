#include "Driver.h"
#include <iostream>

using namespace std;

/**
 * @brief Test function for Phase 4 - Driver Class
 */
void testPhase4()
{
    cout << "=== PHASE 4 TEST: DRIVER CLASS ===" << endl;

    // Test 1: Create drivers using different constructors
    cout << "\nTest 1: Creating drivers" << endl;

    // Default constructor
    Driver driver1;
    cout << "Default driver created." << endl;

    // Parameterized constructor
    Driver driver2(101, 5, 0);  // ID 101, at location 5, in zone 0
    Driver driver3(102, 8, 1);  // ID 102, at location 8, in zone 1
    Driver driver4(103, 12, 2); // ID 103, at location 12, in zone 2

    // Test 2: Test getter methods
    cout << "\nTest 2: Testing getter methods" << endl;
    cout << "Driver 2 ID: " << driver2.getId() << endl;
    cout << "Driver 2 Location: " << driver2.getCurrentLocation() << endl;
    cout << "Driver 2 Zone: " << driver2.getZoneId() << endl;
    cout << "Driver 2 Status: " << Driver::statusToString(driver2.getStatus()) << endl;
    cout << "Driver 2 Available: " << (driver2.isAvailable() ? "Yes" : "No") << endl;

    // Test 3: Test setter methods
    cout << "\nTest 3: Testing setter methods" << endl;

    // Change location
    driver2.setCurrentLocation(10);
    cout << "Driver 2 new location: " << driver2.getCurrentLocation() << endl;

    // Change zone
    driver2.setZoneId(3);
    cout << "Driver 2 new zone: " << driver2.getZoneId() << endl;

    // Test invalid inputs
    driver2.setCurrentLocation(-5); // Should show error
    driver2.setZoneId(-1);          // Should show error

    // Test 4: Test status transitions
    cout << "\nTest 4: Testing status transitions" << endl;

    cout << "Initial status of driver 3: " << Driver::statusToString(driver3.getStatus()) << endl;
    cout << "Is available? " << (driver3.isAvailable() ? "Yes" : "No") << endl;

    // Simulate trip assignment
    driver3.setStatus(ASSIGNED);
    cout << "After assignment - Available? " << (driver3.isAvailable() ? "Yes" : "No") << endl;

    // Simulate starting trip
    driver3.setStatus(ON_TRIP);

    // Simulate completing trip
    driver3.setStatus(AVAILABLE);
    cout << "After completion - Available? " << (driver3.isAvailable() ? "Yes" : "No") << endl;

    // Go offline
    driver3.setStatus(OFFLINE);

    // Test 5: Print driver information
    cout << "\nTest 5: Printing driver information" << endl;
    driver2.printInfo();
    driver3.printInfo();

    // Test 6: Test all status strings
    cout << "\nTest 6: Testing all status string conversions" << endl;
    cout << "AVAILABLE: " << Driver::statusToString(AVAILABLE) << endl;
    cout << "ASSIGNED: " << Driver::statusToString(ASSIGNED) << endl;
    cout << "ON_TRIP: " << Driver::statusToString(ON_TRIP) << endl;
    cout << "OFFLINE: " << Driver::statusToString(OFFLINE) << endl;

    // Test 7: Test multiple drivers
    cout << "\nTest 7: Testing multiple drivers" << endl;
    Driver drivers[3] = {
        Driver(201, 1, 0),
        Driver(202, 2, 1),
        Driver(203, 3, 2)};

    // Check availability of all drivers
    for (int i = 0; i < 3; i++)
    {
        cout << "Driver " << drivers[i].getId()
             << " is available: " << (drivers[i].isAvailable() ? "Yes" : "No") << endl;
    }

    // Assign first driver
    drivers[0].setStatus(ASSIGNED);
    cout << "\nAfter assigning driver " << drivers[0].getId()
         << ", availability: " << (drivers[0].isAvailable() ? "Yes" : "No") << endl;

    cout << "\n=== PHASE 4 TEST COMPLETE ===" << endl;
}

int main()
{
    testPhase4();
    return 0;
}