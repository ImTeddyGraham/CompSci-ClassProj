#include <iostream>
#include "addressBook.h"
#include "menu.h"

using namespace std;

int main() {
    addressBook *myBook;
    try {
        myBook = new addressBook("records.csv");
    } catch (...) {
        cout << "FATAL ERROR: failed to read file, terminating" << endl;
        return 0;
    }

    // adds menu options
    Menu menuObj("Main Menu");
    menuObj.add("Next", 's');
    menuObj.add("Previous", 'w');
    menuObj.add("Go to first", 'f');
    menuObj.add("Display all", 'd');
    menuObj.add("Display tree", 't');
    menuObj.add("Search", 'j');
    menuObj.add("Quit", 'q');

    // default action is to display 3 records
    myBook->display3();

    while (true){
        // display main menu and take actions related to options
        char selection = menuObj.displayAndRead();
        
        switch(selection)
        {
            case('s'):{++(*myBook); myBook->display3(); break;}
            case('w'):{--(*myBook); myBook->display3(); break;}
            case('f'):{myBook->goToFirst(); break;}
            case('d'):{ myBook->display('0'); break;}
            case('t'):{ myBook->display('1'); break;}
            case('j'):{ myBook->search(); break;}
            case('q'): { delete myBook; return 0;}
        }
    }
}
