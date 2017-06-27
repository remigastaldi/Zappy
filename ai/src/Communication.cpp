//
// Communication.cpp for Zappy in /home/gastal_r/rendu/Zappy/ai/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Sun Jun 25 11:49:42 2017 gastal_r
// Last update Tue Jun 27 12:28:13 2017 gastal_r
//

#include "Communication.hpp"
#include "Utils.hpp"

Communication::Communication(int port, const std::string &machine, const std::string &teamName)
  : _port(port),
  _machine(machine)
{
    _pe = getprotobyname("TCP");
    _fd = socket(AF_INET, SOCK_STREAM, _pe->p_proto);
    _s_in.sin_family = AF_INET;
    _s_in.sin_port = htons(_port);
    _s_in.sin_addr.s_addr = inet_addr(_machine.c_str());
    connect(_fd, (struct sockaddr *)&_s_in, sizeof(_s_in));

    _inStream.reset(Utils::createInStreamFromFD(_fd));
    _outStream.reset(Utils::createOutStreamFromFD(_fd));

    std::getline(*_inStream, _answer, '\n');
    std::cout << _answer << std::endl;
    *_outStream << teamName << std::endl;
    std::getline(*_inStream, _answer, '\n');
    std::cout << _answer << std::endl;
    std::getline(*_inStream, _answer, '\n');
    std::cout << _answer << std::endl;
}

void         Communication::checkIfEventMessage()
{
  std::string answerCp(_answer);

  if (answerCp.find("dead") != std::string::npos)
    throw Event::Dead();
  else if (answerCp.find("ko") != std::string::npos)
    throw Event::Ko();
  else if (answerCp.find("game over") != std::string::npos)
  {
    answerCp.erase(0, answerCp.find("game over") + 9);
    throw Event::GameOver(answerCp);
  }
  else if (answerCp.find("answerCp") != std::string::npos)
  {
    // if ((size_t)answerCp.at(answerCp.find_first_of("12345678")) == _currentLevel)
    if (answerCp.find("dead") != std::string::npos)
      throw Event::DeadBroadcaster();
    else
      throw Event::Broadcast((size_t)answerCp.at(answerCp.find_last_of("12345678")));
  }
}

void            Communication::sendCommand(const std::string &command) noexcept
{
  _answer.clear();
  *_outStream << command << std::endl;
  std::getline(*_inStream, _answer, '\n');
  checkIfEventMessage();
}
