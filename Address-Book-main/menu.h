#include <vector> 
#include "addrBookExc.h"
#include <iomanip>

struct menuEntry {
    std::string text;
    char key;
};

class Menu {
    std::string title;
    std::vector<menuEntry> options;
    void validate(char option) {
        try // throws exception if option is not listed 
        {
            for (decltype(options.size()) i=0; i<options.size(); i++){
                if (options[i].key == option) {
                    return;
                }
            }
            throw addrBookExc("invalid menu entry"); 
        }
        catch (addrBookExc e)
        {
            std::cout << "Error: " << e.what() << std::endl;
            throw addrBookExc("invalid menu entry"); 
        }
    }
    public:
    Menu(std::string title) {
        this->title = title;
    }
    void add(std::string option_text, char key) {
        menuEntry temp; 
        temp.key = key; temp.text = option_text;
        options.push_back(temp);
    }
    char displayAndRead(){
        char choice; 
        bool invalid = true;
        
        do {
            std::cout << title << std::endl << "==============" << std::endl; 
            for (decltype(options.size()) i=0; i<options.size(); i++)
                std::cout << std::left << std::setw(10) << options[i].text << "\t(" << options[i].key << ")" << std::endl;
            std::cout << "\nSelection: "; std::cin >> choice;
            std::cout << std::endl;
            try {
                validate(choice);
                invalid = false;
            } catch (addrBookExc) {
                std::cout << "Try Again" << std::endl << std::endl;
            }
        } while(invalid);
        
        return tolower(choice);
    }
};
