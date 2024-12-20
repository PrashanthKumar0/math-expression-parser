#include <string>
#include <memory>

#include "mep.hpp"
#include "lexer.hpp"
#include "Parser.hpp"
#include "ast_types.hpp"


double eval_ast(std::shared_ptr<Expression> ast_node) 
{
    if(!ast_node) return 0.0; // throw error ?

    switch(ast_node->type()) {
        case ExpressionType::NumericLiteral:
            return  dynamic_cast<NumericLiteral*>(ast_node.get())->value;
        case ExpressionType::BinaryExpr:
        {
            BinaryExpr* binop{dynamic_cast<BinaryExpr*>(ast_node.get())};
            double lhs{eval_ast(binop->lhs)};
            double rhs{eval_ast(binop->rhs)};
            OperationType op{binop->operation};
            switch(op) {
                case OperationType::Add:
                    return lhs + rhs;
                case OperationType::Sub:
                    return lhs - rhs;
                case OperationType::Mul:
                    return lhs * rhs;
                case OperationType::Div:
                    return lhs / rhs;
                default:
                    throw std::runtime_error("Invalid Operator Encountered!");
            }
        }
        default:
            throw std::runtime_error("Invalid Expression Encounterd!");
    }
}

double mep::eval(const std::string& expression) 
{
    auto tokens{tokenize(expression)};
    Parser parser{};
    auto ast{parser.parse(tokens)};
    return eval_ast(ast);
}



