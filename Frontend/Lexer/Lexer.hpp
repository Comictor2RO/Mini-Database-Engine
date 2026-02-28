#ifndef LEXER_HPP
#define LEXER_HPP

#include "Token.hpp"
#include <string>
#include <vector>
#include <cctype>

class Lexer{
    public:

        //Constructor
        explicit Lexer(std::string input);

        //Method
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
        Token readWildcard();
};

#endif