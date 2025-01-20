#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>

class RPN
{
    private:
        std::stack<int> stack;
        bool validateInput(const std::string& str) const;

    public:
        RPN(const std::string& str);
        ~RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
};

#endif
