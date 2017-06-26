//
// Event.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 11:48:19 2017 gastal_r
// Last update Mon Jun 26 12:10:25 2017 gastal_r
//

#ifndef     _EVENT_HPP_
#define     _EVENT_HPP_

#include    <exception>
#include    <string>

class Event : public std::exception
{
public:
  virtual ~Event() throw() {};

public:
  class Dead
  {
  public:
    explicit Dead() {};
    virtual ~Dead() throw() {};
  };

  class Ko
  {
  public:
    explicit Ko() {};
    virtual ~Ko() throw() {};
  };

  class GameOver
  {
  public:
    explicit GameOver(const std::string &teamName) : _teamName(teamName) {};
    virtual ~GameOver() throw() {};

    const std::string &getTeamName(void) const { return (_teamName); }

  private:
    const std::string _teamName;
  };

  class Broadcast
  {
  public:
    explicit Broadcast(int caseNb) : _caseNb(caseNb) {};
    virtual ~Broadcast() throw() {};
    virtual int getCase(void) const { return (_caseNb); }

  private:
    int   _caseNb;
  };

  class DeadBroadcaster
  {
  public:
    explicit DeadBroadcaster() {};
    virtual ~DeadBroadcaster() throw() {};
  };
};

#endif /* !_EVENT_HPP_ */
