#pragma once

#include <string>
#include <vector>
#include <memory>

namespace ngopi {
    class BaseNode {
        
    };

    class File : public BaseNode {
        public:
        std::vector<std::shared_ptr<BaseNode>> value;
        std::size_t line;
        std::size_t column;
        std::string file;

        File(std::vector<std::shared_ptr<BaseNode>> value, std::size_t line, std::size_t column, std::string file)
        : value(value), line(line), column(column), file(file) {}

        ~File() {}
    };

    class StringLiteral : public BaseNode {
        public:
        std::string value;
        std::size_t line;
        std::size_t column;
        std::string file;

        StringLiteral(std::string value, std::size_t, std::size_t column, std::string file) 
        : value(value), line(line), column(column), file(file) {}
    };

    class FloatLiteral : public BaseNode {
        public:
        float value;
        std::size_t line;
        std::size_t column;
        std::string file;

        FloatLiteral(float value, std::size_t, std::size_t column, std::string file) 
        : value(value), line(line), column(column), file(file) {}
    };

    class BoolLiteral : public BaseNode {
        public:
        bool value;
        std::size_t line;
        std::size_t column;
        std::string file;

        BoolLiteral(bool value, std::size_t, std::size_t column, std::string file) 
        : value(value), line(line), column(column), file(file) {}
    };

    class IntLiteral : public BaseNode {
        public:
        int value;
        std::size_t line;
        std::size_t column;
        std::string file;

        IntLiteral(int value, std::size_t, std::size_t column, std::string file) 
        : value(value), line(line), column(column), file(file) {}
    };

    class BinaryOperation : public BaseNode {
        public:
        std::shared_ptr<BaseNode> left;
        std::shared_ptr<BaseNode> right;
        std::string operand;
        
        std::size_t line;
        std::size_t column;
        std::string file;

        BinaryOperation(std::shared_ptr<BaseNode> left, std::shared_ptr<BaseNode> right, std::string operand, std::size_t line, std::size_t column, std::string file) 
        : left(left), right(right), operand(operand), line(line), column(column), file(file) {}
    };

    class UnaryOperation : public BaseNode {
        public:
        std::shared_ptr<BaseNode> value;
        std::string operand;
        
        std::size_t line;
        std::size_t column;
        std::string file;

        UnaryOperation(std::shared_ptr<BaseNode> value, std::string operand, std::size_t line, std::size_t column, std::string file) 
        : value(value), operand(operand), line(line), column(column), file(file) {}
    };

    class Variable : public BaseNode {
        public:
        std::string value;
        
        std::size_t line;
        std::size_t column;
        std::string file;

        Variable(std::string value, std::size_t line, std::size_t column, std::string file) 
        : value(value), line(line), column(column), file(file) {}
    };

    class Nullable : public BaseNode {
        public:
        std::size_t line;
        std::size_t column;
        std::string file;

        Nullable(std::size_t line, std::size_t column, std::string file) 
        : line(line), column(column), file(file) {}
    };

    class VariableDefinition : public BaseNode {
        public:
        std::string name;
        std::shared_ptr<BaseNode> value;
        
        std::size_t line;
        std::size_t column;
        std::string file;

        VariableDefinition(std::string name, std::shared_ptr<BaseNode> value, std::size_t line, std::size_t column, std::string file) 
        : name(name), value(value), line(line), column(column), file(file) {}
    };

    class FunctionCall : public BaseNode {
        public:
        std::shared_ptr<BaseNode> function;
        std::vector<std::shared_ptr<BaseNode>> arguments;

        std::size_t line;
        std::size_t column;
        std::string file;

        FunctionCall(std::shared_ptr<BaseNode> function, std::vector<std::shared_ptr<BaseNode>> arguments, std::size_t line, std::size_t column, std::string file) 
        : function(function), arguments(arguments), line(line), column(column), file(file) {}
    };

    class MemberLoopup : public BaseNode {
        public:
        std::shared_ptr<BaseNode> _lookFor;
        std::shared_ptr<BaseNode> _member;

        std::size_t line;
        std::size_t column;
        std::string file;

        MemberLoopup(std::shared_ptr<BaseNode> _lookFor, std::shared_ptr<BaseNode> _member, std::size_t line, std::size_t column, std::string file) 
        : _lookFor(_lookFor), _member(_member), line(line), column(column), file(file) {}
    };
};