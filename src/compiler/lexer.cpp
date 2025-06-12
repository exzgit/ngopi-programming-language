#include "./lexer.hpp"

namespace ngopi {

    /**
     * Main entry point for the lexical analysis process.
     * Reads the source code character by character and generates a sequence of tokens.
     * Handles different types of tokens:
     * - Numbers (integers and decimals)
     * - Strings (with escape sequences)
     * - Identifiers (variables, functions, etc)
     * - Punctuation (operators and symbols)
     * 
     * Returns a vector of tokens that can be used by the parser.
     */
    std::vector<Token> Lexer::start() {
        std::vector<Token> tokens;

        while (!is_at_end()) {
            if (isdigit(peek())) {
                std::cout << peek() << std::endl;
                tokens.push_back(get_number_token());        
            } else if (peek() == '"' || peek() == '\'') {
                tokens.push_back(get_string_token());
            } else if (isalpha(peek()) || peek() == '_') {
                tokens.push_back(get_identifier_token());
            } else if (peek() == '#') {
                skip_comment();
            } else if (ispunct(peek())) {
                tokens.push_back(get_punctuation_token());
            } else if (isspace(peek())) {
                skip_whitespace();
            } else {
                std::string message = "Error at" + file;
                message += ", " + line;
                message += " : " + column; 
                message += "\n";
                message += "Syntax Error: Unexpected token '" + peek();
                message += "'\n";                
                std::string value(1, peek());

                std::cout << message;
                Token token(
                    TokenType::Error, value, file, line, column
                );
                token.is_error = true;
                token.error_message = message;

                tokens.push_back(token);
                
                advance();
            }
        }        
        
        tokens.push_back(Token(TokenType::Eof, "\0", file, line, column));
        return tokens;
    }    
    
    /**
     * Processes numeric literals in the source code.
     * Handles both integer and decimal numbers.
     * Continues reading until it finds a non-digit, non-alpha, and non-dot character.
     * This allows for future support of different number formats (hex, binary, etc).
     * 
     * Returns a Token with type NumberLiteral and the full number as its value.
     */
    Token Lexer::get_number_token() {
        std::size_t ln = line;
        std::size_t cn = column;
        std::string value = "";

        while (isdigit(peek()) || isalpha(peek()) || peek() == '.') {
            value += peek_next();
        }        
        
        Token token(TokenType::NumberLiteral, value, file, ln, cn);

        return token;
    }    
    
    /**
     * Handles string literals in the source code.
     * Supports both single and double quotes.
     * Processes escape sequences:
     * - \n for newline
     * - \r for carriage return
     * - \t for tab
     * - \\ for backslash
     * 
     * Throws an error if it encounters unescaped newlines or invalid characters.
     * Returns a Token with type StringLiteral and the processed string as its value.
     */
    Token Lexer::get_string_token() {
        std::size_t ln = line;
        std::size_t cn = column;
        char mark = peek_next();
        std::string value = "";

        while (peek() != mark) {
            
            if (peek() == '\n' || peek() == '\t' || peek() == '\r') {
                std::string message = "Error at" + file;
                message += ", " + line;
                message += " : " + column; 
                message += "\n";
                message += "Syntax Error: Unexpected token '" + peek();
                message += "'\n";                
                std::cout << message;

                exit(EXIT_FAILURE);
            } 
            
            if (peek() == '\\') {
                advance();
                if (peek() == '\\') {
                    value += "\\";
                    advance();
                } else if (peek() == 'n') {
                    value += "\n";
                    advance();
                } else if (peek() == 'r') {
                    value += "\r";
                    advance();
                } else if (peek() == 't') {
                    value += "\t";
                    advance();
                } else {
                    value += "\\";
                }
            }
                
            value += peek_next();
        }        

        advance();
        
        Token token(TokenType::StringLiteral, value, file, ln, cn);

        return token;
    }    
    
