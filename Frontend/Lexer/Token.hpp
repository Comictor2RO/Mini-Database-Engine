#ifndef TOKEN_HPP
#define TOKEN_HPP

#include "TokenType.hpp"
#include <string>

//Token struct holds the type and value of the token
struct Token{
    TokenType type;
    std::string value;
};

#endif