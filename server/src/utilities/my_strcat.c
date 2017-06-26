/*
** my_strcat.c for  in /home/puccio_c/rendu/PSU/Zappy
** 
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
** 
** Started on  Sun Jun 25 22:35:17 2017 Cyril Puccio
** Last update Sun Jun 25 22:36:37 2017 Cyril Puccio
*/

#include "server.h"

char    *my_strcat(char *dest, char *src)
{
  char  *result;
  int   len;
  int   i;

  i = 0;
  len = 0;
  result = malloc(strlen(dest) + strlen(src) + 1);
  while (dest[i])
    {
      result[i] = dest[i];
      i++;
    }
  while (src[len])
    {
      result[len + i] = src[len];
      len++;
    }
  result[len + i] = '\0';
  return (result);
}
