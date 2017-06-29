/*
** my_strcat.c for  in /home/puccio_c/rendu/PSU/Zappy
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Sun Jun 25 22:35:17 2017 Cyril Puccio
** Last update Wed Jun 28 22:06:38 2017 gastal_r
*/

#include "server.h"

char			*my_strcat(char *dest, char *src, int i, int j)
{
  char			*tmp;
  int			len_src;
  int			len_dest;

  len_src = strlen(src);
  if (dest == NULL)
    {
      if ((dest = malloc((len_src + 1))) == NULL)
	return (NULL);
      while (src[++i])
	dest[i] = src[i];
      dest[i] = '\0';
      return (dest);
    }
  len_dest = strlen(dest);
  if ((tmp = malloc((len_src + len_dest + 1))) == NULL)
    return (NULL);
  while (dest[++j])
    tmp[j] = dest[j];
  while (src[++i])
    tmp[j++] = src[i];
  tmp[j] = '\0';
  free(dest);
  return (tmp);
}
