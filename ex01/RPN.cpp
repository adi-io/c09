#include "RPN.hpp"

RPN::RPN(const std::string& str)
{
    if (!validateInput(str))
    {
        std::cerr << "Error: Invalid input format" << std::endl;
        exit(1);
    }

    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
            continue;

        if (isdigit(str[i]))
        {
            stack.push(str[i] - '0');
            continue;
        }

        if (stack.size() < 2)
        {
            std::cerr << "Error: Insufficient operands" << std::endl;
            exit(1);
        }

        int num2 = stack.top();
        stack.pop();
        int num1 = stack.top();
        stack.pop();

        switch (str[i])
        {
            case '+':
                stack.push(num1 + num2);
                break;
            case '-':
                stack.push(num1 - num2);
                break;
            case '*':
                stack.push(num1 * num2);
                break;
            case '/':
                if (num2 == 0)
                {
                    std::cerr << "Error: Division by zero" << std::endl;
                    exit(1);
                }
                stack.push(num1 / num2);
                break;
            default:
                std::cerr << "Error: Invalid operator" << std::endl;
                exit(1);
        }
    }

    if (stack.size() != 1)
    {
        std::cerr << "Error: Invalid expression" << std::endl;
        exit(1);
    }

    std::cout << stack.top() << std::endl;
}

bool RPN::validateInput(const std::string& str) const
{
    bool hasDigit = false;
    bool hasOperator = false;

    for (size_t i = 0; i < str.length(); i++)
    {
        char c = str[i];
        if (c == ' ')
            continue;
        if (isdigit(c))
            hasDigit = true;
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            hasOperator = true;
        else
            return false;
    }

    return hasDigit && hasOperator;
}

RPN::~RPN() {}

RPN::RPN(const RPN& other) : stack(other.stack) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        stack = other.stack;
    return *this;
}
