#ifndef _AST_TYPES_HPP_
#define _AST_TYPES_HPP_

#include <memory>
#include <iostream>


enum class ExpressionType {
    BinaryExpr,
    NumericLiteral,
    //-----------------
    Invalid,
};

enum class OperationType {
    Add,
    Sub,
    Mul,
    Div,
    //---------------
    Invalid
};

struct Expression
{
    virtual auto type() const -> ExpressionType {
        return ExpressionType::Invalid;
    };

    virtual auto print() const -> void {
        std::cout << " <Invalid Expr> ";
    }

    static auto to_string(ExpressionType type) -> std::string {
        switch(type) {
            case ExpressionType::BinaryExpr:
                return "Binary Expr";

            case ExpressionType::NumericLiteral:
                return "Numeric Literal";

            default:
                return "Invalid";
        }
    }
};

struct BinaryExpr : Expression
{

    std::shared_ptr<Expression> lhs{nullptr};
    std::shared_ptr<Expression> rhs{nullptr};
    OperationType operation{OperationType::Invalid};

    BinaryExpr(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right, OperationType op);

    auto type()  const -> ExpressionType override ;
    auto print() const -> void override;
};

struct NumericLiteral : Expression
{
    double value{0.0};

    NumericLiteral(double val) : value(val) {}
    NumericLiteral(const std::string& val) : value(parse_number(val)) { }

    ExpressionType type() const override ;


    auto print() const -> void override;

private:
    auto parse_number(const std::string& val) const -> double;
};


#endif // _AST_TYPES_HPP_
