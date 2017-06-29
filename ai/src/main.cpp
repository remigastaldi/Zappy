//
// main.cpp for Zappy in /home/gastal_r/rendu/Zappy/client/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Wed Jun 21 16:14:06 2017 gastal_r
// Last update Tue Jun 27 12:52:13 2017 gastal_r
//

#include      "Ai.hpp"

int   is_alpha(char *str)
{
  int   i = 0;

  while (str[i])
  {
    if (str[i] >= '0' && str[i] <= '9')
      i++;
    else
    {
      std::cout << "The argumen after -p must be a int" << std::endl;
      return (1);
    }
  }
  return (0);
}

int          check_arg(char **av)
{
  std::string   tmp(av[1]);
  bool          tiretp = 0;
  bool          tiretn = 0;
  bool          tireth = 0;

  if (tmp == "-p")
  {
    tiretp = 1;
    if (is_alpha(av[2]) == 1)
      return (1);
  }
  else if (tmp == "-h")
    tireth = 1;
  else if (tmp == "-n")
    tiretn = 1;

  tmp = av[3];
  if (tmp == "-p")
  {
    tiretp = 1;
    if (is_alpha(av[4]) == 1)
      return (1);
  }
  else if (tmp == "-h")
    tireth = 1;
  else if (tmp == "-n")
    tiretn = 1;

  tmp = av[5];
  if (tmp == "-p")
  {
    tiretp = 1;
    if (is_alpha(av[6]) == 1)
      return (1);
  }
  else if (tmp == "-h")
    tireth = 1;
  else if (tmp == "-n")
    tiretn = 1;

  if (tiretn == 1 && tiretp == 1 && tireth == 1)
  {
    return (0);
  }
  else
  {
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
    std::cout << "\tname is the name of the team" << std::endl;
    std::cout << "\tport is the port number" << std::endl;
    return (0);
  }
}

int           main(int ac, char *av[])
{
  if (ac != 7)
  {
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
    std::cout << "\tname is the name of the team" << std::endl;
    std::cout << "\tport is the port number" << std::endl;
    return (0);
  }
  if (check_arg(av) == 1)
    return (0);
  Ai   ai(atoi(av[2]), av[4], av[6]);
  ai.start(Ai::State::START);
  return (0);
}
