//
// Ai.hpp for zappy in /home/gastal_r/rendu/Zappy
//
// Made by
// Login   <gastal_r>
//
// Started on  Wed Jun 21 16:04:04 2017
// Last update Wed Jun 21 16:10:11 2017
//

#ifndef		_AI_HPP_
#define		_AI_HPP_

#include  <unordered_map>
#include  <vector>
#include  <string>

#include  "Event.hpp"
#include  "Communication.hpp"

class     Ai : public Communication
{
public:
  enum class Properties
  {
    NOTHING,
    NB_PLAYER,
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  };

  enum class Direction
  {
    FORWARD,
    UP,
    LEFT,
    RIGHT
  };

  enum class State
  {
    START,
    INCANTATION,
    WALK_TO_BROADCASTER,
  };

public:
  Ai(int port, const std::string &teamName, const std::string &machine) noexcept;

  void  start(Ai::State) noexcept;

protected:
  void    primaryState(void) ;
  bool    checkCriticalFood(void) ;
  void    powerupState(void) ;
  size_t  countPlayer(void) const noexcept;
  void    actualiseInventory(void) ;
  bool    checkIfNeedResources(void) noexcept;
  void    actualiseView(void) ;
  bool    lookForFood(void) ;
  int     findFoodCase(void) noexcept;
  bool    lookForResources(void) ;
  int     findNeededResourceCase(void) noexcept;
  void    calculatePath(int resourceCase) noexcept;
  int     calculateDirection(int destination, int a, int b, int c) noexcept;
  void    walkToBroadcaster(int caseId) ;
  void    walkToDir(void) ;
  void    startIncantation(void) ;

private:
  std::unordered_map<size_t, std::unordered_map<Ai::Properties, size_t>> _riseUpConditions;

  std::unordered_map<Ai::Properties, size_t> _currentItems;
  size_t _currentLevel;

  std::vector<std::vector<Ai::Properties>> _view;
  std::vector<Ai::Direction> _path;
  Ai::Properties  _objectToTake;
  int   _eventCase;
};

int           checkPort(char **av);
std::string   checkName(char **av);
std::string   checkHost(char **av);
int           is_alpha(char *str);
int           check_arg(char **av);

#endif	/* !_AI_HPP_ */
