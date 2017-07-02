/*
** arg_checking.cpp for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/ai/src
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Sun Jul 02 14:11:38 2017 Leo Hubert Froideval
** Last update Sun Jul 02 14:11:40 2017 Leo Hubert Froideval
*/

#include "Ai.hpp"

int           checkPort(char **av)
{
  int   i = 0;

  while (i <= 5)
  {
    std::string tmp(av[i++]);
    if (tmp == "-p")
    {
      tmp = av[i++];
      return (atoi(tmp.c_str()));
    }
  }
  return (0);
}

std::string   checkName(char **av)
{
  int   i = 0;

  while (i <= 5)
  {
    std::string   tmp(av[i++]);
    if (tmp == "-n")
    {
      tmp = av[i++];
      return (tmp);
    }
  }
  return (NULL);
}


std::string   checkHost(char **av)
{
  int           i = 0;

  while (i <= 5)
  {
    std::string   tmp(av[i++]);
    if (tmp == "-h")
    {
      tmp = av[i++];
      if (tmp == "localhost")
        tmp = "127.0.0.1";
      return (tmp);
    }
  }
  return (NULL);
}

int   is_alpha(char *str)
{
  int   i = 0;

  while (str[i])
  {
    if (str[i] >= '0' && str[i] <= '9')
      i++;
    else
    {
      std::cout << "The argument after -p must be a int" << std::endl;
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
    std::cout << "USAGE:t ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tmachine ist the name of the machine; localhost by default" << std::endl;
    std::cout << "\tname ist the name of the team" << std::endl;
    std::cout << "\tport ist the port number" << std::endl;
    return (0);
  }
}
