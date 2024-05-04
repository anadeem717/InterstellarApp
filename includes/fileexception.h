/// @file fileexception.h
/// @author Adam T Koehler, PhD
/// @date April 9, 2024
/// @brief File exception class that is derived from the exception class. 
///     This class allows us to override the what() method for this class  
///     and throw exceptions with a specific string message specified during 
///     object creation.

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

#include <exception>
#include <string>

using namespace std;

// The FileException class is derived from the exception class
class FileException : public exception 
{
    private: 
        string message;

    public:
        /// @brief Create a FileException with the specific message
        /// @param msg the message string to display
        FileException(string msg) : message(msg) {}

        /// @brief Overriding the what() method of exception class
        ///        to allow returning of our stored message string.
        /// @return the message data member as a C-string
        const char* what() const throw() override 
        { 
            return message.c_str(); 
        }
};