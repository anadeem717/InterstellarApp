/// @file interstellar.cpp
/// @date 

/*-------------------------------------------
Project 6: Interstellar Travel App
Course: CS 211, Spring 2024, UIC
System: ZyLabs IDE
Author: Areesh Nadeem
------------------------------------------- */

/// Original project documents by Adam T Koehler, PhD
/// UIC CS211 Spring 2024
/// @brief An object oriented terminal program that allows reading of
///        Celestial data files to plan flights between the Solar Systems.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).

// These are all the libraries you need!
#include <algorithm>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

// CS 211 Spring 2024 Project Specific Header Files
#include "celestial.h"
#include "solarsystem.h"
#include "fileexception.h"
#include "flightpath.h"

using namespace std;

// Externally define welcome message function
extern void welcomeSplash(bool);

// Local Function Prototypes
string acquireOption();
void printMenu();
bool validChoice(const string &);

void readObjectsData(vector<shared_ptr<SolarSystem>>& systems); 

void createNewStar(shared_ptr<SolarSystem>& newSys, string name, string system, 
                   string specType, string temp, string mass, vector<shared_ptr<SolarSystem>>& systems);

void createNewPlanet(shared_ptr<SolarSystem>& newSys, string name, string starName, 
                     string sysName, string orbPeriod, string radius, vector<shared_ptr<SolarSystem>>& systems);

void createNewSat(shared_ptr<SolarSystem>& newSys, string name, string planetName, string sysName, 
                  string radius, string naturalString, vector<shared_ptr<SolarSystem>>& systems);

void readSystemConnectionsData(vector<shared_ptr<SolarSystem>>& systems);
shared_ptr<SolarSystem> systemExists(vector<shared_ptr<SolarSystem>>& systems, const string& name);
shared_ptr<SolarSystem> createSolarSystem(const string& name, vector<shared_ptr<SolarSystem>>& systems);
void printCelestialDetails(vector<shared_ptr<SolarSystem>>& systems);
void printConnectionDetails(vector<shared_ptr<SolarSystem>>& systems);
void printLoadedStats(vector<shared_ptr<SolarSystem>>& systems);
void validateFlightPath(const FlightPath& path, vector<shared_ptr<SolarSystem>>& systems);
void printFlightPath(const FlightPath& path);
void printPathConnections(const FlightPath& path);
void printPathObjects(const FlightPath& path);
void clearPathData(FlightPath& path);
void clearSystemConnections(vector<shared_ptr<SolarSystem>>& systems);
void clearSystemData(vector<shared_ptr<SolarSystem>>& systems);
void planPath(FlightPath& path, vector<shared_ptr<SolarSystem>>& systems);

int main(int argc, char* argv[])
{ 
    // Command line argument flags   
    bool showSplash = false;
    bool hideMenu = false;

    // Vector of shared pointers to Solar Systems
    vector<shared_ptr<SolarSystem>> systems;

    // Flight path through the Solar Systems
    FlightPath path;

    // DONE: Determine whether -splash or -hidemenu command line argument exists.
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-splash") == 0) { showSplash = true; }
        else if (strcmp(argv[i], "-hidemenu") == 0) { hideMenu = true; }
    }
    
    // Display the welcome splash or the simple one depending on settings
    welcomeSplash(showSplash);

    // Acquire user option from menu
    string option;
    if (!hideMenu)
    {
        printMenu();    
    }
    option = acquireOption(); 

    while (option != "15")
    {
        if (validChoice(option))
        {                           
            switch (stoi(option))
            {

                case 1:
                    readObjectsData(systems);  
                    break;
                    
                case 2:
                    readSystemConnectionsData(systems);
                    break;

                case 3:
                    printCelestialDetails(systems); 
                    break;

                case 4:
                    printConnectionDetails(systems);
                    break;

                case 5:
                    printLoadedStats(systems);
                    break;

                case 6:
                    planPath(path, systems);
                    break;

                case 7:
                    validateFlightPath(path, systems);
                    break;

                case 8:
                    printFlightPath(path);
                    break;

                case 9:
                    printPathConnections(path);
                    break;

                case 10:
                    printPathObjects(path);
                    break;

                case 11:
                    clearPathData(path);
                    break; 

                case 12:
                    clearSystemConnections(systems);
                    break;

                case 13:
                    clearSystemData(systems);
                    break;           

                // exit the application
                case 15: 
                    return 0;

                // invalid choice, do nothing 
                default:
                    break;    
            }
        }

        cout << endl;
        if (!hideMenu)
        {
            printMenu();
        }
        option = acquireOption();        
    }

    cout << endl << "Thank you for using the Interstellar Travel App." 
        << endl << endl;

    return 0;
}


