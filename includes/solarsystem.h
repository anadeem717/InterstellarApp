/// @file solarsystem.h
/// @author Adam T Koehler, PhD
/// @date April 9, 2024
/// @brief Solar System class that allows collection of and interaction with
///        Celestial objects as part of the Interstellar Travel App.

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
#include "celestial.h"

using namespace std;

class SolarSystem
{ 
    private:
        string name;

        // Collection of Celestial objects that exist within this Solar System
        vector<shared_ptr<Celestial>> celestialBodies;

        /// One-way destinations, aka connections, to other Solar Systems that
        /// can be traveled to from this Solar System
        vector<shared_ptr<SolarSystem>> connections;        

    public:
        // we only allow fully parameterized construction of object
        SolarSystem(const string &);
        
        // accessors or getters
        string getName() const;               
        vector<shared_ptr<Celestial>> getCelestialBodies() const;

        // Acquire a pointer to a Celestial object at a specific
        // index in the private data member celestialBodies
        shared_ptr<Celestial> getCelestialAt(int ind);


        // mutators or setters
        void setName(const string &);        
        void clearConnections();

        // Add a Celestial pointer to the back of private 
        // data member celestialBodies.
        void insertCelestial(shared_ptr<Celestial> &newC);

        // Add a Solar System pointer to the back of private data member
        // connections. Every connection is a potential pathway out of 
        // this Solar System and into another!
        void addConnection(const shared_ptr<SolarSystem> &con);
                

        // informational about data members               
        int numCelestialBodies() const;
        int numConnections() const;

        // counts for direct contents of celestialBodies
        int numPlanets() const;
        int numStars() const;

        // Counts the number of Satellites that are orbiting Planets
        // Satellites are not stored in celestialBodies data member directly,
        // but they are stored within the Planet object they orbit. Therefore
        // they can be counted similarly to Planets and Stars but not directly.
        int numSatellites() const;

        // Dermine whether specified connection with provided name exists
        // e.g. A->B is only connection, calling with "B" will result in true
        //      A->B is only connection, calling with "C" will result in false
        bool connectionExists(const string &name) const;           

        // convert Solar System to a readable multi-line string
        // containing all of its Celestial bodies contained
        // directly or indirectly in the private data member
        string toString() const;

        // convert Solar Systems connections to string
        // {con1_name, con2_name, ...}
        string connectionsToString() const;


        /// @brief Templated search of the private data member
        ///        that allows searching for a specifed object type.
        ///        The search returns the first (lowest) index that matches
        ///        the desired search name. Returns -1 when the search fails.
        /// @param obj a dummy object of the type to search for
        /// @param name a string containing the name to search for
        /// @return the index of the search for object within the private data
        ///         member vector celestialBodies or -1 when the search fails
        template<typename T>    
        int celestialsSearch(T obj, const string &name) const
        {
            int index = 0;
            for (const auto &e : celestialBodies)
            {
                shared_ptr<T> p(dynamic_pointer_cast<T>(e));
                if (p != nullptr && p->getName() == name)
                {
                    return index;
                }    
                index++; 
            }
            return -1;
        }
};