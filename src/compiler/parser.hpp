#pragma once


#include <iostream>
#include <string>
#include <cctype>

#include "token.hpp"
#include "ast.hpp"

namespace ngopi {

    class Parser {
        public:
        std::vector<Token> tokens;
        std::size_t index;

        bool _error = false;

        Parser(std::vector<Token> tokens) : tokens(tokens) {
            index = 0;
        }

        ~Parser() {}

        BaseNode parse();
        BaseNode parse_expression();
        BaseNode parse_literal();
        BaseNode parse_equality();
        BaseNode parse_lg_operand();
        BaseNode parse_high_precedence();
        BaseNode parse_low_precedence();
        BaseNode parse_unary_expr();
        BaseNode parse_parenthise_expr();

        BaseNode parse_variable_definition();

        void skip_semicolon();
        void advance();
        Token peek();
        Token consume();

        bool match(TokenType type);
    };
};