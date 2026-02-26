#ifndef STATEMENT_HPP
#define STATEMENT_HPP

class Statement{
    public:
        virtual void execute() = 0;
        virtual ~Statement() = default;
};

#endif