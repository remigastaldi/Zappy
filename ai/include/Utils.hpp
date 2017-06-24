//
// Utils.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu Jun 22 17:50:43 2017 gastal_r
// Last update Fri Jun 23 15:08:21 2017 gastal_r
//

#ifndef       _UTILS_HPP_
#define       _UTILS_HPP_

#include      "Ai.hpp"

class AiUtils
{
public:
  static inline Ai::Properties stringToEnum(const std::string &value) noexcept
  {
    if (value == "player")
      return (Ai::Properties::NB_PLAYER);
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

  static inline const std::string enumToString(Ai::Properties value) noexcept
  {
    if (value == Ai::Properties::NB_PLAYER)
      return ("player");
    else if (value == Ai::Properties::LINEMATE)
      return ("linemate");
    else if (value == Ai::Properties::DERAUMERE)
      return ("deraumer");
    else if (value == Ai::Properties::SIBUR)
      return ("sibur");
    else if (value == Ai::Properties::MENDIANE)
      return ("mendiane");
    else if (value == Ai::Properties::PHIRAS)
      return ("phiras");
    else if (value == Ai::Properties::THYSTAME)
      return ("thystame");
    return ("nothing");
  }
};

#endif /* end of include guard: _UTILS_HPP_ */
