/*
** epur.c for epur
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Sat Jun  3 21:43:58 2017 Matthias Prost
** Last update	Sat Jun 03 22:59:41 2017 Sonny Fournier
*/

#include "utils.h"

char		*epurStr(char *str)
{
  size_t	i;
  int		a;
  char		*buff;

  i = -1;
  a = -1;
  buff = NULL;
  if (str != NULL)
    {
      if ((buff = malloc(4096)) == NULL)
	{
	  printf("ERROR: cannot malloc\n");
	  exit(EXIT_FAILURE);
	}
      while (str[++i])
	{
	  if (str[i] != 10 && str[i] != '\r')
	    buff[++a] = str[i];
	}
      buff[++a] = '\0';
    }
  return (buff);
}
