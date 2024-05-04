/// @file project_utils.cpp
/// @author Adam T Koehler, PhD
/// @date April 9, 2024
/// @brief Provided utility functions to use during project implementation.

// Copyright Notice
// This document is protected by U.S. copyright law. Reproduction and 
// distribution of this work, including posting or sharing through any medium, 
// is explicitly prohibited by law, and also violates UIC's Student 
// Disciplinary Policy (A2-c. Unauthorized Collaboration; and A2-e3. 
// Participation in Academically Dishonest Activities: Material Distribution).


// =============================//
//  Nothing to do in this file. //
// =============================//

#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "project_values.h"

using namespace std;

/// @brief Sleep for animation based on project animation setting value.
void animate()
{
    if (ANIMATE == 1)
    {
        usleep(SLEEP_USEC);
    }
}

/// @brief Clear the console screen or output two newlines based on
///        the project setting for clearing the screen.
void clearScreen()
{
    if (CLEAR_SCREEN == 1)
    {
        printf("\033[H");
    }
    else
    {
        printf("\n\n");
    }
}

/// @brief Print out the application welcome message
/// ASCII art adapted from generator: https://patorjk.com/software/taag/
void welcomeSplash(bool show)
{
    if (show)
    {
        /*
           ___        __                        __          __   __                
          |   | _____/  |_  ___________  ______/  |_  ____ |  | |  | _____ _______ 
          |   |/    \   __\/ __ \_  __ \/  ___|   __\/ __ \|  | |  | \__  \\_  __ \
          |   |   |  \  | \  ___/|  | \/\___ \ |  | \  ___/|  |_|  |__/ __ \|  | \/
          |___|___|  /__|  \___  >__|  /____  >|__|  \___  >____/____(____  /__|   
                   \/          \/           \/           \/               \/       
          ___________                          __      _      _____                      
          \__    ___/___________ ___  __ ____ |  |    /O\    /  _  \ ______ ______       
            |    |  \_  __ \__  \\  \/ // __ \|  |   (___)  /  /_\  \\____ \\____ \      
            |    |   |  | \// __ \\   /\  ___/|  |__   V   /    |    \  |_> >  |_> >     
            |____|   |__|  (____  /\_/  \___  >____/   V   \____|__  /   __/|   __/      
                                \/          \/                     \/|__|   |__|         
        */      
        vector <string> titles;
        titles.push_back("  ___        __                        __          __   __");
        titles.push_back(" |   | _____/  |_  ___________  ______/  |_  ____ |  | |  | _____ _______");
        titles.push_back(" |   |/    \\   __\\/ __ \\_  __ \\/  ___|   __\\/ __ \\|  | |  | \\__  \\\\_  __ \\");
        titles.push_back(" |   |   |  \\  | \\  ___/|  | \\/\\___ \\ |  | \\  ___/|  |_|  |__/ __ \\|  | \\/");
        titles.push_back(" |___|___|  /__|  \\___  >__|  /____  >|__|  \\___  >____/____(____  /__|   ");
        titles.push_back("          \\/          \\/           \\/           \\/               \\/");
        titles.push_back(" ___________                         __      _      _____");
        titles.push_back(" \\___   ___/__________ ___  __ ____ |  |    /O\\    /  _  \\ ______ ______");
        titles.push_back("    |   | \\_  __ \\__  \\\\  \\/ // __ \\|  |   (___)  /  /_\\  \\\\____ \\\\____ \\");
        titles.push_back("    |   |  |  | \\// __ \\\\   /\\  ___/|  |__   V   /    |    \\  |_> >  |_> >");
        titles.push_back("    |___|  |__|  (____  /\\_/  \\___  >____/   V   \\____|__  /   __/|   __/");
        titles.push_back("                      \\/          \\/                     \\/|__|   |__|");
                                                                                                                                         
        size_t max = 0;
        for(const auto &e : titles)
        {
            if (max < e.size())
            {
                max = e.size();
            }
        }

        for(size_t i=0; i <= max; ++i)
        {
            clearScreen();

            for (const auto &e : titles)
            {
                cout << e.substr(0,i) << endl;
            }

            animate();
        }

        string option;
        cout << endl << endl << "...(ENTER) to continue..." << endl << endl;
        getline(cin, option);
    }
    else
    {
        cout << "Welcome to the Interstellar Travel App" << endl;
        cout << "======================================" << endl;
    }
}
