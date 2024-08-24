#include <Client.hpp>
#include <Channel.hpp>
#include <Server.hpp>


bool Client::getOperator() const { return this->_isOperator; }
const string& Client::getName() const { return this->_user; }
const string& Client::getPass() const { return this->_pass; }
const string& Client::getNick() const { return this->_nick; }
pollfd *Client::getPoll() { return &this->socket; }

int Client::parseMessage(IrcMessage &msg) {
    // msg.print();
    std::string command = msg.getCommand();
    std::vector<std::string> params = msg.getParams();
    string retmsg;
    if (params.empty() || command.empty())
        return -1;
    if (command == "PASS") {
        this->_pass = params[0];
        if (params.size() > 1)
            for (size_t i = 1; i < params.size(); i++)
                this->_pass += " " + params[i];
        if (this->_pass != this->_serverPass) {
            retmsg = "ERROR :Invalid password\r\n";
            this->writeClient(retmsg);
            return 1;
        }else{
            retmsg = "Welcome " + this->_nick + "!" + this->_user + "@localhost\r\n";
            this->writeClient(retmsg);
            this->_accepted = true;
        }
    } else if (command == "NICK") {
        this->_nick = params[0];
    } else if (command == "USER")
        this->_user = params[0];
    else if (command == "OPER") {
        this->_isOperator = true;
    }
    if (command == "JOIN")
       this->_server->join(msg, this);
    else if (command == "PRIVMSG") {
        this->_server->privmsg(msg, this);
    }else if (command == "QUIT") {
        this->_accepted = false;
        this->_server->quit(msg, this);
    }else if (command == "WHO"){
        // :irc.example.net 352 dcarvalh #aaa dcarvalh F456A.75198A.60D2B2.ADA236.IP dcarvalh H :0 realname
        retmsg = ":irc.example.net 352 " + this->_nick + " " + params[0] + " " + this->_nick + " F456A.75198A.60D2B2.ADA236.IP " + this->_nick + " H :0 realname\r\n";
        this->writeClient(retmsg);
    }

    return 0; // Add a return statement to avoid control reaching end of non-void function
}

void Client::join(string joining){
    //  :dcarvalh!dcarvalh@F456A.75198A.60D2B2.ADA236.IP JOIN #aaa * :realname
    string ret = "";
    if (!this->_accepted){
        this->writeClient(ret.append("ERROR :You have not registered\r\n"));
        return;
    }
    ret.append(":" + this->_nick + "!" + this->getName() +" ");
    ret.append(joining + "\r\n");
    this->writeClient(ret);
}

Client::Client(int socket, Server *host) : _pass(), _nick(), _user(), _isOperator(false), socket()
{
    this->_server = host;
    this->_serverPass = host->getPass().append("\r");
    this->socket.fd = socket;
    this->socket.events = POLLIN;
}

int Client::readClient(std::string &buff) {
    char buf[2048];
    int wSize = 0;
    cout << "Read content\t\t\t" << this->socket.fd << endl;
    while (true) {
        buff = "";
        memset(buf, 0, sizeof(buf)); // Clear the buffer after each read
        wSize = recv(this->socket.fd, buf, 2047, MSG_DONTWAIT);
        if (wSize <= 0)
            break;
        buff.append(buf, wSize);
        istringstream iss(buff);
        string line;
        while (std::getline(iss, line)) {
            IrcMessage *msg = new IrcMessage(line);
            parseMessage(*msg); 
            delete msg;
        }
    }
    if (wSize == 0) {
        return 1; // Client closed the connection
        // Handle the disconnection if needed
    } else if (wSize == -1) {
        return -1; // Error occurred
        // Handle the error if needed
    }
    return 0; // Read operation completed successfully
}


int Client::writeClient(std::string &toSend) {
    const char *buf = toSend.c_str(); // Get a pointer to the string's data
    int totalSent = 0;
    int remaining = toSend.length(); // Total bytes remaining to send

    while (remaining > 0) {
        int sent = send(this->socket.fd, buf + totalSent, remaining, 0);
        if (sent == -1) {
            // Error occurred while sending
            return -1;
        }
        totalSent += sent;
        remaining -= sent;
    }
    return totalSent; // Return total bytes sent
}


Channel *Client::addChannel(string channel) {
    // Adicione o cliente ao canal

    Channel *ch = this->_server->addChannel(channel);
    this->_channels[channel] = this->_server->getChannel(channel);
    this->_channels[channel]->addClient(this);
    return ch;
}

void Client::removeChannel(const std::string& channelName) {
    // Verifique se o cliente está no canal
    if (_channels.find(channelName) != _channels.end()) {
        // Remova o cliente do canal
        _channels[channelName]->removeClient(this);
        // Remova o canal do cliente
        _channels.erase(channelName);
    }
}

Client::~Client() {
    std::cout << "Client Destructor #" << this->socket.fd << "\n";
    close(this->socket.fd);
}