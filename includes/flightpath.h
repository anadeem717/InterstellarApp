/// @file flightpath.h
/// @author Adam T Koehler, PhD
/// @date April 9, 2024
/// @brief Flight path objects store a series of points to
///        Solar Systems as a potential pathway through the stars.
///        Utilized by the Interstellar Travel App.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

///
/// DO NOT MODIFY CLASS DECLARATIONS
///

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "solarsystem.h"

using namespace std;

class FlightPath
{    
    private:
        // Collection of pointers to Solar System objects to create
        // a pathway through the stars.
        vector<shared_ptr<SolarSystem>> path;


    public:                 
        // Create a path through user input. Once complete, the path
        // data member contains the valid Solar Systems entered.
        // Contains console output and input via getline.
        // Invalid Solar Systems are not added to the path, for this function
        // invalid systems are those that do not exist in the data set.
        void createPath(const vector<shared_ptr<SolarSystem>> &systems);
                
        // Utilizes the Solar System connections to determine whether
        // we can successfully navigate along the stored path from the
        // first system to the last system to determine whether our
        // path is a valid pathway through the stars.
        bool isValid(const vector<shared_ptr<SolarSystem>> &systems) const;        
        
        // return the private data member
        vector<shared_ptr<SolarSystem>> getPath() const;

        // Convert to string containing names of systems
        // e.g. A path with A, B, and C the string is A -> B -> C
        string toString() const;

        // Creates a human readable string of everything we see on our journey.
        // The returned string has all Celestial objects on path using
        // the various object's member functions with a newline
        // between each system but none at the end.
        string toStringAll() const;

        // Convert path's Solar System connections to a string
        // One example with path A, B, C could produce a string:
        // A -> {}
        // B -> {A, C}
        // C -> {B}
        // The last line does not contain a newline.
        string connectionsString() const;


        // Output various generated strings to console followed by newline
        // Outputs "(empty path)" when the path data member is empty
        void printPath() const;        
        void printPathCelestials() const;
        void printConnections() const;


        // clear the path and reset to empty
        void clear();


        // Extra Credit - bool generatePath(...)
        // This requires a bit of thought to successfully navigate
        // all the data and not end up in infinite loops or infinite recursion.     

        /// @brief Acquire a starting system and an ending system.
        ///        Then automatically generate a path from start to end.
        /// @param systems The data vector of Solar Systems
        /// @return true when a path was generated, otherwise false
        bool generatePath(const vector<shared_ptr<SolarSystem>> &systems);


    private:
        /// @brief Determine the first index value within the container 
        ///        for the Solar System with the provided name. 
        /// @param v the container to iterate over
        /// @param name the name to look for
        /// @return the index value if found, otherwise -1
        int systemIndex(const auto &v, string name) const
        {
            int index = 0;
            for (const auto &e : v)
            {
                shared_ptr<SolarSystem> p(dynamic_pointer_cast<SolarSystem>(e));
                if (p != nullptr && p->getName() == name)
                {
                    return index;
                }    
                index++; 
            }
            return -1;
        }

};