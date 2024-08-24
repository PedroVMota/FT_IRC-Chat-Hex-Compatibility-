#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <IrcMainHeader.hpp>
#include <Server.hpp>
#include <string>

class Client;

class Channel
{

private:
    std::string _name;
    std::vector<Client *> _clients;
    std::vector<Client *> _operator;

public:
    Channel(const std::string &name);
    ~Channel();

    const std::string &getName() const;
    const std::vector<Client *> &getClients();

    void addClient(Client *client);
    void broadcast(std::string &message, Client *sender);
    void removeClient(Client *client);
    bool isOperator(Client &client);
    bool isOperator(std::string name);
    void setOperator(Client *client);
    string getName() { return _name; }
};

#endif // CHANNEL_HPP