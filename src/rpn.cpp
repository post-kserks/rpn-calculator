#include "rpn.h"
#include <stdexcept>
#include <sstream>
#include <iostream>

double evaluate_rpn(const std::string& expression) {
    std::stack<double> stack;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        // Обработка чисел
        try {
            double num = std::stod(token);
            stack.push(num);
            continue;
        } catch (const std::invalid_argument&) {
            // Если не число, то оператор
        }

        // Обработка операторов
        if (token == "+") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '+'");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a + b);
        }
        else if (token == "-") {
            if (stack.size() < 2) throw std::invalid_argument("Not enough operands for '-'");
            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();
            stack.push(a - b);
        }
        else if (token == "*") {
            // ... реализуйте умножение
        }
        else if (token == "/") {
            // ... реализуйте деление с проверкой на ноль
        }
        else {
            throw std::invalid_argument("Invalid token: " + token);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid expression: too many or too few operands");
    }
    return stack.top();
}
