
#include "Communication.hpp"

Communication::Communication() noexcept
{
    connected = 0;
    port = 0;
    pe = getprotobyname("TCP");
    fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    s_in.sin_family = AF_INET;
}

void            Communication::getConnected() noexcept
{
    s_in.sin_port = htons(port);
    s_in.sin_addr.s_addr = inet_addr(machine.c_str());
    connect(fd, (struct sockaddr *)&s_in, sizeof(s_in));
    connected = 1;
}

void            Communication::setPort(int pt) noexcept
{
    this->port = pt;
}

int             Communication::getPort() noexcept
{
    return (port);
}

void            Communication::setMachine(const std::string& machine) noexcept
{
    this->machine = machine;
}

void            Communication::receiveCmd(const std::string& commande) noexcept
{
    cmd = commande;
    sendCmd();
}


void            Communication::sendCmd() noexcept
{
    if (connected == 0)
        getConnected();
    dprintf(1, "%s\n", cmd.c_str());
}

const std::string&     Communication::waitCmd()
{

    // if (answer == "ko")
    // if (answer == "dead")
    return (answer);
}
