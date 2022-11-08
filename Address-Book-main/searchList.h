#include "record.h"
#include <iomanip>

struct searchListEl {
    record *addrBookElem;
    searchListEl *link;
};

class searchList {
    searchListEl *head;
    searchListEl *last;
    public:
    searchList();
    ~searchList();
    void add(record*);
    void display();
};

searchList::searchList() {
    head = nullptr; last = nullptr;
}

searchList::~searchList() {
    if (head == nullptr && last == nullptr){return;}
    searchListEl *temp = head->link;
    while(temp != nullptr){
        delete(head);
        head = temp;
        temp = head->link;
    }
    delete(head);
    head = nullptr;

}

void searchList::add(record *element) {
    searchListEl *newItem = new searchListEl;
    newItem->addrBookElem = element;
    newItem->link = nullptr;
    
    if (head == nullptr){
        head = newItem;
        last = newItem;
    }else{
        last->link = newItem;
        last = newItem;
    }
}

void searchList::display() {

    searchListEl *temp = head;
    while (temp != nullptr){
        std::cout << temp->addrBookElem->first_name << " " << temp->addrBookElem->last_name << "\t"
        << temp->addrBookElem->address_street << "\t"<< temp->addrBookElem->address_city << "\t"
        << temp->addrBookElem->address_state << "\t" << temp->addrBookElem->address_zip << "\t"
        << temp->addrBookElem->mobile_no << "\t" << temp->addrBookElem->notes << std::endl;
        temp = temp->link;
    }
}

