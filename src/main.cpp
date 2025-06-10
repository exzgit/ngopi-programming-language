#include "main.hpp"

int main(int argc, char* argv[]) {
    
    std::string code = "int __main__() {\n";
    code += "\tlet str name = \"John Doe\"\n";
    code += "}\n";
    
    ngopi::Lexer lexer(code, "___");
    auto tokens = lexer.start();

    for (auto token : tokens) {
        std::cout << token.to_string() << std::endl;
    }

    return 0;
}