/// @brief acquire user menu choice
/// @return acquried string value
string acquireOption()
{
    string option;
    
    cout << endl << "Enter a selection: ";
    getline(cin, option);
    cout << endl;

    return option;
}


/// @brief prints out the contents of menu.txt
void printMenu()
{
    ifstream inFS;
    string line; 
    inFS.open("menu.txt");

    while(getline(inFS, line)) {
        cout << line << endl;
    }

    inFS.close(); 
}


/// @brief Determines whether a provided string meets the criteria.
///        Valid choices are size 1 or 2 and must be all numeric digits.
/// @param choice the string to validate 
/// @return true when the choice is valid
bool validChoice(const string &choice)
{
    int size = choice.size();

    if (size != 1 && size != 2) { return false; }

    // must be all digits
    for (int i = 0; i < size; i++) {
        if (!isdigit(choice[i])) { return false; }
    }

    return true; // string valid, no alpha, size is 1 or 2
}

// Reads a Celestial Objects data file and parses it
// to add all celestial objects with their data into corresponding
// Solar Systems and types. 
void readObjectsData(vector<shared_ptr<SolarSystem>>& systems) { 
    try {

        // get file
        string filename;
        ifstream inFS;
        cout << "Enter the file location and name:\n";
        getline(cin, filename);
        cout << endl; 

        inFS.open(filename);
        if (!inFS.is_open()) { 
            throw FileException("Exception Caught: File Not Found - " + filename);
        }

        string data;
        shared_ptr<SolarSystem> newSys; // the solar system to add objects to

        while (getline(inFS, data)) {
            // if its an empty line or comment, skip
            if (data[0] == '#' || data.empty()) { continue; }

            // if no comma -> bad line, so throw exception
            if (data.find(",") == string::npos) {
                throw FileException("Exception Caught: Bad Data Line - No Comma Found: " + data);
            }

            // use string stream to parse data
            stringstream stream(data);
            string celestial; 
            getline(stream, celestial, ','); 

            // Case create a new SolarSystem
            if (celestial == "System") {
                string name;
                getline(stream, name, ',');

                if (name.empty()) { 
                    throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + data);
                }

                // if the system already exists, do nothing
                // else, add it to the systems vector
                newSys = systemExists(systems, name);
                if (newSys == nullptr) {
                    newSys = createSolarSystem(name, systems); 
                }
               
            }

            // Case create a new Star 
            else if (celestial == "Star") {
                string name, sysName, specType, temp, mass; 
                getline(stream, name, ',');
                getline(stream, sysName, ',');
                getline(stream, specType, ',');
                getline(stream, temp, ',');
                getline(stream, mass, ',');

                // if data not formatted correctly
                if (name.empty() || sysName.empty() || specType.empty() || 
                    temp.empty() || mass.empty()) { 
                    throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + data);
                }

                createNewStar(newSys, name, sysName, specType, temp, mass, systems); 

            }

            // Case create a new planet
            else if (celestial == "Planet") {
                string name, starName, sysName, orbPeriod, radius;
                getline(stream, name, ',');
                getline(stream, starName, ',');
                getline(stream, sysName, ',');
                getline(stream, orbPeriod, ',');
                getline(stream, radius, ',');

                // if data not formatted correctly
                if (name.empty() || sysName.empty() || starName.empty() || 
                    orbPeriod.empty() || radius.empty()) { 
                    throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + data);
                }

                createNewPlanet(newSys, name, starName, sysName, orbPeriod, radius, systems);
            }

            // Case create a new Satellite
            else if (celestial == "Satellite") {
                string name, planetName, sysName, radius, naturalString;

                getline(stream, name, ',');
                getline(stream, planetName, ',');
                getline(stream, sysName, ',');
                getline(stream, radius, ',');
                getline(stream, naturalString, ',');

                // if data not formatted correctly
                if (name.empty() || sysName.empty() || planetName.empty() || 
                    naturalString.empty() || radius.empty()) { 
                    throw FileException("Exception Caught: Bad Data Line - Mismatched Data Amount: " + data);
                }

                createNewSat(newSys, name, planetName, sysName, radius, naturalString, systems);

            }
            else { // No matching Case found
                throw FileException("Exception Caught: Bad Data Line - Invalid Celestial Type: " + data);
            }
        }
        inFS.close();
    
    }
    catch (FileException& e) {
        cout << e.what() << endl;
    }
  
}

