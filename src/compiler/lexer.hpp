#pragma once

#include "./token.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <cctype>

namespace ngopi {
    class Lexer {
        private:
        std::size_t index;
        std::string source;
        std::size_t line;
        std::size_t column;
        std::string file;
        
        public:
        Lexer(std::string source, std::string file) : source(source), file(file) {
            this->index = 0;
            this->line = 1;
            this->column = 0;
        }

        ~Lexer() {}

        std::vector<Token> start();
        Token get_number_token();
        Token get_string_token();
        Token get_string_interpolate_token();
        Token get_identifier_token();
        Token get_punctuation_token();

        void skip_whitespace();
        void skip_comment();
        void advance();

        char peek();
        char peek_next();

        bool is_at_end();
    };
};