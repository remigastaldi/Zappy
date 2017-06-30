//
// Utils.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 17:50:43 2017 gastal_r
// Last update Fri Jun 30 17:54:54 2017 gastal_r
//

#ifndef       _UTILS_HPP_
#define       _UTILS_HPP_

#include      "Ai.hpp"

class Utils
{
public:
  static inline Ai::Properties stringToEnum(const std::string &value)
  {
    if (value == "player")
      return (Ai::Properties::NB_PLAYER);
    if (value == "food")
      return (Ai::Properties::FOOD);
    else if (value == "linemate")
      return (Ai::Properties::LINEMATE);
    else if (value == "deraumer")
      return (Ai::Properties::DERAUMERE);
    else if (value == "sibur")
      return (Ai::Properties::SIBUR);
    else if (value == "mendiane")
      return (Ai::Properties::MENDIANE);
    else if (value == "phiras")
      return (Ai::Properties::PHIRAS);
    else if (value == "thystame")
      return (Ai::Properties::THYSTAME);
    return (Ai::Properties::NOTHING);
  }

  static inline const std::string enumToString(Ai::Properties value)
  {
    switch (value)
    {
    case Ai::Properties::NB_PLAYER:
      return ("player");
    case Ai::Properties::FOOD:
      return ("food");
    case Ai::Properties::LINEMATE:
      return ("linemate");
    case Ai::Properties::DERAUMERE:
      return ("deraumer");
    case Ai::Properties::SIBUR:
      return ("sibur");
    case Ai::Properties::MENDIANE:
      return ("mendiane");
    case Ai::Properties::PHIRAS:
      return ("phiras");
    case Ai::Properties::THYSTAME:
      return ("thystame");
    case Ai::Properties::NOTHING:
      return ("nothing");
    }
  return ("unknow");
  }

  static inline const std::string enumToString(Ai::Direction value)
  {
    switch (value)
    {
    case Ai::Direction::FORWARD:
      return ("Forward");
    case Ai::Direction::RIGHT:
      return ("Right");
    case Ai::Direction::LEFT:
      return ("Left");
    case Ai::Direction::UP:
      return ("Up");
    }
    return ("unknow");
  }

  static inline const std::string threadNumber()
  {
    return (std::string(""));
    // std::basic_ostream<typename _CharT, optional typename _Traits>
    // std::ostream *os = new std::ostream(std::cout.rdbuf());
    // *os << "[" << std::this_thread::get_id() << "] ";
    // return *os;
  }
};

#endif /* end of include guard: _UTILS_HPP_ */
