//
// Communication.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 16:36:20 2017 gastal_r
// Last update Tue Jun 27 12:28:51 2017 gastal_r
//

#ifndef COMMUNICATION_HPP
# define COMMUNICATION_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <iomanip>

class   Communication
{
private:
  std::string         _cmd;
  int                 _port;
  struct protoent     *_pe;
  int                 _fd;
  struct sockaddr_in  _s_in;

  std::unique_ptr<std::istream> _inStream;
  std::unique_ptr<std::ostream> _outStream;

protected:
  std::string         _machine;
  std::string         _answer;

public:
  Communication(int port, const std::string &machine, const std::string &teamName);
  void                checkIfEventMessage();
  void                sendCommand(const std::string &command) noexcept;
};

#endif //COMMUNICATION_HPP
