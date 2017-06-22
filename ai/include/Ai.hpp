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

#include  "Exception.hpp"
#include  "Communication.hpp"
//#include  "Utils.hpp"

class     Ai : public Communication
{
  enum class Properties
  {
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
    WAITING,

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
  bool    needResources(void) noexcept;
  bool    broadcast(void) noexcept;

private:
  std::unordered_map<size_t, std::unordered_map<Ai::Properties, size_t>> _riseUpConditions;
  std::unordered_map<Ai::Properties, size_t> _currentItems;
  size_t _currentLevel;
};

#endif	/* !_AI_HPP_ */
