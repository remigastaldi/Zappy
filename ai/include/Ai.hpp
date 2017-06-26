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

public:
  Ai(int port, char* machine, char* team) noexcept;
  ~Ai() = default;
  Ai(const Ai& other) = default;
  Ai(Ai&& other) = default;
  Ai& operator=(const Ai& other) = default;
  Ai& operator=(Ai&& other) = default;
  void  start(void) noexcept;

protected:
  const std::string &checkIfEventMessage(std::string &message);
  void    primaryState(void) noexcept;
  bool    checkCriticalFood(void) noexcept;
  void    powerupState(void) noexcept;
  size_t  countPlayer(void) noexcept;
  void    actualiseInventory(void) noexcept;
  bool    checkIfNeedResources(void) noexcept;
  void    actualiseView(void) noexcept;
  bool    lookForFood(void) noexcept;
  int     findFoodCase(void) noexcept;
  bool    lookForResources(void) noexcept;
  int     findNeededResourceCase(void) noexcept;
  void    calculatePath(int resourceCase) noexcept;
  int     calculateDirection(int destination, int a, int b, int c) noexcept;
  void    walkToBroadcaster(int caseId) noexcept;
  void    walkToDir(void) noexcept;

private:
  std::unordered_map<size_t, std::unordered_map<Ai::Properties, size_t>> _riseUpConditions;

  std::unordered_map<Ai::Properties, size_t> _currentItems;
  size_t _currentLevel;

  std::vector<std::vector<Ai::Properties>> _view;
  std::vector<Ai::Direction> _path;
  Ai::Properties  _objectToTake;
};

#endif	/* !_AI_HPP_ */
