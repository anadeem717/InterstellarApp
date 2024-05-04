/// @file planet.cpp

/*-------------------------------------------
Project 6: Planet Class CPP File
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE
Author: Areesh Nadeem
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Planet derived class from Celestial base class.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <iostream>
#include <string>
#include <vector>
#include "celestial.h"

using namespace std;

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

// Fully Qualified Constructor
Planet::Planet(const string& name, double orbitP, double radius) : Celestial(name) {
    this->orbitalPeriod = orbitP;
    this->radius = radius;
}

Planet::~Planet() { }

// Returns the number of satellites with the planet
int Planet::numSats() const {
    return sats.size();
}

// Returns a string containing info for planet
string Planet::toString() const {
    string output;
    output += "Planet " + name + " with orbital period " + to_string(orbitalPeriod) + " and relative radius of " + to_string(radius); 
    for (auto const& e : sats) {
        output += "\n    ";
        output += e->toString(); 
    }

   return output; 
}

// Getters planet data
double Planet::getOrbitalPeriod() const { return orbitalPeriod; }
double Planet::getRadius() const { return radius; }

// Setters planet data
void Planet::setOrbitalPeriod(double orbP) { this->orbitalPeriod = orbP; }
void Planet::setRadius(double rad) { this->radius = rad; }

// Adds a satellite to the <sats> vector
void Planet::addSat(shared_ptr<Celestial> &celestial) { sats.push_back(celestial); }

// Checks to see if a satellite exists in the <sats> vector
// with string <name>. Returns true if it exists, false otherwise. 
bool Planet::satExists(const string &name) const {
    for (const auto& e : sats) {
        if (e->getName() == name) { return true; }
    }
    return false;
}

// Outputs each satellite info in <sats> to the console
void Planet::printSats() const {
    for (auto const& e : sats) {
        cout << e->toString() << endl;
    }
}