    /**
     * Processes identifiers and keywords in the source code.
     * An identifier starts with a letter or underscore and can contain:
     * - Letters (a-z, A-Z)
     * - Numbers (0-9)
     * - Underscores (_)
     * 
     * Checks if the identifier matches any language keywords:
     * - Control flow (if, else, for, while, etc)
     * - Declarations (let, const, function, class, etc)
     * - Types (int, float, str, bool, etc)
     * - Values (true, false, null)
     * 
     * Returns appropriate Token type for keywords, or Identifier for variables/functions.
     */    Token Lexer::get_identifier_token() {
        std::size_t ln = line;
        std::size_t cn = column;
        std::string value = "";

        while (isalpha(peek()) || isdigit(peek()) || peek() == '_') {
            value += peek_next();
        }

        TokenType type = TokenType::Identifier;
        
        // Keywords
        if (value == "if") {
            type = TokenType::If;
        } else if (value == "else") {
            type = TokenType::Else;
        } else if (value == "let") {
            type = TokenType::Let;
        } else if (value == "const") {
            type = TokenType::Const;
        } else if (value == "static") {
            type = TokenType::Static;
        } else if (value == "public") {
            type = TokenType::Public;
        } else if (value == "int") {
            type = TokenType::Int;
        } else if (value == "float") {
            type = TokenType::Float;
        } else if (value == "char") {
            type = TokenType::Char;
        } else if (value == "str") {
            type = TokenType::Str;
        } else if (value == "bool") {
            type = TokenType::Bool;
        } else if (value == "self") {
            type = TokenType::Self;
        } else if (value == "new") {
            type = TokenType::New;
        } else if (value == "import") {
            type = TokenType::Import;
        } else if (value == "use") {
            type = TokenType::Use;
        } else if (value == "as") {
            type = TokenType::As;
        } else if (value == "is") {
            type = TokenType::Is;
        } else if (value == "in") {
            type = TokenType::In;
        } else if (value == "for") {
            type = TokenType::For;
        } else if (value == "while") {
            type = TokenType::While;
        } else if (value == "function") {
            type = TokenType::Function;
        } else if (value == "class") {
            type = TokenType::Class;
        } else if (value == "struct") {
            type = TokenType::Struct;
        } else if (value == "enum") {
            type = TokenType::Enum;
        } else if (value == "typename") {
            type = TokenType::Typename;
        } else if (value == "interface") {
            type = TokenType::Interface;
        } else if (value == "namespace") {
            type = TokenType::Namespace;
        } else if (value == "switch") {
            type = TokenType::Switch;
        } else if (value == "case") {
            type = TokenType::Case;
        } else if (value == "default") {
            type = TokenType::Default;
        } else if (value == "break") {
            type = TokenType::Break;
        } else if (value == "return") {
            type = TokenType::Return;
        } else if (value == "continue") {
            type = TokenType::Continue;
        } else if (value == "true") {
            type = TokenType::True;
        } else if (value == "false") {
            type = TokenType::False;
        } else if (value == "null") {
            type = TokenType::Nullable;
        }

        Token token(type, value, file, ln, cn);
        return token;
    }    
    
