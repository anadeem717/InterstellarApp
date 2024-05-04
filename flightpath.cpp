/// @file flightpath.cpp

/*-------------------------------------------
Project 6: FlightPath Class CPP File
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE
Author: Areesh Nadeem
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Flight path class implementations.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "solarsystem.h"
#include "flightpath.h"

using namespace std;


// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.



// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.


// Create a path through user input, and add it <path> vector.
// Invalid Solar Systems are not added to the path.
void FlightPath::createPath(const vector<shared_ptr<SolarSystem>> &systems) {
    cout << "Activating flight plan plotting system...\n";
    cout << "Only valid solar systems can be added to the plan.\n\n";
    cout << "Type DONE to terminate flight planning.\n\n";

    while (true) {
        cout << "Name of a Solar System to add to plan: \n";

        string system; 
        getline(cin, system); 

        cout << endl;

        if (system == "DONE") { break; }

        bool exists = false;
        shared_ptr<SolarSystem> newSystem;

        // check to see if system is valid / exists
        for (auto const& e : systems) {
            if (e->getName() == system) { 
                exists = true;
                newSystem = e; 
                break;
            }
        }

        if (!exists) {
            cout << "Invalid system: Nothing added to path.\n"; 
            continue;
        }

        path.push_back(newSystem);
        cout << newSystem->getName() << " added to path.\n";

    }
}

// Check to see if <path> is a valid pathway
// Using system connections data. 
bool FlightPath::isValid(const vector<shared_ptr<SolarSystem>> &systems) const {

    // edge cases
    if (path.size() == 0) { return true; }
    if (path.size() == 1) { return true; }

    // check and see every A->B if it is valid connection
    for (size_t i = 0; i < path.size() - 1; i++) {
        auto currSys = path.at(i);
        auto x = systemIndex(systems, currSys->getName());

        if (x == -1) { return false; }

        // if the connection doesn't exist between A->B,
        // then it is not valid
        if (!(systems.at(x)->connectionExists(path.at(i+1)->getName()))) {
            return false;
        }
    }

    return true; // valid
}        

// returns <path> vector
vector<shared_ptr<SolarSystem>> FlightPath::getPath() const { return path; }

// Return the string the path containing names of systems
string FlightPath::toString() const {
    string output;

    for (size_t i = 0; i < path.size(); i++) {
        if (i == path.size() - 1) {
            output += path.at(i)->getName();
            break;
        }
        output += path.at(i)->getName() + " -> ";
    }

    return output; 
}

// Creates a human readable string of everything we see on the path.
// The returned string includes all Celestial Objects as well. 
string FlightPath::toStringAll() const {
    string output;

    for (size_t i = 0; i < path.size(); i++) {
        if (i == path.size() - 1) {
            output += path.at(i)->toString();
            break;
        }
        output += path.at(i)->toString() + '\n';
    }

    return output;

}

// Convert path's Solar System connections to a string
string FlightPath::connectionsString() const {

    if (path.size() == 0) { return {}; }

    string output;
    for (size_t i = 0; i < path.size(); i++) {
        if (i == path.size() - 1) {
            output += path.at(i)->getName() + " -> ";
            output += path.at(i)->connectionsToString();
            break;
        }
        output += path.at(i)->getName() + " -> ";
        output += path.at(i)->connectionsToString() + '\n';
    }

    return output; 
}


// Outputs the stored path
// Outputs "(empty path)" if <path> is empty
void FlightPath::printPath() const {
    cout << "Planned Path:\n";
    
    if (path.size() == 0) { cout << "(empty path)\n"; }
    else {
        cout << toString() << endl; 
    }

} 

// Outputs the Celestials on path
// Outputs "(empty path)" if <path> is empty
void FlightPath::printPathCelestials() const {
    cout << "Celestials on Path:\n";

    if (path.size() == 0) { cout << "(empty path)\n"; }
    else {
        cout << toStringAll() << endl; 
    }
}

// Outputs the connections for the path
// Outputs "(empty path)" if <path> is empty
void FlightPath::printConnections() const {
    cout << "Path Connections:\n";

    if (path.size() == 0) { cout << "(empty path)\n"; }
    else {
        cout << connectionsString() << endl; 
    }
}

// Clears the <path> vector
void FlightPath::clear() { path.clear(); }