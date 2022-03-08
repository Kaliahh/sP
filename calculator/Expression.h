//
// Created by ane on 22/02/2022.
//

#ifndef CALCULATOR_EXPRESSION_H
#define CALCULATOR_EXPRESSION_H

#include <memory>
#include "calculator.hpp"

namespace calculator {

    class Expression {
    public:
        Expression(const Expression& other) = default;
        Expression& operator=(const Expression& other) = default;

        Expression(Expression&& other) noexcept = default;
        Expression& operator=(Expression&& other) noexcept = default;

        ~Expression() = default;
    };

    class VariableExpression : public Expression {
        std::unique_ptr<var_t> var;
    };

    class UnaryExpression : public Expression {
    public:
        enum op_t { plus, minus, add, sub, assign, mult, div } op;
        std::unique_ptr<expr_t> operand;
    };

    class BinaryExpression : public UnaryExpression {

        std::unique_ptr<expr_t> other_operand;

    };
}


#endif //CALCULATOR_EXPRESSION_H
