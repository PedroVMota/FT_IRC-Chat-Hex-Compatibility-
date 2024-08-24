#pragma once

#include <IrcMainHeader.hpp>
#include "Client.hpp"
#include <ostream>

using namespace std;
class Server;
class PollConnection
{

public:


    map<int, Client *> connectionList;
    vector<pollfd> connectionSockets;

    int numClients;
    sockaddr_in sI;
    PollConnection() : connectionList(), connectionSockets(), numClients(0){};

    void                    addClient(int, Server *);
    void                    delClient(Client *);
    void                    closeConnecions(){
        for(int i = 3; i - 3 < numClients; i++)
        {
            if( connectionList.at(i) == 0)
                continue;
            delete connectionList.at(i); 
            connectionList.erase(i);
        }
        
    }
    int                     getSize() const;
    Client *                operator[](size_t index)
    {
        if (index >= this->connectionList.size())
            throw out_of_range("Index out of range\n");
        return this->connectionList[index];
    }

    map<int, Client *>          getClients() const;
    vector<pollfd>          getPoll() const;
    pollfd                GetSpecifPoll(int);
    Client *                GetSpecifClient(int);


    
};

// GET CONNECTION AND SOCKETS




ostream &operator<<(ostream &os, PollConnection const &other);