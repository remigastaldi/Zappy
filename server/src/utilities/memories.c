/*
** memories.c for Zappy in /Users/leohubertfroideval/Shared/PSU_2016/Zappy/server/src/utilities
**
** Made by Leo Hubert Froideval
** Login   <leohubertfroideval@epitech.eu>
**
** Started on  Thu Jun 22 16:19:50 2017 Leo Hubert Froideval
** Last update Sun Jul  2 17:47:14 2017 Matthias Prost
*/

#include "utilities.h"

void	*xmalloc(size_t size)
{
  void	*ptr;

  if ((ptr = malloc(size)) == NULL)
    exit(0);
  return (ptr);
}
