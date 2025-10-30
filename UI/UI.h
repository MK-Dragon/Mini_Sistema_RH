// UI/UI.h

#pragma once
#include "../Model/Employee.h"
#include "../Model/Dates.h"
#include "../Utils/Calendar.h"

#include <string>
#include <iostream>
#include <conio.h> // Header for _getch()
#include <vector>

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

    std::cout << "(3) Manage Vacation" << std::endl;
    std::cout << "(4) Mark absences" << std::endl;
    std::cout << "(5) Employee's Monthly Calendar" << std::endl;

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
void printListOfEmployees(std::vector <Employee> emp_list){
    clearScreenANSI();
    std::cout << "* Todos os Produtos *" << std::endl;
    
    for (int i = 0; i < emp_list.size(); i++) {
        std::cout << i+1 << ") Name: " << emp_list[i].name
                  //<< "\tYear: " << emp_list[i].year
                  << "\n";
    }
}





// General Use
void showPressAnyKey(){
    std::cout << "\nPress Any Key to Continue" << std::endl;
    char key = _getch();
}