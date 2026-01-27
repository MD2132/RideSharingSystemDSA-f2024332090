#include "City.h"
#include <iostream>

using namespace std;

// Default initial capacity for arrays
const int INITIAL_CAPACITY = 10;
const int INITIAL_ROAD_CAPACITY = 5;

// ==================== Road Implementation ====================

City::Road::Road() : toNodeId(-1), distance(0) {}

City::Road::Road(int to, int dist) : toNodeId(to), distance(dist) {}

// ==================== Node Implementation ====================

City::Node::Node() : id(-1), zoneId(-1), roads(nullptr),
                     roadCount(0), capacity(0) {}

City::Node::Node(int nodeId) : id(nodeId), zoneId(-1), roadCount(0)
{
    capacity = INITIAL_ROAD_CAPACITY;
    roads = new Road[capacity];
}

City::Node::~Node()
{
    if (roads != nullptr)
    {
        delete[] roads;
    }
}

void City::Node::addRoad(int to, int distance)
{
    // Resize if needed
    if (roadCount >= capacity)
    {
        capacity *= 2;
        Road *newRoads = new Road[capacity];

        // Copy existing roads
        for (int i = 0; i < roadCount; i++)
        {
            newRoads[i] = roads[i];
        }

        delete[] roads;
        roads = newRoads;
    }

    // Add new road
    roads[roadCount] = Road(to, distance);
    roadCount++;
}

bool City::Node::hasRoadTo(int nodeId) const
{
    for (int i = 0; i < roadCount; i++)
    {
        if (roads[i].toNodeId == nodeId)
        {
            return true;
        }
    }
    return false;
}

int City::Node::getRoadIndex(int nodeId) const
{
    for (int i = 0; i < roadCount; i++)
    {
        if (roads[i].toNodeId == nodeId)
        {
            return i;
        }
    }
    return -1;
}

// ==================== City Implementation ====================

City::City() : nodeCount(0)
{
    capacity = INITIAL_CAPACITY;
    nodes = new Node *[capacity];

    // Initialize all pointers to nullptr
    for (int i = 0; i < capacity; i++)
    {
        nodes[i] = nullptr;
    }
}

City::~City()
{
    // Delete all nodes
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i] != nullptr)
        {
            delete nodes[i];
        }
    }
    delete[] nodes;
}

int City::findNode(int id) const
{
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i] != nullptr && nodes[i]->id == id)
        {
            return i;
        }
    }
    return -1; // Node not found
}

void City::resizeNodes()
{
    capacity *= 2;
    Node **newNodes = new Node *[capacity];

    // Copy existing nodes
    for (int i = 0; i < nodeCount; i++)
    {
        newNodes[i] = nodes[i];
    }

    // Initialize new pointers to nullptr
    for (int i = nodeCount; i < capacity; i++)
    {
        newNodes[i] = nullptr;
    }

    delete[] nodes;
    nodes = newNodes;
}

bool City::addLocation(int id)
{
    // Check if node already exists
    if (findNode(id) != -1)
    {
        cout << "Location " << id << " already exists!" << endl;
        return false;
    }

    // Resize if needed
    if (nodeCount >= capacity)
    {
        resizeNodes();
    }

    // Create new node (zone will be unassigned = -1)
    nodes[nodeCount] = new Node(id);
    nodeCount++;

    cout << "Location " << id << " added successfully!" << endl;
    return true;
}

bool City::addRoad(int from, int to, int distance)
{
    // Validate distance
    if (distance <= 0)
    {
        cout << "Cannot add road: Distance must be positive!" << endl;
        return false;
    }

    int fromIndex = findNode(from);
    int toIndex = findNode(to);

    // Check if both nodes exist
    if (fromIndex == -1)
    {
        cout << "Cannot add road: Location " << from << " does not exist!" << endl;
        return false;
    }

    if (toIndex == -1)
    {
        cout << "Cannot add road: Location " << to << " does not exist!" << endl;
        return false;
    }

    // Check if trying to add road to self
    if (from == to)
    {
        cout << "Cannot add road from a location to itself!" << endl;
        return false;
    }

    // Check if road already exists
    if (nodes[fromIndex]->hasRoadTo(to))
    {
        cout << "Road from " << from << " to " << to << " already exists!" << endl;
        return false;
    }

    // Add road (undirected graph - add both directions)
    nodes[fromIndex]->addRoad(to, distance);
    nodes[toIndex]->addRoad(from, distance);

    cout << "Road from " << from << " to " << to << " with distance "
         << distance << " added successfully!" << endl;
    return true;
}

