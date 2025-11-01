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


Employee& HResources::get_employee(int emp_id)
{
    for (int i = 0; i < next_id; i++)
    {
        if (list_of_employees[i].id == emp_id)
        {
            return list_of_employees[i];
        }
    }
    return list_of_employees[0];
}

// Vacation
void HResources::add_vacation(Employee &emp, Date day)
{
    std::cout << "Emp Vacation size @ start add: " << emp.vacations.size() << "\n";
    emp.vacations.push_back(day);
    std::cout << "\n\tDebug: added to HR: " << std::to_string(day.day) << "-" << std::to_string(day.month) << "-" << std::to_string(day.year) << "\n";
    std::cout << "Emp Vacation size @ end add: " << emp.vacations.size() << "\n";
}

// Vacation
std::vector<Date> HResources::get_vacation_days(Employee &emp, int month, int year)
{
    std::vector<Date> vaction_days;
    std::cout << "Emp: " << emp.id << " " << emp.name << "\n";
    std::cout << "Emp Vacation size @ start hr get vacation: " << emp.vacations.size() << "\n";
    for (int i = 0; i < emp.vacations.size(); i++)
    {
        std::cout << "\tDebug @ get vact:" << emp.vacations[i].day << "-" << emp.vacations[i].month << "-" << emp.vacations[i].year;
        if (emp.vacations[i].month == month && emp.vacations[i].year == year)
        {
            vaction_days.push_back(emp.vacations[i]);
            std::cout << "\tIN";
        }
        std::cout << "\n";
    }
    std::cout << "Vacation size @ Return: " << vaction_days.size() << "\n";
    return vaction_days;
}
