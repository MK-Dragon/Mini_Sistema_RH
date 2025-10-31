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

#include <cstdlib>
void clearScreenANSI() {
    // \033[2J clears the screen, \033[1;1H moves the cursor to the top-left (row 1, column 1)
    std::cout << "\033[2J\033[1;1H";
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
        std::cout << i+1 << ") Name: " << emp_list[i].name
                  //<< "\tYear: " << emp_list[i].year
                  << "\n";
    }
}
void printListOfEmployees(std::vector <Employee> emp_list){
    clearScreenANSI();
    std::cout << "* List of Empoyees *" << std::endl;
    printEmployees(emp_list);    
}




// Mark Vacation






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



// Draw Calender!!!

// --- Helper Function ---
bool is_date_marked(const std::vector<Date>& dates, int day_to_check) {
    // Use std::find_if to efficiently check if any Date in the vector 
    // has a matching 'day' component.
    return std::find_if(dates.begin(), dates.end(), 
        [day_to_check](const Date& d) {
            return d.day == day_to_check;
        }) != dates.end();
}
// Main calender funtion
void printCalendarMarked(
    const std::string& month_name, 
    int days_in_month, 
    int start_day_of_week, // 0 = Domingo, 6 = Sábado
    const std::vector<Date>& marked_dates, 
    char marker_char
) {
    // ... (Input validation omitted for brevity, but should be included)

    // 1. Print the Month Title
    std::cout << "\n-----------------------------\n";
    std::cout << std::setw(20) << std::right << month_name << "\n";
    std::cout << "-----------------------------\n";

    // 2. Print Weekday Headers (Using 4-character column width)
    std::cout << "Sun Mon Tue Wed Thu Fri Sat\n";

    // 3. Print the Empty Spacing (Offset for the first day)
    for (int i = 0; i < start_day_of_week; ++i) {
        std::cout << "    "; // 4 spaces to align with the columns
    }

    // 4. Print the Days
    int current_day_of_week = start_day_of_week;

    for (int day = 1; day <= days_in_month; ++day) {
        
        // Check if the current day needs a marker
        bool is_marked = is_date_marked(marked_dates, day);
        
        // Print the day number and marker
        // Use setw(2) for the day and print the marker character or a space
        std::cout << std::setw(2) << day;
        if (is_marked) {
            std::cout << marker_char << " ";
        } else {
            std::cout << "  "; // Two spaces to maintain column width
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