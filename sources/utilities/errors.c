/*
** errors.c for Zappy in /home/prost_m/Rendu/Semestre_4/Zappy/sources/utilities/
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 19:52:02 2017 Matthias Prost
** Last update	Thu Jun 15 19:52:21 2017 Full Name
*/

#include "utilities.h"

int	s_error(char *str)
{
  perror(str);
  exit(EXIT_FAILURE);
}
