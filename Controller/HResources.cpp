// Controller/HResources.cpp

#include <iostream>
#include <string>
#include <vector>

#include "HResources.h"
#include "../Model/Employee.h"
#include "../Model/Dates.h"


// Add & List
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


Employee HResources::get_employee(int emp_id)
{
    for (int i = 0; i < next_id; i++)
    {
        if (list_of_employees[i].id = emp_id)
        {
            return list_of_employees[i];
        }
    }
    return list_of_employees[0];
}

// Vacation
void HResources::add_vacation(Employee emp, Date day)
{
    emp.vacations.push_back(day);
}

// Vacation
std::vector<Date> HResources::get_vacation_days(Employee emp, int month, int year)
{
    std::vector<Date> vaction_days;
    for (int i = 0; i < emp.vacations.size(); i++)
    {
        if (emp.vacations[i].month == month && emp.vacations[i].year == year)
        {
            vaction_days.push_back(emp.vacations[i]);
        }
    }
    return vaction_days;
}
