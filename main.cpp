#include <iostream>
#include "City.h"

using namespace std;

int main()
{
    City city;

    city.addLocation(1);
    city.addLocation(2);
    city.addLocation(3);
    city.addLocation(4);

    city.addRoad(1, 2);
    city.addRoad(2, 3);
    city.addRoad(3, 4);
    city.addRoad(4, 1);

    city.printGraph();

    return 0;
}
