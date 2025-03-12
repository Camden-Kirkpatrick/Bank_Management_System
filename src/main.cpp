#include "../include/utilities.hpp"
#include "../include/global.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <string>

i32 main()
{
    // A container to hold all the banks in the system
    std::vector<std::unique_ptr<Bank::Bank>> banks;

    bool is_running = true;
    int choice = 0;

    std::cout << R"(

______                _          ___  ___                                                           _   
| ___ \              | |         |  \/  |                                                          | |  
| |_/ /  __ _  _ __  | | __      | .  . |  __ _  _ __    __ _   __ _   ___  _ __ ___    ___  _ __  | |_ 
| ___ \ / _` || '_ \ | |/ /      | |\/| | / _` || '_ \  / _` | / _` | / _ \| '_ ` _ \  / _ \| '_ \ | __|
| |_/ /| (_| || | | ||   <       | |  | || (_| || | | || (_| || (_| ||  __/| | | | | ||  __/| | | || |_ 
\____/  \__,_||_| |_||_|\_\      \_|  |_/ \__,_||_| |_| \__,_| \__, | \___||_| |_| |_| \___||_| |_| \__|
                                                                __/ |                                   
                                                               |___/                                    
                          _____              _                                                          
                         /  ___|            | |                                                         
                         \ `--.  _   _  ___ | |_   ___  _ __ ___                                        
                          `--. \| | | |/ __|| __| / _ \| '_ ` _ \                                       
                         /\__/ /| |_| |\__ \| |_ |  __/| | | | | |                                      
                         \____/  \__, ||___/ \__| \___||_| |_| |_|                                      
                                  __/ |                                                                 
                                 |___/                                                                          
                                                                                                                                                        
                                                                                               
                                                                                                  
    )" << "\n";

    // Run the main loop, showing menu options until the user exits
    do
    {
        DisplayMenu(choice, is_running, banks);
    } while (is_running);

    std::cout << "Goodbye!" << std::endl;

    return 0;
}
