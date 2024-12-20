#ifndef _LEXER_HPP_
#define _LEXER_HPP_


#include <vector>
#include <string>


enum class TokenType {
    //--------------
    // single char
    LParen,
    RParen,
    BinaryOp,
    //--------------
    // multi char
    NumericLiteral,
    //--------------
    Eof,
    Invalid,
};

struct Token {
    TokenType type{TokenType::Invalid};
    std::string value{""};
};

std::vector<Token> tokenize(const std::string& source);






// Just for debugging
std::ostream& operator << (std::ostream& out,const std::vector<Token>& tokens);



#endif  // _LEXER_HPP_
