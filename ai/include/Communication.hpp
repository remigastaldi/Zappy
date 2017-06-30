//
// Communication.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 16:36:20 2017 gastal_r
// Last update Fri Jun 30 17:07:28 2017 gastal_r
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
#include  <thread>

#include "FdStream.hpp"
#include "Event.hpp"

class   Communication
{
private:
  struct protoent     *_pe;
  int                 _fd;
  struct sockaddr_in  _s_in;
  std::unique_ptr<FdStream> _fdStream;

protected:
  int                 _port;
  std::string         _teamName;
  std::string         _machine;
  std::string         _answer;

public:
  Communication(int port, const std::string &teamName, const std::string &machine) noexcept;

  void                checkIfEventMessage();
  void                sendCommand(const std::string &command);
  void                receiveCommand(void);
};

#endif //COMMUNICATION_HPP
