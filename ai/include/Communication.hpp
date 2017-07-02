//
// Communication.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 16:36:20 2017 gastal_r
// Last update Sun Jul  2 16:56:57 2017 gastal_r
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
#include <thread>

#include "FdStream.hpp"
#include "Event.hpp"

class   Communication
{
private:
  struct protoent     *_pe;
  struct sockaddr_in  _s_in;
  std::unique_ptr<FdStream> _fdStream;

protected:
  int                 _fd;
  int                 _port;
  std::string         _teamName;
  std::string         _machine;
  std::string         _answer;

  std::thread         _thread;
  std::string         _buff;

public:
  Communication(int port, const std::string &teamName, const std::string &machine);

  bool                checkIfEventMessage(std::string &msg);
  void                sendCommand(const std::string &command);
  void                receiveCommand(void);
};

#endif //COMMUNICATION_HPP
