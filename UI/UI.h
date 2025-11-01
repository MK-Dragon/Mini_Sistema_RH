// UI/UI.h

#pragma once
#include "../Model/Employee.h"
#include "../Model/Dates.h"
#include "../Utils/Calendar.h"

#include <string>
#include <iostream>
#include <conio.h> // Header for _getch()
#include <vector>

#include <iomanip>
#include <algorithm> // Required for std::find_if
#include <optional> // Requires C++17, but is the cleanest way to return a marker

#include <cstdlib>
void clearScreenANSI() {
    // \033[2J clears the screen, \033[1;1H moves the cursor to the top-left (row 1, column 1)
    std::cout << "\033[2J\033[1;1H";
    //std::cout << "\n\n\n" << std::endl;
}



// Main Menu
void printMainMenu(){
    clearScreenANSI();

    // Header
    std::cout << "* Main Menu *" << std::endl;

    // Options
    std::cout << "(1) List Employees " << std::endl;
    std::cout << "(2) Add Employee" << std::endl;

    std::cout << "(3) Mark Vacation" << std::endl;
    std::cout << "(4) Remove Vacation" << std::endl;

    std::cout << "(5) Mark absences" << std::endl;
    std::cout << "(6) Remove absences" << std::endl;

    std::cout << "(7) Employee's Monthly Calendar" << std::endl;

    // Exit
    std::cout << "(0) Exit" << std::endl;
    std::cout << "\t> "; // for user input
}



// Add Employee
void printAddEmployee_name(){
    clearScreenANSI();
    std::cout << "* Add Employee *" << std::endl;
    std::cout << "Name: "; // for user input
}
/*void printAddEmployee_birthday(){
    clearScreenANSI();
    std::cout << "* Add Employee *" << std::endl;
    std::cout << "Birthday [d-m-y]: "; // for user input
}
void printAddEmployee_phone(){
    clearScreenANSI();
    std::cout << "* Add Employee *" << std::endl;
    std::cout << "Phone: "; // for user input
}*/



// List Employees
void printEmployees(std::vector <Employee> emp_list){
    for (int i = 0; i < emp_list.size(); i++) {
        std::cout << i << ") Name: " << emp_list[i].name
                  //<< "\tYear: " << emp_list[i].year
                  << "\n";
    }
}
void printListOfEmployees(std::vector <Employee> emp_list){
    clearScreenANSI();
    std::cout << "* List of Empoyees *" << std::endl;
    printEmployees(emp_list);    
}



// ASK generic:
void printEnterValue(std::string title, std::string ask){
    clearScreenANSI();

    std::cout << "* " << title << " *" << std::endl;
    std::cout << "\t" << ask << ": "; // for user input
}



// Choose Employee:
void printChooseEmployee(std::string title, std::vector <Employee> emp_list){
    clearScreenANSI();

    std::cout << "* " << title << " *" << std::endl;
    printEmployees(emp_list);
    std::cout << "\tEmployee number: "; // for user input
}

// Choose Day:
void printChooseDay(std::string title){
    clearScreenANSI();
    
    std::cout << "* " << title << " *" << std::endl;
    std::cout << "\tDate (dd-mm-yyyy): "; // for user input
}




// Draw Calender

/*std::optional<char> get_day_marker(
    const std::vector<Date>& vacations, 
    const std::vector<Date>& absences, 
    int day_to_check
) {
    // Check for Vacation first
    if (std::find_if(vacations.begin(), vacations.end(), 
        [day_to_check](const Date& d) {
            return d.day == day_to_check;
        }) != vacations.end()) 
    {
        return 'V'; // Using 'V' as a default marker for Vacation
    }
    
    // Check for Absence second
    if (std::find_if(absences.begin(), absences.end(), 
        [day_to_check](const Date& d) {
            return d.day == day_to_check;
        }) != absences.end()) 
    {
        return 'A'; // Using 'A' as a default marker for Absence
    }
    
    // Day is not marked in either list
    return std::nullopt;
}*/








// --- Main Calendar Function (Modified) ---
void printCalendarMarked(
    const std::string& month_name, 
    int days_in_month, 
    int start_day_of_week, // 0 = Domingo, 6 = Sábado
    
    // NEW PARAMETERS for two sets of dates and their markers
    const std::vector<Date>& vacations, 
    char vacation_marker,
    const std::vector<Date>& absences, 
    char absence_marker
) {
    // ... (Input validation omitted for brevity)

    // 1. Print the Month Title
    std::cout << "\n-----------------------------\n";
    std::cout << std::setw(20) << std::right << month_name << "\n";
    std::cout << "-----------------------------\n";

    // 2. Print Weekday Headers
    std::cout << "Sun Mon Tue Wed Thu Fri Sat\n";

    // 3. Print the Empty Spacing
    for (int i = 0; i < start_day_of_week; ++i) {
        std::cout << "    "; 
    }

    // 4. Print the Days
    int current_day_of_week = start_day_of_week;

   for (int day = 1; day <= days_in_month; ++day){
        // Check for a marker in either list
        char marker = ' '; // Default to space
        
        // Check Vacation list
        //if (vacations.size() == 0)
        //{
            // just look cute ^_^  and Please don't Crash
        //}
        //else 
        if (std::find_if(vacations.begin(), vacations.end(), 
            [day](const Date& d) { return d.day == day; }) != vacations.end()) 
        {
            marker = vacation_marker;
        } 
        // Check Absence list (ONLY if not already a Vacation. If a day can be BOTH, 
        // you need a more complex system, like a char for each, e.g., 'VA')
        else if (std::find_if(absences.begin(), absences.end(), 
            [day](const Date& d) { return d.day == day; }) != absences.end()) 
        {
            marker = absence_marker;
        }

        // Print the day number and marker
        // Using setw(2) for the day, and then printing the marker and an alignment space
        std::cout << std::setw(2) << day;
        if (marker != ' ') {
            std::cout << marker << " "; // Marker + 1 space
        } else {
            std::cout << "  "; // 2 spaces to maintain column width
        }
        
        // Move to the next day of the week
        current_day_of_week++;

        // If we reach the end of the week (Saturday), start a new line
        if (current_day_of_week % 7 == 0) {
            std::cout << "\n";
            current_day_of_week = 0; // Reset to Sunday (0)
        }
    }

    // 5. Final Formatting
    std::cout << "\n-----------------------------\n";
}





// General Use
void showPressAnyKey(){
    std::cout << "\nPress Any Key to Continue" << std::endl;
    char key = _getch();
}

void showError(std::string errorTitle, std::string errorMessage)
{
    std::cout << "🚨 " << errorTitle << " 🚨" << std::endl;
    std::cout << errorMessage << std::endl;
    showPressAnyKey();
}