#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <cctype>

//Token types for the tokens that the lexer will return
enum class TokenType{
    KEYWORD,
    IDENTIFIER,
    STRING,
    NUMBER,
    OPERATOR,
    PUNCTUATION,
    END_OF_FILE
};

//Token struct holds the type and value of the token
struct Token{
    TokenType type;
    std::string value;
};

class Lexer{
    public:
    explicit Lexer(std::string input);
        std::vector<Token> tokenize();
    private:
        std::string input;
        int position;

        void skipWhitespace();
        Token readWord();
        Token readNumber();
        Token readString();
        Token readOperator();
        Token readPunctuation();
};

#endif