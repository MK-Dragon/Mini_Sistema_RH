// main.cpp

#include <iostream>
#include <string>

#include "Controller/HResources.h"
#include "Controller/HResources.cpp"
#include "Model/Employee.h"
#include "Model/Dates.h"
#include "UI/UI.h"
#include "Utils\CSV_Manager.h"


HResources hr;


int get_emp_id(){
    // Get employee ID
    int imp_id;
    while (true) {
        if (!(std::cin >> imp_id)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid input. Please enter a number between 0 and " << hr.next_id -1 << "\n";
            continue;
        }
        if (imp_id >= 0 && imp_id < hr.next_id) break;
        std::cout << "Invalid input. Please enter a number between 0 and " << hr.next_id -1 << "\n";
    }
    return imp_id;
}

Date get_weed_day(){
    Date new_day;
    //std::cout << "\n\tDebug @ new day:" << std::to_string(new_day.day) << "-" << std::to_string(new_day.month) << "-" << std::to_string(new_day.year) << "\n";

    while (true)
    {
        std::string new_day_string;
        std::getline(std::cin >> std::ws, new_day_string);
        std::cin.clear();

        //std::cout << "Debug String: " << new_day_string << "\n";        

        new_day = parse_date(new_day_string);
        //std::cout << "\n\tDebug at parse:" << std::to_string(new_day.day) << "-" << std::to_string(new_day.month) << "-" << std::to_string(new_day.year) << "\n";

        // If date is Zero / Error
        if (new_day.day == 0 || new_day.month == 0 || new_day.year == 0)
        {
            std::cout << "Invalid day. Please enter a number equal or bigger then 1.\n";
            showPressAnyKey();
            continue;
        }
        // check weekend
        int day_week = diaSemana(new_day.day, new_day.month, new_day.year);
        if (day_week == 0 || day_week == 6)
        {
            std::cout << "Invalid day. Please enter a Week Day.\n";
            showPressAnyKey();
            continue;
        }
        break;
    }
    //std::cout << "\n\tDebug return get_week:" << std::to_string(new_day.day) << "-" << std::to_string(new_day.month) << "-" << std::to_string(new_day.year) << "\n";
    return new_day;
}




int main()
{
    int menu = 0; // Main menu
    std::string FILE_NAME = "db.csv";

    // Load CSV
    Load_from_CSV(FILE_NAME);
    
    // testing
    hr.add_employee("Marco");
    hr.add_employee("Zé Manel");
    hr.add_employee("Ana Pimpão");
    for (int i = 0; i < 3; i++)
    {
        Employee e = hr.get_employee(i);
    }
    
    // Check CSV


    while (menu != -1)
    {
        Employee* emp;
        std::string new_emp_name;
        int imp_id;

        int num_days;
        Date new_day;
        std::string new_day_string;
        

        // Show Menu
        printMainMenu();

        // Get user input
        while (true) {
            if (!(std::cin >> menu)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input. Please enter a number between 0 and 7.\n";
                continue;
            }
            if (menu >= 0 && menu <= 7) break;
            std::cout << "Please enter a number between 0 and 7.\n";
        }

        // Enter Menu
        switch (menu)
        {
            case 0: // Exit
                menu = -1;
                break;

            case 1: // List Employees
                printListOfEmployees(hr.get_list_employees());

                showPressAnyKey();
                menu = 0;
                break;
            
            case 2: // Add Employees
                printAddEmployee_name();
                std::getline(std::cin >> std::ws, new_emp_name);
                std::cin.clear();
                
                hr.add_employee(new_emp_name);
                menu = 0;
                break;
            
            case 3: // Mark Vacation
                printChooseEmployee("Mark Vacation", hr.get_list_employees());
                
                // Get employee ID
                imp_id = get_emp_id();
                emp = &hr.get_employee(imp_id);

                // get number of days to add
                printEnterValue("Mark Vacation", "Number os Days");
                while (true) {
                    if (!(std::cin >> num_days)) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Invalid input. Please enter a number equal or bigger then 0.\n";
                        continue;
                    }
                    if (num_days >= 0) break;
                    std::cout << "Invalid input. Please enter a number equal or bigger then 0.\n";
                }
                // get day
                for (int i = 0; i < num_days; i++)
                {
                    std::string title = "Vacation Day " + std::to_string(i + 1) + "/" + std::to_string(num_days);
                    printChooseDay(title);
                    
                    hr.add_vacation(*emp, get_weed_day());
                }
                menu = 0;
                break;

            case 7: // Employee's Monthly Calendar
                printChooseEmployee("Employee's Monthly Calendar", hr.get_list_employees());
                // Get employee ID
                imp_id = get_emp_id();
                emp = &hr.get_employee(imp_id);

                //std::cout << "Emp: " << emp->id << " " << emp->name << "\n";
                //std::cout << "Emp Vacation size @ MAIN: " << emp->vacations.size() << "\n";

                // get Month & year
                printEnterValue("Employee's Monthly Calendar", "Month and Year");
                while (true)
                {
                    std::getline(std::cin >> std::ws, new_day_string);
                    std::cin.clear();

                    new_day = parse_month_year(new_day_string);

                    // If date is Zero / Error
                    if (new_day.month == 0 || new_day.year == 0)
                    {
                        std::cout << "Invalid Date. Please enter a Mounth or Year.\n";
                        showPressAnyKey();
                        continue;
                    }
                    break;
                }
                {
                    std::string title = emp->name + " - " + nomeMes(new_day.month) + " " + std::to_string(new_day.year);
                    printCalendarMarked(
                        title,
                        diasNoMes(new_day.month, new_day.year),
                        diaSemana(1, new_day.month, new_day.year),
                        hr.get_vacation_days(*emp, new_day.month, new_day.year),
                        'V'
                    );
                    
                    /*std::vector<Date> vaction_days = hr.get_vacation_days(*emp, new_day.month, new_day.year);
                    std::cout << "Debug vac list:" << "\n";
                    for (int i = 0; i < vaction_days.size(); i++)
                    {
                        std::cout << "\t" << 
                        std::to_string(vaction_days[i].day) << "/" <<
                        std::to_string(vaction_days[i].month) << "/" <<
                        std::to_string(vaction_days[i].year) << "/" << std::endl;
                    }*/
                }

                showPressAnyKey();
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