bool City::setZone(int nodeId, int zoneId)
{
    int nodeIndex = findNode(nodeId);

    if (nodeIndex == -1)
    {
        cout << "Cannot set zone: Location " << nodeId << " does not exist!" << endl;
        return false;
    }

    // Validate zone ID (assuming positive zone IDs)
    if (zoneId < 0)
    {
        cout << "Cannot set zone: Zone ID must be non-negative!" << endl;
        return false;
    }

    nodes[nodeIndex]->zoneId = zoneId;
    cout << "Zone " << zoneId << " assigned to location " << nodeId << " successfully!" << endl;
    return true;
}

int City::getZone(int nodeId) const
{
    int nodeIndex = findNode(nodeId);

    if (nodeIndex == -1)
    {
        return -1; // Location doesn't exist
    }

    return nodes[nodeIndex]->zoneId;
}

int City::getLocationsInZone(int zoneId, int *resultArray) const
{
    int count = 0;

    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i]->zoneId == zoneId)
        {
            resultArray[count] = nodes[i]->id;
            count++;
        }
    }

    return count;
}

int City::getNodeCount() const
{
    return nodeCount;
}

bool City::locationExists(int id) const
{
    return findNode(id) != -1;
}

int City::getDistance(int from, int to) const
{
    int fromIndex = findNode(from);

    if (fromIndex == -1)
    {
        return -1; // Node doesn't exist
    }

    Node *fromNode = nodes[fromIndex];
    int roadIndex = fromNode->getRoadIndex(to);

    if (roadIndex == -1)
    {
        return -1; // Road doesn't exist
    }

    return fromNode->roads[roadIndex].distance;
}

void City::printGraph() const
{
    cout << "\n=== City Graph (Weighted with Zones) ===" << endl;
    cout << "Total locations: " << nodeCount << endl;
    cout << "==========================================" << endl;

    if (nodeCount == 0)
    {
        cout << "City is empty!" << endl;
        return;
    }

    for (int i = 0; i < nodeCount; i++)
    {
        Node *currentNode = nodes[i];
        cout << "Location " << currentNode->id
             << " [Zone: " << (currentNode->zoneId == -1 ? "Unassigned" : to_string(currentNode->zoneId))
             << "] is connected to: ";

        if (currentNode->roadCount == 0)
        {
            cout << "None (isolated)";
        }
        else
        {
            for (int j = 0; j < currentNode->roadCount; j++)
            {
                cout << currentNode->roads[j].toNodeId
                     << "(" << currentNode->roads[j].distance << "km)";
                if (j < currentNode->roadCount - 1)
                {
                    cout << ", ";
                }
            }
        }
        cout << endl;
    }
    cout << "==========================================" << endl;
}

void City::printZones() const
{
    cout << "\n=== City Zones ===" << endl;

    if (nodeCount == 0)
    {
        cout << "City is empty!" << endl;
        return;
    }

    // First, find all unique zones
    int *uniqueZones = new int[nodeCount];
    int uniqueZoneCount = 0;

    for (int i = 0; i < nodeCount; i++)
    {
        int zoneId = nodes[i]->zoneId;
        bool found = false;

        // Check if zone is already in our unique list
        for (int j = 0; j < uniqueZoneCount; j++)
        {
            if (uniqueZones[j] == zoneId)
            {
                found = true;
                break;
            }
        }

        // Add if not found
        if (!found)
        {
            uniqueZones[uniqueZoneCount] = zoneId;
            uniqueZoneCount++;
        }
    }

    // Print each zone and its locations
    for (int i = 0; i < uniqueZoneCount; i++)
    {
        int zoneId = uniqueZones[i];

        if (zoneId == -1)
        {
            cout << "Unassigned Zone: ";
        }
        else
        {
            cout << "Zone " << zoneId << ": ";
        }

        bool first = true;
        for (int j = 0; j < nodeCount; j++)
        {
            if (nodes[j]->zoneId == zoneId)
            {
                if (!first)
                {
                    cout << ", ";
                }
                cout << nodes[j]->id;
                first = false;
            }
        }
        cout << endl;
    }

    delete[] uniqueZones;
    cout << "==================" << endl;
}