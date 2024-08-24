#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <IrcMainHeader.hpp>
#include <IrcMessage.hpp>

class Server;
class Channel;
using namespace std;

class Client{
    private:
        string _pass, _serverPass;
        string _nick;
        string _user;
        Server      *_server;
        bool        _isOperator;
        bool        _accepted;
        map<string, Channel *> _channels;

    public:
        pollfd      socket;
        Client(int, Server *);
        ~Client();

        int readClient(string &);
        int writeClient(string &);

        bool getOperator() const;
        const string& getName() const;
        const string& getPass() const;
        const string& getNick() const;
        Channel * addChannel(string);
        pollfd *getPoll();

        void removeChannel(const std::string& channelName);



        int parseMessage(IrcMessage &);
        void join(string);
        void setPass(const string &newPass){
            this->_pass = newPass;
        }void setAccept(bool value){
            this->_accepted = value;
        }
        bool getAccept() { return this->_accepted; }

        Channel *getChannel(string name){
            return this->_channels[name];
        }
        map<string, Channel *> getChannelList(){
            return this->_channels;
        }
};

#endif