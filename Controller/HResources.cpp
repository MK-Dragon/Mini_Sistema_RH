// Controller/HResources.cpp

#include <iostream>
#include <string>
#include <vector>

#include "HResources.h"
#include "../Model/Employee.h"
#include "../Model/Dates.h"



std::vector <Employee> HResources::get_list_employees()
{
    return list_of_employees;
}

void HResources::add_employee(std:: string name)
{
    Employee new_emp {
        next_id,
        name,
        std::vector<Date>{},
        std::vector<Date>{}
    };
    list_of_employees.push_back(new_emp);
    next_id++;
}