#include <PollConnection.hpp>
#include <Server.hpp>


void PollConnection::addClient(int socket, Server *serv)
{
    Client *s = new Client(socket, serv);
    this->connectionList[socket] = s;
    this->connectionSockets.push_back(*s->getPoll());
    std::cout << "AddClient: " << s->getPoll()->fd << endl;
    this->numClients++;
}

void PollConnection::delClient(Client *c)
{
    this->numClients--;
    int fd = c->socket.fd;
    if(!c)
    {
        std::cout << "Non existed client!\n";
        return ;
    }
    std::cout << "Removing Client >>" << c->getPoll()->fd << endl;
    delete this->connectionList.at(c->getPoll()->fd);
    this->connectionList.erase(fd);

    for(vector<pollfd>::iterator it = this->connectionSockets.begin(); it != this->connectionSockets.end(); it++)
    {
        if((*it).fd == fd)
        {
            this->connectionSockets.erase(it);
            return;
        }
    }
}

pollfd PollConnection::GetSpecifPoll(int index)
{
    if (index > this->getSize())
        throw runtime_error("The index is bigger that the max");
    return this->connectionSockets[index];
}

Client *PollConnection::GetSpecifClient(int index)
{
    if (index > this->getSize())
        throw runtime_error("The index is bigger that the max");
    return this->operator[](index);
}

ostream &operator<<(ostream &os, PollConnection const &other)
{
    os << "Number of Clients: " << other.getClients().size() << endl;
    os << "Number of Polls: " << other.getPoll().size() << endl;
    return os;
}



// ======================================== GETTERS ========================================

vector<pollfd> PollConnection::getPoll() const {
    return this->connectionSockets;
}

map<int, Client *> PollConnection::getClients() const {
    return connectionList;
}

int PollConnection::getSize() const {
    return connectionList.size();
}
