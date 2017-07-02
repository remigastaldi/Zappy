//
// Communication.cpp for Zappy in /home/gastal_r/rendu/Zappy/ai/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Sun Jun 25 11:49:42 2017 gastal_r
// Last update Sun Jul  2 16:51:54 2017 gastal_r
//

#include "Communication.hpp"

Communication::Communication(int port, const std::string &teamName, const std::string &machine) noexcept
  : _port(port),
  _teamName(teamName),
  _machine(machine)
{
    _pe = getprotobyname("TCP");
    _fd = socket(AF_INET, SOCK_STREAM, _pe->p_proto);
    _s_in.sin_family = AF_INET;
    _s_in.sin_port = htons(_port);
    _s_in.sin_addr.s_addr = inet_addr(_machine.c_str());
    if (connect(_fd, (struct sockaddr *)&_s_in, sizeof(_s_in)) == -1)
      exit(0);

    _fdStream.reset(new FdStream(_fd));

    *_fdStream >> _answer;
    std::cout << "[" << _fd << "] " << "Received <== " << _answer << std::endl;
    *_fdStream << teamName;
    std::cout << "[" << _fd << "] " << "Send ==> " << teamName << std::endl;
    *_fdStream >> _answer;
    std::cout << "[" << _fd << "] " << "Received <== " << _answer << std::endl;
    if (_answer.find("ko") != std::string::npos)
      throw Event::Exit("Bad team name");
    if (std::stoi(_answer) == 0)
      throw Event::Exit("No more place in this team");
    *_fdStream >> _answer;
    std::cout << "[" << _fd << "] " << "Received <== " << _answer << std::endl;
}

bool         Communication::checkIfEventMessage(std::string &msg)
{
  if (msg.empty())
  {
    throw Event::Exit("Serveur down");
  }
  if (msg.find("egg") != std::string::npos)
  {
    throw Event::Egg();
  }
  else if (msg.find("ko") != std::string::npos)
  {
    throw Event::Ko();
  }
  else if (msg.find("game over") != std::string::npos)
  {
    msg.erase(0, msg.find("game over") + 9);
    throw Event::GameOver(msg);
  }
  else if (msg.find("message") != std::string::npos)
  {
    // if ((size_t)msg.at(msg.find_first_of("12345678")) == _currentLevel)
    if (msg.find("dead") != std::string::npos)
      throw Event::DeadBroadcaster();
    else
    {
      msg.erase(0, msg.find_last_of(" ") + 1);
      throw Event::Broadcast(std::stoi(msg));
    }
  }
  else if (msg.find("dead") != std::string::npos)
  {
    throw Event::Dead();
  }
  return (true);
}

void            Communication::sendCommand(const std::string &command)
{
  _answer.clear();
  // std::cout << "Lock" << std::endl;
  // _lock.exchange(true);
  std::cout << "[" << _fd << "] " << "Send ==> " << command << std::endl;
  *_fdStream << command;
  receiveCommand();
}

void          Communication::receiveCommand(void)
{
  *_fdStream >> _answer;
  std::cout << "[" << _fd << "] " << "Received <== " << _answer << std::endl;
  checkIfEventMessage(_answer);
}
