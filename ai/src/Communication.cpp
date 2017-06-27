//
// Communication.cpp for Zappy in /home/gastal_r/rendu/Zappy/ai/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Sun Jun 25 11:49:42 2017 gastal_r
// Last update Tue Jun 27 11:14:06 2017 gastal_r
//

#include "Communication.hpp"

Communication::Communication() noexcept
{}

Communication::Communication(int port, const std::string &machine)
  : _port(port),
  _machine(machine)
{
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
    // sendCmd();
}

void            Communication::sendCommand(const std::string &command) noexcept
{
    dprintf(_fd, "%s\n", command.c_str());
    waitResponseFromServer();
}

void            Communication::waitResponseFromServer(void) noexcept
{

}

const std::string&     Communication::waitCmd()
{

    // if (answer == "ko")
    // if (answer == "dead")
    return (_answer);
}
