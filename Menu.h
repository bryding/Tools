#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Menu_Error{
public:
    Menu_Error(std::string e);
    void log_error();
    void print_error();
private:
    Menu_Error() {}

    std::string           error;
    int                   hour, minute, day, month, year;
    static int            ERROR_COUNT;
    static std::fstream   log_file;
};

class Menu{
public:
    Menu(std::string disFile_in, std::string helpFile_in);

    /** Interface **/
    void print_menu() const;
    std::string get_command();

private:
    //Constructor is private because helpFile and displayFile
    //  MUST be initalized for this class to be used properly.
    Menu(){}

    std::string file_to_string(std::ifstream& in_file) const;
    void print_help() const;

    std::string     displayFile,
                    helpFile;
};



#endif //MENU_H