    /**
     * Processes operators and punctuation marks in the source code.
     * Handles both single and double character operators.
     * 
     * Double character operators:
     * - Arithmetic (++, --, +=, -=, *=, /=, **, %=)
     * - Comparison (==, <=, >=)
     * - Assignment (:=)
     * 
     * Single character operators:
     * - Basic arithmetic (+, -, *, /, %)
     * - Comparison (<, >)
     * - Logical (&, |, !)
     * - Other (@, =, ., ,)
     * 
     * Also handles brackets and parentheses (), [], {}
     * Returns appropriate Token type based on the operator or punctuation found.
     */
    Token Lexer::get_punctuation_token() {
        std::size_t ln = line;
        std::size_t cn = column;
        std::string value = "";
        char current = peek();
        char next = peek_next();
        
        TokenType type = TokenType::Unknown;
        
        // Double character operators
        if (current == '+' && next == '+') {
            type = TokenType::Increment;
            value = "++";
            advance();
        } else if (current == '-' && next == '-') {
            type = TokenType::Decrement;
            value = "--";
            advance();
        } else if (current == '+' && next == '=') {
            type = TokenType::PlusEqual;
            value = "+=";
            advance();
        } else if (current == '-' && next == '=') {
            type = TokenType::MinusEqual;
            value = "-=";
            advance();
        } else if (current == '*' && next == '*') {
            type = TokenType::Power;
            value = "**";
            advance();
        } else if (current == '*' && next == '=') {
            type = TokenType::PowerEqual;
            value = "*=";
            advance();
        } else if (current == '/' && next == '=') {
            type = TokenType::DivideEqual;
            value = "/=";
            advance();
        } else if (current == '%' && next == '=') {
            type = TokenType::PercentEqual;
            value = "%=";
            advance();
        } else if (current == ':' && next == '=') {
            type = TokenType::ColonEqual;
            value = ":=";
            advance();
        } else if (current == '<' && next == '=') {
            type = TokenType::LessEqual;
            value = "<=";
            advance();
        } else if (current == '>' && next == '=') {
            type = TokenType::GreaterEqual;
            value = ">=";
            advance();
        } else if (current == '=' && next == '=') {
            type = TokenType::Equal;
            value = "=";
            advance();
        }
        // Single character operators and punctuation
        else {
            value = std::string(1, current);
            switch (current) {
                case '+': type = TokenType::Plus; break;
                case '-': type = TokenType::Minus; break;
                case '*': type = TokenType::Multiply; break;
                case '/': type = TokenType::Divide; break;
                case '%': type = TokenType::Percent; break;
                case ';': type = TokenType::Semicolon; break;
                case ':': type = TokenType::Colon; break;
                case '&': type = TokenType::And; break;
                case '@': type = TokenType::At; break;
                case '!': type = TokenType::Exclamation; break;
                case '|': type = TokenType::Or; break;
                case '=': type = TokenType::IsEqual; break;
                case ',': type = TokenType::Comma; break;
                case '.': type = TokenType::Dot; break;
                case '<': type = TokenType::Less; break;
                case '>': type = TokenType::Greater; break;
                case '(': type = TokenType::LeftParenthise; break;
                case ')': type = TokenType::RightParenthise; break;
                case '[': type = TokenType::LeftBracket; break;
                case ']': type = TokenType::RightBracket; break;
                case '{': type = TokenType::LeftCurly; break;
                case '}': type = TokenType::RightCurly; break;
                default: type = TokenType::Unknown;
            }
        }
        
        Token token(type, value, file, ln, cn);
        return token;
    }
      
    /**
     * Skips over any whitespace characters in the source code.
     * This includes:
     * - Spaces
     * - Tabs
     * - Newlines
     * - Carriage returns
     * 
     * Advances the lexer position until a non-whitespace character is found.
     */
    void Lexer::skip_whitespace() {
        while (isspace(peek())) {
            advance();
        }
    }
      
    /**
     * Handles single-line comments in the source code.
     * Comments start with # and continue until the end of the line.
     * Similar to Python's comment style.
     * 
     * Example:
     * # This is a comment
     * 
     * Advances the lexer position until the end of the comment line.
     */
    void Lexer::skip_comment() {
        if (peek() == '#') {
            while (peek() != '\n') {
                advance();
            }
        }
    }
      
    /**
     * Moves the lexer one character forward in the source code.
     * Keeps track of line and column numbers for error reporting.
     * 
     * Special handling for newline characters:
     * - Increments the line counter
     * - Resets the column counter to 0
     * 
     * For all other characters:
     * - Increments both index and column counters
     */
    void Lexer::advance() {
        if (peek() == '\n') {
            line += 1;
            column = 0;
        }

        column += 1;
        index += 1;
    }    
    
    /**
     * Looks at the current character in the source code without advancing.
     * Acts as a lookahead function for the lexer.
     * 
     * Returns:
     * - The current character if within source code bounds
     * - '\0' if at the end of the source code
     * 
     * Used by other lexer functions to determine token types
     * without consuming characters.
     */    char Lexer::peek() {
        if (is_at_end()) {
            return '\0';
        }
        return source[index];
    }
    
    /**
     * Gets the current character and advances the lexer.
     * Combines peek() and advance() into a single operation.
     * 
     * Returns:
     * - The current character before advancing
     * 
     * Commonly used when building token values character by character,
     * such as in numbers, strings, and identifiers.
     */
    char Lexer::peek_next() {
        char c = peek();
        advance();
        return c;
    }    

    /**
     * Checks if the lexer has reached the end of the source code.
     * 
     * Returns true if either:
     * - Current index is beyond the source length
     * - Current character is the null terminator
     * 
     * Used to prevent buffer overruns and ensure safe
     * termination of lexical analysis.
     */
    bool Lexer::is_at_end() {
        if (index >= source.length() || source[index] == '\0') {
            return true;
        }

        return false;
    }
}