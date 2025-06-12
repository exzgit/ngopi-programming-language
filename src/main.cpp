#include "main.hpp"

int main(int argc, char* argv[]) {
    
    std::string code = "let name = \"John Doe\"";
    
    ngopi::Lexer lexer(code, "___");
    auto tokens = lexer.start();

    ngopi::Parser parser(tokens);
    auto node = parser.parse();

    return 0;
}