// Creates a new Star and adds it to the corresponding solar system 
// using the data provided. If the system does not exist, we create it here
void createNewStar(shared_ptr<SolarSystem>& newSys, string name, string system, 
                   string specType, string temp, string mass, vector<shared_ptr<SolarSystem>>& systems) {

    // if the system doesn't exist, create it
    newSys = systemExists(systems, system);
    if (newSys == nullptr) {
        newSys = createSolarSystem(system, systems); 
    }
    
    shared_ptr<Celestial> newStar(new Star(name, specType, stod(temp), stod(mass)));

    newSys->insertCelestial(newStar);
}

// Creates a new Planet and adds it to the corresponding solar system 
// using the data provided. If the system does not exist, we create it here
void createNewPlanet(shared_ptr<SolarSystem>& newSys, string name, string starName, 
                     string sysName, string orbPeriod, string radius, vector<shared_ptr<SolarSystem>>& systems) {

    // if the system doesn't exist, create it
    newSys = systemExists(systems, sysName);
    if (newSys == nullptr) {
        newSys = createSolarSystem(sysName, systems); 
    }
    
    // if the star doesn't exist, create it
    if (newSys->celestialsSearch(Star({},{},{},{}), starName) == -1) {
        shared_ptr<Celestial> newStar(new Star(starName, {"unknown"}, {}, {}));
        newSys->insertCelestial(newStar);
    }

    shared_ptr<Celestial> newPlanet(new Planet(name, stod(orbPeriod), stod(radius)));
    newSys->insertCelestial(newPlanet);
}

// Creates a new Satellite and adds it to the corresponding 
// system and planet using the data provided. 
// If the system/planet does not exist, we create it here
void createNewSat(shared_ptr<SolarSystem>& newSys, string name, string planetName, string sysName, 
                  string radius, string naturalString, vector<shared_ptr<SolarSystem>>& systems) {
    bool natural; 

    if (naturalString == "Yes") { natural = true; }
    else { natural = false; }

    // if the system doesn't exist, create it
    newSys = systemExists(systems, sysName);
    if (newSys == nullptr) {
        newSys = createSolarSystem(sysName, systems); 
    }

    shared_ptr<Celestial> newSat(new Satellite(name, stod(radius), natural));
    auto index = newSys->celestialsSearch(Planet({},{},{}), planetName);

    // if the planet doesn't exist, create it
    if (index == -1) {
        shared_ptr<Celestial> newPlanet(new Planet(planetName, {}, {}));
        newSys->insertCelestial(newPlanet);
    }

    // index of planet to add satellite to
    index = newSys->celestialsSearch(Planet({},{},{}), planetName);

    // get the pointer to the planet then add the sat to it
    auto planet = dynamic_pointer_cast<Planet>(newSys->getCelestialAt(index));
    planet->addSat(newSat);
}


// Reads a Solar System connections data file and parses it
// to add all connections to each Solar System
void readSystemConnectionsData(vector<shared_ptr<SolarSystem>>& systems) {
   try {
       // get file
        string filename;
        ifstream inFS;
        cout << "Enter the file location and name:\n";
        getline(cin, filename);
        cout << endl; 

        inFS.open(filename);
        if (!inFS.is_open()) { 
            throw FileException("Exception Caught: File Not Found - " + filename);
        }

        string data;
        shared_ptr<SolarSystem> startSystem;

        while (getline(inFS, data)) {
            if (data[0] == '#' || data.empty()) { continue; }

            stringstream stream(data);
            string systemName; 
            getline(stream, systemName, ',');

            // if the system doesn't exist, do nothing
            startSystem = systemExists(systems, systemName);
            if (startSystem == nullptr) { continue; }

            string nextSystemName;
            shared_ptr<SolarSystem> nextSystem;

            while (getline(stream, nextSystemName, ',')) {

                // if the nextSystem doesnt exist, do nothing
                nextSystem = systemExists(systems, nextSystemName);

                if (nextSystem == nullptr) { continue; }

                // else add the connection to the starting system
                startSystem->addConnection(nextSystem); 
            }
        }
        inFS.close(); 
   }
   catch (FileException& e) {
        cout << e.what() << endl;
    }
}

// Checks if a system exists in the <systems> vector.
// Returns true if it already exists, false if it doesn't
shared_ptr<SolarSystem> systemExists(vector<shared_ptr<SolarSystem>>& systems, const string& name) {
    for (auto const& e : systems) {
        if (e->getName() == name) { return e; }
    }
    return nullptr;
}

// creates a new SolarSystem object using a shared_ptr and adds it to <systems> 
// returns the new system that is created
shared_ptr<SolarSystem> createSolarSystem(const string& name, vector<shared_ptr<SolarSystem>>& systems) {
    shared_ptr<SolarSystem> newSys(new SolarSystem(name));
    systems.push_back(newSys); 

    return newSys; 
}

