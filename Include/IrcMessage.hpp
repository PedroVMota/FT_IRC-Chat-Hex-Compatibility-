#pragma once
#include "IrcMainHeader.hpp"

class IrcMessage
{
private:
    std::string _type;
    std::vector<std::string>    _params;


public:
    std::string _list;
    IrcMessage(const std::string &msg);
    ~IrcMessage();
    std::string getCommand();
    std::vector<std::string> getParams();
    void print();
};