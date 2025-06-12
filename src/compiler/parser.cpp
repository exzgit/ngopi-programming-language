#include "parser.hpp"

#include <iostream>
#include "../shared/value.hpp"

namespace ngopi {
    BaseNode Parser::parse() {
        std::vector<std::shared_ptr<BaseNode>> node;

        while (peek().type != TokenType::Eof && index < tokens.size()) {
            if (match(TokenType::Let)) {
                node.push_back(std::make_shared<BaseNode>(parse_variable_definition()));
            } else {
                std::cout << "Error at " << peek().file << ", " << peek().line << " : " << peek().column << "\n";
                std::cout << "Syntax Error: Unexpected token '" << peek().value << "'\n"; 
                _error = true;
            }
        }

        return File(node, 0, 0, "");
    }

    BaseNode Parser::parse_expression() {
        return parse_equality();
    }
    
    BaseNode Parser::parse_equality() {
        BaseNode left = parse_lg_operand();
        if (match(TokenType::IsEqual)) {
            std::size_t line = peek().line;
            std::size_t column = peek().column;
            std::string file = peek().file;
            advance();
            left = BinaryOperation(std::make_shared<BaseNode>(left), std::make_shared<BaseNode>(parse_lg_operand()), "==", line, column, file);
        }

        return left;
    }
    
    BaseNode Parser::parse_lg_operand() {
        BaseNode left = parse_low_precedence();
        if (match(TokenType::Less) || match(TokenType::Greater) || match(TokenType::LessEqual) || match(TokenType::GreaterEqual)) {
            Token token = consume();
            std::size_t line = peek().line;
            std::size_t column = peek().column;
            std::string file = peek().file;
            left = BinaryOperation(std::make_shared<BaseNode>(left), std::make_shared<BaseNode>(parse_low_precedence()), token.value, line, column, file);
        }

        return left;
    }
    
    
    BaseNode Parser::parse_low_precedence() {
        BaseNode left = parse_low_precedence();
        if (match(TokenType::Plus) || match(TokenType::Minus)) {
            Token token = consume();
            std::size_t line = peek().line;
            std::size_t column = peek().column;
            std::string file = peek().file;
            left = BinaryOperation(std::make_shared<BaseNode>(left), std::make_shared<BaseNode>(parse_low_precedence()), token.value, line, column, file);
        }

        return left;
    }
    
    BaseNode Parser::parse_high_precedence() {
        BaseNode left = parse_low_precedence();
        if (match(TokenType::Multiply) || match(TokenType::Divide)) {
            Token token = consume();
            std::size_t line = peek().line;
            std::size_t column = peek().column;
            std::string file = peek().file;
            left = BinaryOperation(std::make_shared<BaseNode>(left), std::make_shared<BaseNode>(parse_low_precedence()), token.value, line, column, file);
        }

        return left;
    }

    BaseNode Parser::parse_unary_expr() {
        BaseNode left = parse_parenthise_expr();
        if (match(TokenType::Minus)) {
            Token token = consume();
            std::size_t line = peek().line;
            std::size_t column = peek().column;
            std::string file = peek().file;
            left = UnaryOperation(std::make_shared<BaseNode>(left), token.value, line, column, file);
        }

        return left;
    }
    
    BaseNode Parser::parse_parenthise_expr() {
        if (match(TokenType::LeftParenthise)) {
            Token token = consume();
            std::size_t line = peek().line;
            std::size_t column = peek().column;
            std::string file = peek().file;
            BaseNode value = parse_expression();
            if (!match(TokenType::RightParenthise)) {
                std::cout << "Error at " << peek().file << ", " << peek().line << " : " << peek().column << "\n";
                std::cout << "Syntax Error: Expected token ')', but got '" << peek().value << "'\n"; 
                _error = true;
            }
            advance();
            return value;
        }

        return parse_literal();
    }
    
    BaseNode Parser::parse_literal() {
        Token token = peek();
        if(match(TokenType::StringLiteral)) {
            advance();
            return StringLiteral(token.value, token.line, token.column, token.file);
        } else if (match(TokenType::NumberLiteral)) {
            advance();
            if (canConvertToInt(token.value)) {
                return IntLiteral(strToInt(token.value), token.line, token.column, token.file);
            } else {
                return IntLiteral(strToFloat(token.value), token.line, token.column, token.file);
            }
        } else if (match(TokenType::True) || match(TokenType::False)) {
            advance();
            return BoolLiteral(token.type == TokenType::True, token.line, token.column, token.file);
        } else if (match(TokenType::Nullable)) {
            advance();
            return Nullable(token.line, token.column, token.file);
        } else {
            std::cout << "Error at " << peek().file << ", " << peek().line << " : " << peek().column << "\n";
            std::cout << "Syntax Error: Unexpected token '" << peek().value << "'\n"; 
            _error = true;

            return Nullable(token.line, token.column, token.file);
        }
    }
    
    BaseNode Parser::parse_variable_definition() {
        std::size_t line = peek().line;
        std::size_t column = peek().column;
        std::string file = peek().file;

        advance();

        std::string identifier = peek().value;
        if (!match(TokenType::Identifier)) {
            std::cout << "Error at " << peek().file << ", " << peek().line << " : " << peek().column << "\n";
            std::cout << "Syntax Error: Expected identifier, but got '" << peek().value << "'\n"; 
            _error = true;
        }

        advance();

        if (!match(TokenType::Equal)) {
            std::cout << "Error at " << peek().file << ", " << peek().line << " : " << peek().column << "\n";
            std::cout << "Syntax Error: Expected '=', but got '" << peek().value << "'\n"; 
            _error = true;
        }

        advance();

        BaseNode value = parse_expression();
        skip_semicolon();
        
        return VariableDefinition(identifier, std::make_shared<BaseNode>(value), line, column, file);
    }


    void Parser::skip_semicolon() {
        if (match(TokenType::Semicolon)) {
            advance();
        }
    }


    void Parser::advance() {
        if (index >= tokens.size()) return;
        index++;
    }
    
    Token Parser::peek() {
        if (index >= tokens.size()) {
            return tokens[tokens.size() - 1];
        }

        return tokens[index];
    }
    
    Token Parser::consume() {
        Token token = peek();
        advance();
        return token;
    }
    
    bool Parser::match(TokenType type) {
        if (peek().type == type) {
            return true;
        }
        
        return false;
    }
}