#include "token.hpp"

namespace ngopi {
    Token::Token(
        TokenType type,
        std::string value,
        std::string file,
        std::size_t line,
        std::size_t column
    ) : type(type), value(value), file(file), line(line), column(column), is_error(false), error_message("") {}

    Token::~Token() {}

    std::string Token::to_string() {
        std::string result = "Token [";
        result += value + "  ";
        result += is_error ? "Valid" : "Error";
        result += " ]";
        return result;
    }
}