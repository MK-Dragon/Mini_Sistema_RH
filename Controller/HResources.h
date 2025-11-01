// Controller/HResources.h

#pragma once
#include <iostream>

#include "../Model/Employee.h"
#include "../Model/Dates.h"



struct HResources
{
    // Variables
    std::vector <Employee> list_of_employees;
    int next_id = 0;

    // Add & List
    std::vector <Employee> get_list_employees();
    void add_employee(std:: string name);

    Employee& get_employee(int emp_id);

    // Vacation
    void add_vacation(Employee &emp, Date day);
    void remove_vacation(Employee &emp, Date day_to_remove);
    std::vector<Date> get_vacation_days(Employee &emp, int month, int year);

    // Absences
    void add_absence(Employee &emp, Date day);
    void remove_absence(Employee &emp, Date day_to_remove);
    std::vector<Date> get_absence_days(Employee &emp, int month, int year);
};