// Prints all celestials for each system in <systems>
void printCelestialDetails(vector<shared_ptr<SolarSystem>>& systems) {
    if (systems.size() == 0) { cout << "No data loaded.\n"; }

    for (size_t i = 0; i < systems.size(); i++) {
        auto bodies = systems.at(i)->getCelestialBodies();
        cout << systems.at(i)->getName() << endl;  

        for (size_t j = 0; j < bodies.size(); j++) {
            auto sat = dynamic_pointer_cast<Satellite>(bodies.at(j));

            // case outputting satellite
            if (sat != nullptr) {
                cout << "    " << bodies.at(j)->toString() << endl;
            }

            // case outputting star or planet
            else {
                cout << "  " << bodies.at(j)->toString() << endl; 
            }
        }
    }

}

// Prints what each system is connected to in <systems>
void printConnectionDetails(vector<shared_ptr<SolarSystem>>& systems) {
    if (systems.size() == 0) { cout << "No connections loaded.\n"; }

    for (auto const& e : systems) {
        cout << e->getName() << " -> " << e->connectionsToString() << endl; 
    }

}

// Prints stats about <systems> data to the console
void printLoadedStats(vector<shared_ptr<SolarSystem>>& systems) {

    int numStars = 0;
    int numPlanets = 0;
    int numSats = 0; 
    double totConnections = 0;
    int minConnections = 0; 
    int maxConnections = 0; 
    double avg = 0.0; 
    double medianConnection = 0.0;
    vector<double> connectionsVec; 

    if (systems.size() != 0) { 

        minConnections = systems.at(0)->numConnections(); 

        // for each item in systems, update the data values
        for (auto const& e : systems) {
            connectionsVec.push_back(e->numConnections());

            numStars += e->numStars();
            numPlanets += e->numPlanets();
            numSats += e->numSatellites(); 

            totConnections += e->numConnections(); 
            if (e->numConnections() < minConnections) {
                minConnections = e->numConnections(); 
            }
            if (e->numConnections() > maxConnections) {
                maxConnections = e->numConnections(); 
            }
        }
        avg = (totConnections / systems.size());
    }

    // calculate the median
    // median is the midpoint of a sorted list
    int size = connectionsVec.size(); 
    if (size == 1) { 
        medianConnection = connectionsVec.at(0);  
    }
    else if (size != 0) {
        
        sort(connectionsVec.begin(), connectionsVec.end());

        // if size is even
        if (size % 2 == 0) {
            medianConnection = (connectionsVec.at(size/2) + connectionsVec.at(size/2 - 1)) / 2;
        } 
        else {
            medianConnection = connectionsVec.at((size)/2);
        }
    }

    cout << "Stats for Loaded Data\n";
    cout << "=====================\n";
    cout << "Number of Solar Systems: " << systems.size() << endl;
    cout << "Number of Stars: " << numStars << endl;
    cout << "Number of Planets: " << numPlanets << endl;
    cout << "Number of Satellites: " << numSats << endl;
    cout << "Minimum Number of Connections: " << minConnections << endl;
    cout << "Maximum Number of Connections: " << maxConnections << endl;
    cout << "Average Number of Connections: " << avg << endl;
    cout << "Median Number of Connections: " << medianConnection << endl;

}

// Validates the user-inputted flight path
void validateFlightPath(const FlightPath& path, vector<shared_ptr<SolarSystem>>& systems) {
    if (path.isValid(systems)) {
        cout << "Path is valid, ready to explore!\n";
    } 
    else {
        cout << "Invalid path, route not connected.\n";
    }
}

// Prins the flight path to the console
void printFlightPath(const FlightPath& path) {
    path.printPath(); 
}

// Prints the system connections on path to console
void printPathConnections(const FlightPath& path) {
    cout << path.connectionsString(); 
}

// prints celestials on path to console
void printPathObjects(const FlightPath& path) {
    cout << path.toStringAll(); 
}

// clears the <path> vector
void clearPathData(FlightPath& path) {
    path.clear(); 
}

// Clears all system connections for each system in <systems>
void clearSystemConnections(vector<shared_ptr<SolarSystem>>& systems) {
    for (auto const& e : systems) {
        e->clearConnections(); 
    }
}

// Clears all data in <systems>
void clearSystemData(vector<shared_ptr<SolarSystem>>& systems) {
    systems.clear(); 
}

// Allows user to plan their own path through the systems
void planPath(FlightPath& path, vector<shared_ptr<SolarSystem>>& systems ) {
    path.clear(); 
    path.createPath(systems); 
}