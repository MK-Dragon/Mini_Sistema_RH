// Utils\CSV_Manager.h

#include <iostream>
#include <string>




void Check_File_Exists(std::string FILE_NAME)
{
    std::cout << "\t" << "File Exists! OR NOT! XD\n";
}



void Load_from_CSV(std::string FILE_NAME)
{
    std::cout << "Laoding Data!\n";

    // Chack File Exists -> Make File (if not)
    Check_File_Exists(FILE_NAME);

    // Save Data to File
}

void Save_to_CSV(std::string FILE_NAME)
{
    std::cout << "Saving Data!\n";

    // Chack File Exists -> Make File (if not)
    Check_File_Exists(FILE_NAME);

    // Save Data to File
}
