// main.cpp

#include <iostream>
#include <string>

#include "Controller/HResources.h"
#include "Controller/HResources.cpp"
#include "Model/Employee.h"
#include "Model/Dates.h"
#include "UI/UI.h"
#include "Utils\CSV_Manager.h"






int main()
{
    // Loop Values
    int menu = 0; // Main menu
    std::string FILE_NAME = "db.csv";

    // Load CSV
    Load_from_CSV(FILE_NAME);
    // Check CSV


    while (menu != -1)
    {
        // Show Menu
        printMainMenu();

        // Get user input
        while (true) {
            if (!(std::cin >> menu)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a number between 0 and 5.\n";
                continue;
            }
            if (menu >= 0 && menu <= 5) break;
            std::cout << "Please enter a number between 0 and 5.\n";
        }

        // Enter Menu
        switch (menu)
        {
            case 0: // Exit
                menu = -1;
                break;

            case 1: // List Employees
                menu = 0;
                break;
            
            case 2: // Add Employees
                menu = 0;
                break;

            default:
                break;
        }
    }

    // Save to CSV and Exit
    Save_to_CSV(FILE_NAME);
    return 0;
}
