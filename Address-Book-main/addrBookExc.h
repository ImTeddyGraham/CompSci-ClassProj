#ifndef H_ADDRBOOK_EXC
#define H_ADDRBOOK_EXC

#include <stdexcept>
#include <string>

class addrBookExc : public std::runtime_error{
    public:
    addrBookExc(std::string s) : std::runtime_error(s){};
};


#endif
