/// @file star.cpp

/*-------------------------------------------
Project 6: Star Class CPP File
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE
Author: Areesh Nadeem
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Star derived class from Celestial base class.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// All the headers you need!
#include <string>
#include "celestial.h"

using namespace std;

// Local Helper Functions
// If you were allowed to change the the .h files many, if not all,
// of these would go into a private section of the class declaration.





// Class Implementations
// Defining all functions from the header that are not already
// fully defined within the header and class declaration.

// Fully qualified Constructor
Star::Star(const string& name, const string &spectralType, double temperature, double mass) : Celestial(name) {
    this->spectralType = spectralType;
    this->temperature = temperature;
    this->mass = mass;
}

Star::~Star() { }

// Returns Star info as a string
string Star::toString() const { 
    return "Star " + name + " of type " + spectralType + " with temperature " + to_string(temperature) + " and mass " + to_string(mass); 
}

// Getters for Star data
double Star::getMass() const { return mass; }
double Star::getTemperature() const { return temperature; }
string Star::getSpectralType() const { return spectralType; }

// Setters for Star data
void Star::setMass(double mass) { this->mass = mass; }
void Star::setTemperature(double temperature) { this->temperature = temperature; }
void Star::setSpectralType(const string &spectralType) { this->spectralType = spectralType; }