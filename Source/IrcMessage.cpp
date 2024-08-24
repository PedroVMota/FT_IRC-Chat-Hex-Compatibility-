#include "IrcMessage.hpp"

#include <sstream>

std::vector<std::string> splitString(const std::string &str){
    std::vector<std::string> result;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, ' ') || std::getline(iss, token, '\n'))
        result.push_back(token);
    return result;
}

IrcMessage::IrcMessage(const std::string &msg) : _list(msg){
    std::string _cmd;
    std::string _par;

    if (_list.empty() || _list == ".\r\n") return ;// Check if _list is empty or contains only ".\r\n"
    
    std::vector<std::string> tokens = splitString(msg);
    this->_type = tokens[0];
    this->_params.assign(tokens.begin() + 1, tokens.end()); // Assign the tokens vector from the second position to the end to _params
}

IrcMessage::~IrcMessage(){}

std :: string IrcMessage :: getCommand(){
    return this->_type;
}

std :: vector<std :: string> IrcMessage :: getParams()
{
    return this->_params; 
}

void IrcMessage :: print(){
    if (this->_list.empty() || _list == ".\r\n") return ;

    std::cout << "Command: " << this->_type << std::endl;
    std :: cout << "Params: ";
    for (size_t i = 0; i < _params.size(); i++)
            std::cout << _params[i] << " ";
    std::cout << std::endl;
}