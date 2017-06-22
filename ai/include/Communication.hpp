//
// Communication.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 16:36:20 2017 gastal_r
// Last update Thu Jun 22 16:37:57 2017 gastal_r
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
  std::string         cmd;
  std::string         answer;
  int                 port;
  std::string         machine;
  bool                connected;
  struct protoent     *pe;
  int                 fd;
  struct sockaddr_in  s_in;
public:
  Communication() noexcept;
  ~Communication() = default;
  Communication(const Communication& other) = default;
  Communication(Communication&& other) = default;
  Communication& operator=(const Communication& other) = default;
  Communication& operator=(Communication&& other) = default;
  void                  setPort(int port) noexcept;
  int                   getPort() noexcept;
  void                  setMachine(const std::string& machine) noexcept;
  const std::string&    getMachine() noexcept;
  void                  receiveCmd(const std::string&) noexcept;
  const std::string&    waitCmd();
  void                  sendCmd() noexcept;
  void                  getConnected() noexcept;
};

#endif //COMMUNICATION_HPP
