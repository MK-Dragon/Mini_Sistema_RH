// Controller/HResources.cpp

#include <iostream>
#include <string>
#include <vector>

#include <algorithm> // Required for std::remove

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
    emp.vacations.push_back(day);
}
void HResources::remove_vacation(Employee &emp, Date day_to_remove)
{
    // The erase-remove idiom:
    
    // 1. std::remove goes through the vector and shifts any element that 
    //    DOES NOT match 'day_to_remove' to the front. 
    //    It returns an iterator pointing to the first "removed" (now junk) element.
    auto it = std::remove(emp.vacations.begin(), emp.vacations.end(), day_to_remove);

    // 2. std::vector::erase uses the iterator range (from the result of std::remove 
    //    to the end) to physically delete the elements and resize the vector.
    emp.vacations.erase(it, emp.vacations.end());
    
    // You could add debugging output here if needed:
    // std::cout << "\n\tDebug: Removed date from HR.\n";
}

// Vacation
std::vector<Date> HResources::get_vacation_days(Employee &emp, int month, int year)
{
    std::vector<Date> vaction_days;
    //std::cout << "Emp: " << emp.id << " " << emp.name << "\n";
    //std::cout << "Emp Vacation size @ start hr get vacation: " << emp.vacations.size() << "\n";
    for (int i = 0; i < emp.vacations.size(); i++)
    {
        //std::cout << "\tDebug @ get vact:" << emp.vacations[i].day << "-" << emp.vacations[i].month << "-" << emp.vacations[i].year;
        if (emp.vacations[i].month == month && emp.vacations[i].year == year)
        {
            vaction_days.push_back(emp.vacations[i]);
            //std::cout << "\tIN";
        }
        //std::cout << "\n";
    }
    //std::cout << "Vacation size @ Return: " << vaction_days.size() << "\n";
    return vaction_days;
}





// Absences
void HResources::add_absence(Employee &emp, Date day)
{
    emp.absences.push_back(day);
}
void HResources::remove_absence(Employee &emp, Date day_to_remove)
{
    auto it = std::remove(emp.absences.begin(), emp.absences.end(), day_to_remove);
    emp.absences.erase(it, emp.absences.end());
}

// Absences
std::vector<Date> HResources::get_absence_days(Employee &emp, int month, int year)
{
    std::vector<Date> absence_days;
    //std::cout << "Emp: " << emp.id << " " << emp.name << "\n";
    //std::cout << "Emp Vacation size @ start hr get vacation: " << emp.vacations.size() << "\n";
    for (int i = 0; i < emp.vacations.size(); i++)
    {
        //std::cout << "\tDebug @ get vact:" << emp.vacations[i].day << "-" << emp.vacations[i].month << "-" << emp.vacations[i].year;
        if (emp.absences[i].month == month && emp.absences[i].year == year)
        {
            absence_days.push_back(emp.absences[i]);
            //std::cout << "\tIN";
        }
        //std::cout << "\n";
    }
    //std::cout << "Vacation size @ Return: " << absence_days.size() << "\n";
    return absence_days;
}