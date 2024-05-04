/// @file satellite.cpp

/*-------------------------------------------
Project 6: Satellite Class CPP File
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE
Author: Areesh Nadeem
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief Satellite derived class from Celestial base class.
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
Satellite::Satellite(const string& name, double radius, bool natural) : Celestial(name) {
    this->radius = radius;
    this->natural = natural;
}

Satellite::~Satellite() { }

// Returns a string consisting of info for Satellite
string Satellite::toString() const { 
    if (natural) {
        return "Satellite " + name + " is natural with radius of " + to_string(radius); 
    }
    else {
        return "Satellite " + name + " is human made with radius of " + to_string(radius); 
    }
}

// Getters for Satellite Data
bool Satellite::isNatural() const { return natural; }
double Satellite::getRadius() const { return radius; }

// Setters for Satellite Data
void Satellite::setNatural(bool natural) { this->natural = natural; }
void Satellite::setRadius(double radius) { this->radius = radius; }