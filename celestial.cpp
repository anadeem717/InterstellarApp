/// @file celestials.cpp
/// @author Adam T Koehler, PhD
/// @date April 9, 2024
/// @brief Celestial base class implementations. 
///        Utilized by the Interstellar Travel App.

// ============================================================
// Nothing to do in this file, it is provided in completed form
// as a reference on how to implement C++ class implementation
// files and how to use doxygen style function commenting.
// ============================================================

#include <string>
#include "celestial.h"

/// @brief Create a Celestial object specifying values for all private
///     data members of the class. Invoked within initalization lists
///     of constructors for derived classes.
/// @param n the value to set the private data member name to
Celestial::Celestial(const string &n)
{
    name = n;
}

/// @brief obtain the name of this Celestial object
/// @return the private data member string containing the name
string Celestial::getName() const 
{
    return name;
}

/// @brief Empty destructor required for polymorphic pointers
Celestial::~Celestial() { }