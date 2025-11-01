// main.cpp

#include <iostream>
#include <string>

#include <locale>

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
    std::vector<Date> empty_vacations;
std::vector<Date> empty_absences;
printCalendarMarked("Test Month", 31, 5, empty_vacations, 'V', empty_absences, 'A');

    // FIX: Use the standard C locale name for UTF-8
    try {
        std::locale::global(std::locale("C.UTF-8"));
        std::cout.imbue(std::locale("C.UTF-8"));
    } catch (const std::runtime_error& e) {
        // Fallback in case "C.UTF-8" also fails (e.g., on some older Windows systems)
        std::cerr << "Warning: Failed to set C.UTF-8 locale. Using default C locale." << std::endl;
        std::locale::global(std::locale("C"));
        std::cout.imbue(std::locale("C"));
    }
    // This ensures your C++ program *sends* UTF-8 bytes to the console.
    try {
        std::locale::global(std::locale("C.UTF-8")); 
        std::cout.imbue(std::locale("C.UTF-8"));
    } catch (const std::runtime_error& e) {
        // Fallback or warning if C.UTF-8 isn't available
        // It's crucial this part doesn't crash the program.
        std::cerr << "Warning: UTF-8 locale not available. Display may be corrupted." << std::endl;
    }


    int menu = 0; // Main menu
    std::string FILE_NAME = "db.csv";

    // Load CSV
    if (Check_File_Exists(FILE_NAME) == 1)
    {
        // READ FILE
        std:: cout << "main -> Reading File: " << FILE_NAME << "\n";
        std::vector<Employee> loaded_emp = read_csv(FILE_NAME);
        std:: cout << "main -> Num Emps: " << loaded_emp.size() << "\n";

        for (const auto& emp : loaded_emp){
            hr.add_loaded_employee(emp.name, emp.vacations, emp.absences);
        }
    }
    else // Not File found -> Load Demo
    {
        std::vector<Date> vac = {{31,10,2025}, {30,10,2025}};
        std::vector<Date> abse = {{7,10,2025}, {8,10,2025}};

        hr.add_loaded_employee("Zé Manel", vac, abse);
        hr.add_loaded_employee("Ana Pimbão", vac, abse);
        hr.add_loaded_employee("Lili Canelas", vac, abse);
        hr.add_loaded_employee("Fernado Fisgado", vac, abse);
    }


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


            case 4: // REMOVE Vacation
                printChooseEmployee("Remove Vacation", hr.get_list_employees());
                
                // Get employee ID
                imp_id = get_emp_id();
                emp = &hr.get_employee(imp_id);

                // get number of days to add
                printEnterValue("Remove Vacation", "Number os Days");
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
                    
                    hr.remove_vacation(*emp, get_weed_day());
                }
                menu = 0;
                break;


            case 5:
                break;

            case 6:
                break;


            case 7: // Employee's Monthly Calendar
                printChooseEmployee("Employee's Monthly Calendar", hr.get_list_employees());
                // Get employee ID
                imp_id = get_emp_id();
                emp = &hr.get_employee(imp_id);

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
                    std:: cout << "main -> before print Cale: " << emp->absences.size() << "\n";

                    std::vector<Date> vacations;
                    std::vector<Date> absences;

                    // What EVER the F#$% the bug was! -.-' This Fixes it!
                    if (emp->vacations.size() != 0)
                    {
                        vacations = hr.get_vacation_days(*emp, new_day.month, new_day.year);
                    }
                    if (emp->absences.size() != 0)
                    {
                        absences = hr.get_absence_days(*emp, new_day.month, new_day.year);
                    }
                    
                    std::string title = emp->name + " - " + nomeMes(new_day.month) + " " + std::to_string(new_day.year);
                    printCalendarMarked(
                        title,
                        diasNoMes(new_day.month, new_day.year),
                        diaSemana(1, new_day.month, new_day.year),
                        vacations,
                        'V',
                        absences,
                        'A'
                    );
                }
                showPressAnyKey();
                menu = 0;
                break;

            default:
                break;
        }
    }

    // Save to CSV and Exit
    if (!write_csv(FILE_NAME, hr.get_list_employees()))
    {
        showError("Error Saving CSV", "We Could not Save the Data...");
    }
    return 0;
}
