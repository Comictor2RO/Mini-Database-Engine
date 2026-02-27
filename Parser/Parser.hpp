#ifndef PARSER_HPP
#define PARSER_HPP

#include "../Lexer/Lexer.hpp"
#include "../SelectStatement/SelectStatement.hpp"
#include "../InsertStatement/InsertStatement.hpp"
#include "../DeleteStatement/DeleteStatement.hpp"
#include <vector>

class Parser {
    public:
        Parser(const std::vector<Token> &tokens);
        Statement *parse();
    private:
        std::vector<Token> tokens;
        int position;

        Token currentToken();
        Token consumeToken();

        SelectStatement *parseSelect();
        InsertStatement *parseInsert();
        DeleteStatement *parseDelete();
        Condition *parseCondition();
};


#endif