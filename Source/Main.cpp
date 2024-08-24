#include <IrcMainHeader.hpp>
#include <Server.hpp>

Server *irc = NULL;


void closeSignal(int sig)
{
    if(!irc)
        std::cout << "There is no server to shutdown\n";
    else if (sig == SIGINT)
        irc->stop();
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    signal(SIGINT, closeSignal);
    irc = new Server("8080", "a");
    irc->serverLoop();
    std::cout << "Stop\n";
    delete irc;
}