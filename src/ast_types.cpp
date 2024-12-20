#include <memory>
#include <string>
#include <iostream>


#include "ast_types.hpp"



BinaryExpr::BinaryExpr(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, OperationType op)
        : lhs(left)
        , rhs(right)
        , operation(op)
    {}

ExpressionType BinaryExpr::type() const 
{
    return ExpressionType::BinaryExpr;
}

void BinaryExpr::print() const 
{
    std::cout << " ( ";
    lhs->print();
    
    switch(operation) {
        case OperationType::Add :
            std::cout << " + ";
        break;
        case OperationType::Sub :
            std::cout << " - ";
        break;
        case OperationType::Mul :
            std::cout << " * ";
        break;
        case OperationType::Div :
            std::cout << " / ";
        break;
        default:
            std::cout << " Invalid ";
        break;
    }
    
    rhs->print();
    std::cout << " ) ";
}

ExpressionType NumericLiteral::type() const 
{
    return ExpressionType::NumericLiteral;
}

void NumericLiteral::print() const 
{
    std::cout << value << " ";
}

double NumericLiteral::parse_number(const std::string& val) const 
{
    double num{0};
    bool isNeg{false};
    bool firstIter{true};
    for(char ch : val) {
        if(firstIter && (ch == '-' || ch == '+')) {
            isNeg = ch == '-';
            firstIter = false;
            continue;
        }
        // assuming (ch - '0') <= 9 and >= 0 
        num = num * 10 + (ch - '0');
    }
    return isNeg ? -num : num;
}
