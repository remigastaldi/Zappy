/*
** epur.c for epur
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Sat Jun  3 21:43:58 2017 Matthias Prost
** Last update Thu Jun 22 16:25:55 2017 Leo Hubert Froideval
*/

#include "utilities.h"

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
      buff = xmalloc(strlen(str) + 1);
      while (str[++i])
	{
	  if (str[i] != 10 && str[i] != '\r')
	    buff[++a] = str[i];
	}
      buff[++a] = '\0';
      bzero(str, strlen(str));
      memcpy(str, buff, strlen(buff));
      free (buff);
    }
  return (str);
}
