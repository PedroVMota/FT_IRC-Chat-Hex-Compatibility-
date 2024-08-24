#pragma once
#include <PollConnection.hpp>
#include <IrcMainHeader.hpp>

using namespace std;


class Channel;

class Server
{
private: 
    PollConnection _conn;
    string _port, _pass;
    map <string, Channel *> _channels;
    bool run;
public:
    Server();
    Server(string const &, string const&);
    ~Server();

    void stop() { this->run = false;};
    void start() { this->run = true;};


    bool ircMensageContent(string aa);
    Channel * addChannel(string);
    Channel *getChannel(string);
    string getPass() const { return this->_pass; }
    bool serverLoop();
    void removeClientFromChannel(string &);


    void op(IrcMessage &, Client *);
    void join(IrcMessage &, Client *);
    void privmsg(IrcMessage &, Client *);
    void quit(IrcMessage &, Client *);
    void who(IrcMessage &, Client *);

    
    
};
