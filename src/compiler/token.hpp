#pragma once

#include <vector>
#include <string>

namespace ngopi {

    enum class TokenType {
        // General Token
        Error,
        Unknown,
        Eof,
        Identifier,

        // Literal Token
        StringLiteral,
        CharLiteral,
        NumberLiteral,
        True,
        False,
        Nullable,

        // Keyword Token
        If,
        Else,
        Let,
        Const,
        Static,
        Public,
        Int,
        Float,
        Char,
        Str,
        Bool,
        Self,
        New,
        Import,
        Use,
        As,
        Is,
        In,
        For,
        While,
        Function,
        Class,
        Struct,
        Enum,
        Typename,
        Interface,
        Namespace,
        Switch,
        Case,
        Default,
        Break,
        Return,
        Continue,
        
        // Punctuation Token
        Plus,
        Minus,
        Multiply,
        Divide,
        Semicolon,
        Colon,
        Power,
        Percent,
        And,
        At,
        Exclamation,
        Or,
        Equal,
        Double,
        PlusEqual,
        MinusEqual,
        DivideEqual,
        ColonEqual,
        PowerEqual,
        PercentEqual,
        Increment,
        Decrement,
        Comma,
        Dot,
        Less,
        LessEqual,
        Greater,
        GreaterEqual,
        LeftParenthise,
        RightParenthise,
        LeftBracket,
        RightBracket,
        LeftCurly,
        RightCurly
    };


    class Token {
        public:
        TokenType type;
        std::string value;
        std::size_t line;
        std::size_t column;
        bool is_error;
        std::string error_message;
        std::string file;

        Token(
            TokenType type,
            std::string value,
            std::string file,
            std::size_t line,
            std::size_t column
        );

        ~Token();

        std::string to_string();
    };
};