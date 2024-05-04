/// @file celestials.h
/// @author Adam T Koehler, PhD
/// @date April 9, 2024
/// @brief Celestial base class and derived Celestial Object Classes
///        utilized by the Interstellar Travel App.

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

using namespace std;

// No objects of this base class should exist within the 
// Interstellar Travel App. It allows collecting pointers of derived classes.
class Celestial
{ 
    private:

    protected:    
        string name;
    
    public:        
        Celestial(const string &);
        virtual ~Celestial();

        // final virtual function cannot be overriden in derived class
        virtual string getName() const final;  

        // pure virtual function must be overriden in derived class     
        virtual string toString() const = 0;
};


// The Star class is derived from the Celestial class
class Star : public Celestial
{    
    private:
        // solar mass (mass relative to the sun)        
        double mass;

        // Star temperature in Kelvins
        double temperature;        

        // the spectral classification or type
        string spectralType;

    public:  
        // we only allow fully parameterized construction of object
        Star(const string& name, const string &spectralType, 
             double temperature, double mass);             
        virtual ~Star();

        double getMass() const;
        double getTemperature() const;
        string getSpectralType() const;
        
        void setMass(double);
        void setTemperature(double);
        void setSpectralType(const string &);
        
        // converts the details of the object to a string
        // not newline terminated
        virtual string toString() const override;
};


// The Planet class is derived from the Celestial class
class Planet : public Celestial
{
    private:
        double orbitalPeriod;
        double radius;

        // vector of pointers to Celestials that are orbiting this Planet
        vector<shared_ptr<Celestial>> sats;

    public:       
        // we only allow fully parameterized construction of object
        Planet(const string& name, double orbitP, double radius);
        virtual ~Planet();

        double getOrbitalPeriod() const;
        double getRadius() const;
        int numSats() const;

        void setOrbitalPeriod(double);
        void setRadius(double);

        // Add a pointer to a Celestial object to the orbit of this Planet
        // by inserting it at the back of the vector that collects all 
        // Celestials that orbit this planet
        void addSat(shared_ptr<Celestial> &);   

        // Search the collection of Celestials orbiting the Planet to
        // determine whether an object with the supplied name exists
        // in the collection. True when found, otherwise false.
        bool satExists(const string &name) const;

        // Output each element of sat's string of details to the console
        // each element's string is followed by a newline (on its own line)
        void printSats() const; 
        
        // Convert this planet and its details to a human readable string
        // Each Celestial in orbit is also added to the string, one per line
        // The string may have newlines internally but is not newline terminated.
        virtual string toString() const override;      
};


// The Satellite class is derived from the Celestial class
class Satellite : public Celestial
{
    private:
        // is the satellite natural or human made?        
        bool natural;

        // radius relative to Earth
        double radius;        
    
    public:   
        // we only allow fully specified object creation      
        Satellite(const string&, double, bool);
        virtual ~Satellite();

        bool isNatural() const;
        double getRadius() const;

        void setNatural(bool);
        void setRadius(double);

        // Convert this Satellite and its details to a human readable string. 
        // The string is not newline terminated.
        virtual string toString() const override;

};

// DO NOT REMOVE - USED IN GRADING
#include "celestials_more.h"
