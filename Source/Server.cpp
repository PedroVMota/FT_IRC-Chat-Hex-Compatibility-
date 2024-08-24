#include <Server.hpp>
#include <Channel.hpp>

Server ::Server() : _conn(), _port(), _pass() {}

Server::~Server()
{
    this->_conn.closeConnecions();
    for (map<string, Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
    {
        delete it->second;
    }
    _channels.clear();
}

Server ::Server(string const &port, string const &pass) : _conn(), _port(port), _pass(pass), run(true)
{

    // check pass and port
    this->run = true;
    if (port.length() == 0 || pass.length() == 0)
        throw std::runtime_error("Paramters are not valid");
    // creating server socket
    int SocketServer = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    if (SocketServer == -1)
        throw std::runtime_error("Socket initialization went wrong");
    // custom options
    setsockopt(SocketServer, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    // prepare the process with ip:port
    this->_conn.sI.sin_family = AF_INET;
    this->_conn.sI.sin_addr.s_addr = INADDR_ANY;
    this->_conn.sI.sin_port = htons(atoi(port.c_str()));
    if (bind(SocketServer, (sockaddr *)&this->_conn.sI, sizeof(this->_conn.sI)) == -1)
        throw std::runtime_error("Bind System went wrong!");
    if (listen(SocketServer, FOPEN_MAX) == -1)
        throw std::runtime_error("Listen System went wrong!");
    // Add client to the server
    _conn.addClient(SocketServer, this);
}

Channel *Server::getChannel(string name)
{
    if (this->_channels.find(name) == this->_channels.end())
        return NULL;
    return this->_channels[name];
}

bool Server::serverLoop()
{
    string buff;
    while (this->run)
    {
        int events = poll(this->_conn.connectionSockets.data(), this->_conn.numClients, -1);
        while (events > 0)
        {
            if (this->_conn.connectionSockets[0].revents & POLLIN)
            {
                socklen_t addrlen = sizeof(this->_conn.sI);
                int newClient = accept(this->_conn.connectionSockets[0].fd, (sockaddr *)&this->_conn.sI, &addrlen);
                if (newClient == -1)
                    return false;
                this->_conn.addClient(newClient, this);
            }
            for (map<int, Client *>::iterator it = this->_conn.connectionList.begin(); it != this->_conn.connectionList.end(); it++)
            {
                cout << this->_conn.connectionList.size() << endl;
                cout << "Selecting Client #" << (*it).second->socket.fd << endl;
                int readResult = ((it)->second)->readClient(buff);
                if (readResult == 1)
                {
                    this->_conn.delClient(it->second);
                    break;
                }
            }
            events--;
        }
    }
    return false;
}

Channel *Server::addChannel(string name)
{
    Channel *newChannel = new Channel(name);
    if (this->_channels.find(name) != this->_channels.end())
        return NULL;
    this->_channels[name] = newChannel;
    return newChannel;
}

void Server::op(IrcMessage &m, Client *c)
{
    (void)m;
    (void)c;
}
void Server::join(IrcMessage &m, Client *c)
{
    vector<string> p = m.getParams();
    if (!c->getAccept())
    {
        c->writeClient((string &)"ERROR :You have not registered\r\n");
        return;
    }
    if (p[0][0] == '#')
    {
        string ret = ":" +
                     c->getNick() + "!" + c->getName() + " " + m._list + "\r\n";
        c->writeClient(ret);
        c->addChannel(p[0]);
        if (c->getChannel(p[0])->getClients().size() == 1)
            c->getChannel(p[0])->setOperator(c);
    }
    else
    {

        string ret = p[0] + ": No such channel\r\n";
        c->writeClient(ret);
    }
}
void Server::privmsg(IrcMessage &m, Client *c)
{
    string channelName = m.getParams()[0] + '\r';
    map<string, Channel *> _channels = c->getChannelList();
    if (_channels.find(channelName) == _channels.end())
        return;
    string tt = ":" + c->getNick() + "!" + c->getName() + " " + m._list + "\r\n";
    this->_channels[channelName]->broadcast(tt, c);
}
void Server::quit(IrcMessage &m, Client *c)
{
    (void)m;
     for(std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
        it->second->removeClient(c);
    }
    this->_channels.clear();

}
void Server::who(IrcMessage &m, Client *c)
{
    (void)m;
    (void)c;
}
