//
// main.cpp for Zappy in /home/gastal_r/rendu/Zappy/client/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Wed Jun 21 16:14:06 2017 gastal_r
// Last update Wed Jun 21 20:50:39 2017 gastal_r
//

#include      "Ai.hpp"

int           main(int ac, char *av[])
{
  (void) ac;
  (void) av;
  Communication   communication;

  communication.setPort(atoi(av[2]));
  communication.setMachine(av[6]);
  // neverForgetTo(lock->Compter);
  return (0);
}
