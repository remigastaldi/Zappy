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
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
  };

  enum class State
  {
    WAITING

  };

  enum class Direction
  {
    FORWARD,
    UP,
    LEFT,
    RIGHT
  };

public:
  Ai(int port, char* machine) noexcept;

  ~Ai() = default;
  Ai(const Ai& other) = default;
  Ai(Ai&& other) = default;
  Ai& operator=(const Ai& other) = default;
  Ai& operator=(Ai&& other) = default;

  void  start(void) noexcept;

protected:
  const std::string checkIfEventMessage(const std::string &message);
  void    primaryState(void) noexcept;
  void    powerupStateFirstCheck(void) noexcept;
  void    powerupState(void) noexcept;
  size_t  countPlayer(void) noexcept;
  void    startIncantation(void) noexcept;
  bool    checkIfNeedResources(void) noexcept;
  const std::vector<std::vector<Ai::Properties>> getLookView(void) noexcept;
  bool    lookForResources(void) noexcept;
  int     findNeededResourceCase(const std::vector<std::vector<Ai::Properties>>  &view) noexcept;
  void    calculatePath(int resourceCase) noexcept;
  int     calculateDirection(int destination, int a, int b, int c) noexcept;
  void    walkToResource(void) noexcept;

private:
  std::unordered_map<size_t, std::unordered_map<Ai::Properties, size_t>> _riseUpConditions;

  std::unordered_map<Ai::Properties, size_t> _currentItems;
  size_t _currentLevel;

  std::vector<Ai::Direction> _path;
  Ai::Properties  _objectToTake;
};

#endif	/* !_AI_HPP_ */
