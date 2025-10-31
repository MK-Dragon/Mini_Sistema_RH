// Controller/HResources.h

#pragma once
#include <iostream>

#include "../Model/Employee.h"
#include "../Model/Dates.h"



struct HResources
{
    std::vector <Employee> list_of_employees;
    int next_id = 0;

    std::vector <Employee> get_list_employees();
    void add_employee(std:: string name);
};

