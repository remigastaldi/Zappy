
#include "Communication.hpp"

Communication::Communication() noexcept
{}

Communication::Communication(int port, char *machine, char *team)
{
    std::string s(team);
    this->port = port;
    this->machine = machine;
    pe = getprotobyname("TCP");
    fd = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    s_in.sin_family = AF_INET;
    s_in.sin_port = htons(this->port);
    s_in.sin_addr.s_addr = inet_addr(this->machine.c_str());
    teamName = s;
    connect(fd, (struct sockaddr *)&s_in, sizeof(s_in));
    // buf = get_next_line(fd);
    read(fd, buf, 10000);
    printf("Server said: %s", buf);
    dprintf(fd, "%s", teamName.c_str());
    // buf = get_next_line(fd);
    read(fd, buf, 10000);
    printf("Server said: %s", buf);
    // buf = get_next_line(fd);
    read(fd, buf, 10000);
    printf("Server said: %s", buf);
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
    dprintf(fd, "%s", cmd.c_str());
    waitCmd();
}

const std::string&     Communication::waitCmd()
{
    char    buf[10000];
    // if (answer == "ko")
    // if (answer == "dead")
    read(fd, buf, 10000);
    printf("%s\n", buf);
    return (answer);
}
