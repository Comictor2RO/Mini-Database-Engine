#include "Parser.hpp"

Parser::Parser(const std::vector<Token> &tokens)
    : tokens(tokens), position(0)
{}

Token Parser::currentToken()
{
    return tokens[position];
}

Token Parser::consumeToken()
{
    Token t = currentToken();
    position++;
    return t;
}

CreateStatement *Parser::parseCreate() {
    consumeToken(); //Jumps over CREATE
    consumeToken(); //Jumps over TABLE
    std::string table = consumeToken().value; //Saves table name

    std::vector<Columns> columns;

    consumeToken(); //Jumps over (

    while (currentToken().value != ")" && currentToken().type != TokenType::END_OF_FILE)
    {
        if (currentToken().value == ",")
        {
            consumeToken(); //Jumps over ,
            continue;
        }
        Columns col;
        col.name = consumeToken().value; //Column name  ex: "id"
        col.type = consumeToken().value; //Column type  ex: "INT"
        columns.push_back(col);
    }

    consumeToken(); //Jumps over )

    return new CreateStatement(table, columns);
}

SelectStatement *Parser::parseSelect()
{
    consumeToken(); //Jumps over SELECT

    std::vector<std::string> columns;
    std::string table;

    while (currentToken().value != "FROM" && currentToken().type != TokenType::END_OF_FILE) //Checks until find FROM
    {
        if (currentToken().value == ",")
            consumeToken(); //Skips the punctuation
        else
            columns.push_back(consumeToken().value); //Saves the columns
    }

    consumeToken(); //Jumps over FROM
    table = consumeToken().value; //Name of the table

    Condition *condition = nullptr;
    if (currentToken().value == "WHERE") //Checks if there is a condition
    {
        consumeToken(); //Jumps over WHERE
        condition = parseCondition(); //Saves the condition
    }

    return new SelectStatement(columns, table, condition);
}

InsertStatement *Parser::parseInsert()
{
    consumeToken();
    consumeToken();

    std::string table = consumeToken().value; //Save table name
    std::vector<std::string> values;
    std::vector<std::string> columns;
    while (currentToken().value != "VALUES" && currentToken().type != TokenType::END_OF_FILE)
    {
        if (currentToken().value == "," || currentToken().value == ")" || currentToken().value == "(")
            consumeToken(); //Jumps over punctuation
        else
            columns.push_back(consumeToken().value); //Saves the columns
    }

    consumeToken(); //Jumps over VALUES

    while (currentToken().type != TokenType::END_OF_FILE)
    {
        if (currentToken().type == TokenType::PUNCTUATION)
            consumeToken(); //Jumps over punctuation
        else
            values.push_back(consumeToken().value); //Saves the values
    }

    return new InsertStatement(table, columns, values);
}

DeleteStatement *Parser::parseDelete()
{
    consumeToken(); //Jumps over DELETE
    consumeToken(); //Jumps over FROM

    std::string table = consumeToken().value;

    Condition *condition = nullptr;
    if (currentToken().value == "WHERE")
    {
        consumeToken(); //Jumps over WHERE
        condition = parseCondition(); //Saves the condition
    }

    return new DeleteStatement(table, condition);
}

Condition *Parser::parseCondition()
{
    std::string column = consumeToken().value;
    std::string op = consumeToken().value;
    std::string value = consumeToken().value;

    Condition *condition = new Condition();
    condition->column = column;
    condition->value = value;
    condition->op = op;
    return condition;
}

Statement *Parser::parse()
{
    Token token = currentToken();

    if (token.type != TokenType::KEYWORD)
        return nullptr;
    if (token.value == "SELECT")
        return parseSelect();
    if (token.value == "INSERT")
        return parseInsert();
    if (token.value == "DELETE")
        return parseDelete();
    if (token.value == "CREATE")
        return parseCreate();
    return nullptr;
}