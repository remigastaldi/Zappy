//
// Exception.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 11:48:19 2017 gastal_r
// Last update Thu Jun 22 11:48:35 2017 gastal_r
//

#ifndef     _EXCEPTION_HPP_
#define     _EXCEPTION_HPP_

#include    <exception>
#include    <string>

class Exception : public std::exception
{
public:
  explicit Exception(const std::string &message) : _message(message) {;}
  Exception(const std::string &message, const std::string &var) : _message(message)
  {
    _message += var;
  }
  virtual ~Exception() throw() {};
  virtual const char* what() const throw() { return(_message.c_str());}

private:
  std::string   _message;
};

#endif /* !_EXCEPTION_HPP_ */
