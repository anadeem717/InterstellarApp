/// @file satellite.cpp

/*-------------------------------------------
Project 6: SolarSystem Class CPP File
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE
Author: Areesh Nadeem
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Implementations for the Solar System class that allows 
///        collection of and interaction with Celestial objects.
///        Utilized as part of the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

#include "solarsystem.h"
#include "celestial.h"

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.


// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

// Constructor
SolarSystem::SolarSystem(const string &name) {
    this->name = name;
}

string SolarSystem::getName() const { return name; }

vector<shared_ptr<Celestial>> SolarSystem::getCelestialBodies() const {
    return celestialBodies;
}

void SolarSystem::setName(const string &name) { this->name = name; }        
void SolarSystem::clearConnections() { connections.clear(); }

// Inserts a new celestial to the <celestialBodies> vector.
void SolarSystem::insertCelestial(shared_ptr<Celestial> &newC) {

    // Check to see if the celestial is null or is already in vector
    if (newC != nullptr && (celestialsSearch(Star({},{},{},{}), newC->getName()) == -1)) {
        celestialBodies.push_back(newC);
    }
}

// Returns a ptr to a Celestial at the specified index
// Returns nullptr if it doesn't exist
shared_ptr<Celestial> SolarSystem::getCelestialAt(int ind) {
    if (ind >= 0 && ind < static_cast<int>(celestialBodies.size())) {
        return celestialBodies.at(ind);
    }
    else return nullptr;
}

// Adds a system connection to <connections> vector
// Checks to see if it already in vector
void SolarSystem::addConnection(const shared_ptr<SolarSystem> &con) {
    if (con != nullptr && (find(connections.begin(), connections.end(), con) == connections.end())) {
        connections.push_back(con);
    }
}

int SolarSystem::numCelestialBodies() const {
    return celestialBodies.size();
}
        
int SolarSystem::numConnections() const {
    return connections.size(); 
}

int SolarSystem::numPlanets() const {
    int count = 0;

    for (const auto& e : celestialBodies) {
        // use dynamic pointer casting to see if object is of type Planet
        shared_ptr<Planet> planet = dynamic_pointer_cast<Planet>(e);

        if (planet != nullptr) { count++; }
    }

    return count;
}

int SolarSystem::numStars() const {
    int count = 0;

    for (const auto& e : celestialBodies) {
        // use dynamic pointer casting to see if object is of type Star
        shared_ptr<Star> star = dynamic_pointer_cast<Star>(e);

        if (star != nullptr) { count++; }
    }

    return count;
}

int SolarSystem::numSatellites() const {
    int count = 0;

    for (const auto& e : celestialBodies) {
        // use dynamic pointer casting to see if object is of type Planet
        shared_ptr<Planet> planet = dynamic_pointer_cast<Planet>(e);

        if (planet != nullptr) { count += planet->numSats(); }
    }

    return count;

}

// Determines whether specified connection with provided name exists
// Returns true if present, false otherwise
bool SolarSystem::connectionExists(const string &name) const {
    bool exists = false;
    for (auto const& e : connections) {
        if (e->getName() == name) { exists = true; }
    }

    return exists;
}

// Converts Solar Systems connections to string
string SolarSystem::connectionsToString() const {
    string output;
    output += '{';
    for (size_t i = 0; i < connections.size(); i++) {
        if (i == connections.size() - 1) {
            output += connections.at(i)->getName();
            break;
        }
        output += connections.at(i)->getName() + ", ";
    }
    output += '}';
    return output;
}

// Converts Solar System to a string containing all 
// of its Celestial bodies, with newline after each output
string SolarSystem::toString() const {
    string output;

    output += name;
   
    for (auto const& e : celestialBodies) {
        output += "\n  " + e->toString();
    }
    return output;
}