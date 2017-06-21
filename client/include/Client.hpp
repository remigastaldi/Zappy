//
// Client.hpp for zappy in /home/gastal_r/rendu/Zappy
//
// Made by
// Login   <gastal_r>
//
// Started on  Wed Jun 21 16:04:04 2017
// Last update Wed Jun 21 16:10:11 2017
//

#ifndef		_CLIENT_HPP_
#define		_CLIENT_HPP_

class     Client
{
public:
  Client();

  ~Client() = default;
  Client(const Client& other) = default;
  Client(Client&& other) = default;
  Client& operator=(const Client& other) = default;
  Client& operator=(Client&& other) = default;
};

#endif	/* !_CLIENT_HPP_ */
