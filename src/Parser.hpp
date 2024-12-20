#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <memory>

#include "lexer.hpp"
#include "ast_types.hpp"

class Parser {

public:
    std::shared_ptr<Expression> parse(const std::vector<Token>& tokens);

private:

    Token advance();
    Token current_tk();

    std::shared_ptr<Expression> parse_expr();
    std::shared_ptr<Expression> parse_multiplicative_expr();
    std::shared_ptr<Expression> parse_additive_expr();
    std::shared_ptr<Expression> parse_primary_expr();

private:
    constexpr static TokenType s_EOF_TOKEN{TokenType::Eof};
    std::size_t m_parseIdx{};
    std::vector<Token> m_tokens{};
};


#endif // _PARSER_HPP_
