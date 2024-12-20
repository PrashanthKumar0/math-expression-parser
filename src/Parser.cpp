
#include <memory>
#include <vector>
#include <stdexcept>

#include "Parser.hpp"

#include "lexer.hpp"
#include "ast_types.hpp"

std::shared_ptr<Expression> Parser::parse(const std::vector<Token>& tokens) 
{
    m_parseIdx = 0;
    m_tokens = tokens;
    return parse_expr();
}

Token Parser::advance() 
{
    if(m_parseIdx >= m_tokens.size()) {
        return {s_EOF_TOKEN};
    }
    Token curr_tk{current_tk()};
    m_parseIdx++;
    return curr_tk;
}

Token Parser::current_tk() 
{
    if(m_parseIdx >= m_tokens.size()) {
        return {s_EOF_TOKEN};
    }
    return m_tokens[m_parseIdx];
}

std::shared_ptr<Expression> Parser::parse_expr() 
{
    return parse_additive_expr();
}

std::shared_ptr<Expression> Parser::parse_multiplicative_expr() 
{
    std::shared_ptr<Expression> left{ parse_primary_expr() };

    while(current_tk().type == TokenType::BinaryOp) {
        
        std::string op{ current_tk().value };

        if(!(op == "*" || op == "/")) {
            break;
        }

        advance();

        OperationType opType{};
        if(op == "*") {
            opType = OperationType::Mul;
        } else {
            opType = OperationType::Div;
        }

        std::shared_ptr<Expression> right{ parse_multiplicative_expr() };
        left = std::make_shared<BinaryExpr>(left, right, opType);
    }

    return left;
}

std::shared_ptr<Expression> Parser::parse_additive_expr() 
{
    std::shared_ptr<Expression> left{ parse_multiplicative_expr() };



    while(current_tk().type == TokenType::BinaryOp) {
        std::string op{ current_tk().value };
        if(!(op == "+" || op == "-")) {
            break;
        }
        advance();
        OperationType opType{};
        if(op == "+") {
            opType = OperationType::Add;
        } else {
            opType = OperationType::Sub;
        }

        std::shared_ptr<Expression> right{ parse_multiplicative_expr() };
        left = std::make_shared<BinaryExpr>(left, right, opType);
    }

    return left;
}

std::shared_ptr<Expression>  Parser::parse_primary_expr() 
{
    const Token curr_tk{advance()};

    switch(curr_tk.type) {
        case TokenType::NumericLiteral:
            return std::make_shared<NumericLiteral>(curr_tk.value);

        case TokenType::LParen:
        {
            std::shared_ptr<Expression> exp{parse_expr()};
            Token tok{advance()};
            if(tok.type != TokenType::RParen) {
                throw std::runtime_error("Unexpedted Token " + tok.value + "  at parseIdx " + std::to_string(m_parseIdx - 1) + "    expected a ')'");
            }
            return exp;
        }
        case TokenType::RParen:
            return nullptr;

        case TokenType::BinaryOp:
        {
            bool isNeg{false};
            if(!(curr_tk.value == "+" || curr_tk.value == "-")) {
                throw std::runtime_error("Unexpedted Token " + curr_tk.value + "  at parseIdx " + std::to_string(m_parseIdx - 1) + "    expected a '+' or '-'");
            }
            Token num_tk{advance()};
            if(num_tk.type != TokenType::NumericLiteral) {
                throw std::runtime_error("Unexpedted Token " + curr_tk.value + "  at parseIdx " + std::to_string(m_parseIdx - 1) + "    expected a NumericLiteral");
            }
            // sign + number
            return std::make_shared<NumericLiteral>(curr_tk.value + num_tk.value);
        }
        default:
            throw std::runtime_error("Invalid Token '"+ curr_tk.value + "'  at parseIdx "  + std::to_string(m_parseIdx - 1));
    }
}
