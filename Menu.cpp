#include "Menu.h"


/** Menu_Error **/

std::fstream Menu_Error::log_file("menu_error_log.txt");
int Menu_Error::ERROR_COUNT = 0;

Menu_Error::Menu_Error(std::string e){
    error = e;
    ERROR_COUNT++;

    time_t t = time(0);
    tm* now = localtime(&t);
    hour = now->tm_hour;
    if(hour > 12) hour -= 12;
    minute = now->tm_min;

    day = now->tm_mday;
    month = now->tm_mon + 1;
    year = now->tm_year +1900;

}


void Menu_Error::log_error(){
    if(ERROR_COUNT == 1){
        log_file << "--------Menu Error Log--------\n\n";
    }

    log_file << ERROR_COUNT << ". ["
             << month << "/" << day << "/" << year << "] "
             << "[" << hour << ":" << minute << "] "
             << error << std::endl;
}

void Menu_Error::print_error(){
    std::cerr << "Exception thrown: "
              << error << std::endl;
}

/***********************/
/** Menu [base class] **/

void Menu::print_menu() const{
    std::ifstream dis(displayFile.c_str());
    std::cout << file_to_string(dis);
}

void Menu::print_help() const{
    std::ifstream help(helpFile.c_str());
    std::cout << file_to_string(help);
}

std::string Menu::file_to_string(std::ifstream& in_file) const{
    if(!in_file.good()) throw Menu_Error("Problem loading a text file.");
    std::string display, temp;
    while(std::getline(in_file, temp)){
        display += temp + '\n';
    }
    return display;
}

Menu::Menu(std::string disFile_in, std::string helpFile_in){
    displayFile = disFile_in;
    helpFile = helpFile_in;

}

std::string Menu::get_command(){
    std::string com;
    std::cout << "\\>";
    std::getline(std::cin, com);

    while(com == "help"){
        print_help();
        std::cout << "\\>";
        std::getline(std::cin, com);
        std::cout << std::endl;
    }
    
    return com;
}
