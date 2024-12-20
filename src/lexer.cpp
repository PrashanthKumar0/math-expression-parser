#include <string>
#include <vector>
#include <cctype>
#include <iostream>
#include <stdexcept>

#include "lexer.hpp"



std::vector<Token> tokenize(const std::string& source) 
{
    std::vector<Token> tokens{};
    for(std::size_t idx{0}; idx < source.size(); ++idx)
    {

        if(source[idx] == '+' || source[idx] == '-' || source[idx] == '*' || source[idx] == '/')  {

            tokens.push_back(Token{TokenType::BinaryOp, std::string(1, source[idx])});

        } else if (source[idx] == '(') {

            tokens.push_back(Token{TokenType::LParen});

        } else if(source[idx] == ')') {

            tokens.push_back(Token{TokenType::RParen});

        } else if(std::isdigit(source[idx])) {

            std::string number{""};
            while(idx < source.size() && isdigit(source[idx])) {
                number += source[idx];
                idx++;
            }
            idx--;
            tokens.push_back(Token{TokenType::NumericLiteral, number});

        } else if(source[idx] == ' ' || source[idx] == '\n') {

            continue;

        } else {

            throw std::runtime_error(std::string("Lex: Invalid character '") + source[idx] + "'   at index " + std::to_string(idx));

        }
    } // for loop

    tokens.push_back({TokenType::Eof});
    return tokens;
}










std::ostream& operator << (std::ostream& out,const std::vector<Token>& tokens) {
    out << "[ " << std::endl;
        for(const auto& token : tokens) {
            out << "\t{ " << std::endl;
                out << "\t\t type : " << static_cast<int>(token.type) << ", "<< std::endl;
                out << "\t\t value : " << token.value << " "<< std::endl;
            out << "\t}, " << std::endl;
        }
    out << "] " << std::endl;
    return out;
}
