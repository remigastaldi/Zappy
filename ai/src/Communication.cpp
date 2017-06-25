
#include "Communication.hpp"

Communication::Communication() noexcept
{}

Communication::Communication(int port, char *machine)
{
    _port = port;
    _machine = machine;
    _pe = getprotobyname("TCP");
    _fd = socket(AF_INET, SOCK_STREAM, _pe->p_proto);
    _s_in.sin_family = AF_INET;
    _s_in.sin_port = htons(_port);
    _s_in.sin_addr.s_addr = inet_addr(_machine.c_str());
    connect(_fd, (struct sockaddr *)&_s_in, sizeof(_s_in));
}

void            Communication::setPort(int pt) noexcept
{
    _port = pt;
}

int             Communication::getPort() noexcept
{
    return (_port);
}

void            Communication::setMachine(const std::string& machine) noexcept
{
    _machine = machine;
}

void            Communication::receiveCmd(const std::string& commande) noexcept
{
    _cmd = commande;
    sendCmd();
}


void            Communication::sendCmd() noexcept
{
    dprintf(_fd, "%s", _cmd.c_str());
}

const std::string&     Communication::waitCmd()
{

    // if (answer == "ko")
    // if (answer == "dead")
    return (_answer);
}
