/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:07:46 by psoares-          #+#    #+#             */
/*   Updated: 2024/04/29 20:08:56 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Channel.hpp>

Channel ::Channel(const std::string &name) : _name(name), _clients() {}
const std::string &Channel::getName() const { return this->_name; }
const std::vector<Client *> &Channel::getClients() { return this->_clients; }
void Channel::addClient(Client *client) { this->_clients.push_back(client); }
void Channel::removeClient(Client *client)
{
    if (client == NULL)
    {
        std::cout << "No client\n";
        return ;
    }
    std::vector<Client *>::iterator it = std::remove(_clients.begin(), _clients.end(), client);
    _clients.erase(it, _clients.end());
}

// GET CONNECTION AND SOCKETS
void Channel::broadcast(std::string &message, Client *sender)
{
    std::vector<Client *>::iterator it = this->_clients.begin();
    std::vector<Client *> sendedClients;
    while (it != this->_clients.end())
    {
        if (*it != sender)
        {
            (*it)->writeClient(message);
            sendedClients.push_back((*it));
        }
        ++it;
    }
}

ostream &operator<<(ostream &os, Channel &other)
{
    os << "Channel: " << other.getName() << std::endl;
    os << "Clients: " << std::endl;
    for (std::vector<Client *>::const_iterator it = other.getClients().begin(); it != other.getClients().end(); ++it)
        os << "    " << (*it)->getNick() << std::endl;
    return os;
}

bool Channel::isOperator(Client &client)
{
    std::vector<Client *>::iterator it;

    it = std::find(_clients.begin(), _clients.end(), &client);
    if (it != _clients.end())
        return true;
    return false;
}

bool Channel::isOperator(std::string clientName)
{
    std::vector<Client *>::iterator it;
    for (it = _clients.begin(); it != _clients.end(); ++it)
        if (clientName.compare((*it)->getNick()) == 0)
            return true;
    return false;
}

void Channel::setOperator(Client *client)
{
    std::vector<Client *>::iterator it = std::find(_operator.begin(), _operator.end(), client);
    if (it == _operator.end())
        _operator.push_back(client);
}

Channel::~Channel() {};