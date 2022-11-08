#include <iostream>
#include "addressBook.h"
#include "addrBookExc.h"
#include "searchList.h"
#include "menu.h"
#include <fstream>
#include <vector>
#include <sstream> 

using namespace std;

int strToInt(string s);

addressBook::addressBook(string filename) { // constructor 
    head = nullptr;
    last = nullptr;
    firstToDisplay = head;
    loadFile(filename);
}
addressBook::~addressBook() { // destructor 
    while (head != nullptr){
        firstToDisplay = head->next;
        delete head;
        head = firstToDisplay;
    }
    last = nullptr;
    firstToDisplay = nullptr;
}
void addressBook::displayRecord(record *r) { 
    if (r == nullptr) {return;} // if LL is empty quit 
    
    // displays all the fields for each node
    cout << left << setw(5) << "Name: " << r->first_name << " " << r->last_name << endl;
    cout << "Street: " << left << setw(25) << r->address_street;
    cout << "City: " << left << setw(25) << r->address_city;
    cout << "State: " << left << setw(25) << r->address_state;
    cout << "ZIP: " << left << setw(20) << r->address_zip << endl;
    cout << left << setw(15) << "Phone: " << r->mobile_no << endl;
    cout << left << setw(15) << "Notes: " << r->notes << endl << endl;
}
void addressBook::display3() {
    int i = 0;
    record *temp = firstToDisplay; 
    while( (temp != nullptr) && (i<3) ){ // displays 3 record if possible 
        displayRecord(temp);
        temp = temp->next; //moves first to display 
        ++i;
    }
}
void addressBook::displayAll(record *current) { // traverses LL displaying each node
    displayRecord(current); 
    if (current == nullptr){return;}
    displayAll(current->next);
}
void addressBook::displayTree(record *current, int indent) {

    for (int i=0; i<indent; i++){cout << "\t";} 
    cout << "id=" << current->id << " name=" << current->first_name << " " << current->last_name << endl;
    if (current->child != 0){displayTree(current->child, indent+1);
    } else if (current->next != nullptr){displayTree(current->next, 0);}
}
void addressBook::display(const char option) {   // 0: all, full     1: tree
    (option == '0') ? displayAll(head) : displayTree(head, 0); 
}
void addressBook::goToFirst() {
    firstToDisplay = head;
    display3();
}
void addressBook::operator++() { 
    if (firstToDisplay->next != nullptr){
        firstToDisplay = firstToDisplay->next;
    }
}
void addressBook::operator--() {
    if (firstToDisplay->prev != nullptr){
        firstToDisplay = firstToDisplay->prev;
    }
}
record* addressBook::parseAllocate(string line) {    
    
    istringstream ss(line);
    string token; 

    record *temp = new record;
    //use stoi instead of sstring maybe 
    //stoi vs sstring ? 
    for (int i=0; i<10; i++){ // parses entire comma separated line
        getline(ss, token, ',');
        switch (i) // sorts record, dependant on comma #
        {
        case(0):{temp->id = strToInt(token); break;}
        case(1):{ // updates parent-child relation
            if (strToInt(token) != 0){
                record *tempTwo = head;
                while( (tempTwo != nullptr) && (tempTwo->id != strToInt(token)) ) {
                    tempTwo = tempTwo->next;
                }
                tempTwo->child = temp;
                }
            break;
            }
        case(2):{temp->first_name = token; break;}
        case(3):{temp->last_name = token; break;}
        case(4):{temp->address_street = token; break;}
        case(5):{temp->address_city = token; break;}
        case(6):{temp->address_state = token; break;}
        case(7):{temp->address_zip = token; break;}
        case(8):{temp->mobile_no = token; break;}
        case(9):{temp->notes = token; break;}
        }
    }
    return temp;
}
void addressBook::addRecord(string line) { // creates new node and inserts to LL 
    //obtains new node
    record *newItem = parseAllocate(line);
    
    // adds node to end of LL
    if (head != nullptr){
        newItem->prev = last;
        newItem->next = nullptr;
        last->next = newItem;
        last = newItem;
    }
    else { // LL is empty 
        head = newItem;
        last = newItem;
        newItem->prev = nullptr;
        newItem->next = nullptr;
        firstToDisplay = newItem;
    }
}
void addressBook::loadFile(string filename) {
    ifstream fin;

    try {
        fin.open(filename);
        if ( !fin.is_open() ) // exception thrown if file is missing
            throw addrBookExc("Error opening file: " + filename + "\n! ! Abort ! !");
    } catch(addrBookExc e) {
        cout << e.what() << endl;
        throw addrBookExc("Error opening file: " + filename + "\n! ! Abort ! !");
    }

    while(!fin.eof()){ // reads entire file
        string line;
        getline(fin, line);
        addRecord(line);
    }
}
void addressBook::search() { 
    // lists menu options 
    Menu menuObj("Search Menu");
    menuObj.add("First Name", '1');
    menuObj.add("Last Name", '2');
    menuObj.add("City", '3');
    menuObj.add("State", '4');
    menuObj.add("Back", 'q');

    char selection = menuObj.displayAndRead();
    if (selection == 'q'){return;}
    
    string keyword;
    cout << "Enter Keyword: "; cin >> keyword; cout << endl;

    searchList searchListObj;
    
    // i wanna just use the scroll ptr but do i need to track its pos?
    record *temp;
    temp = head;

    while (temp != nullptr){ // runs through LL
        switch (selection) // searches desired field, only lists complete matches 
        {
            case('1'):{ // first name
                if (temp->first_name == keyword)
                    searchListObj.add(temp);
                break;
            }
            case('2'):{ // last name
                if (temp->last_name == keyword)
                    searchListObj.add(temp);
                break;
            }
            case('3'):{ // city
                if (temp->address_city == keyword)
                    searchListObj.add(temp);
                break;
            }
            case('4'):{ //state
                if (temp->address_state == keyword)
                    searchListObj.add(temp);
                break;
            }
        }
        temp = temp->next;
    }
    searchListObj.display(); 
}
int strToInt(string s){
    stringstream ss;
    long int converted;
    ss << s;
    ss >> converted;
    return converted;
}
