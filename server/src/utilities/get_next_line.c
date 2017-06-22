/*
** get_next_line.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Thu Jun 15 15:12:22 2017 Matthias Prost
** Last update Thu Jun 22 16:26:09 2017 Leo Hubert Froideval
*/

#include "utilities.h"

char    *initialisation(char *ret, int *tab, int *nb, char *buff)
{
  *nb = *nb - 1;
  ret[tab[2]] = buff[tab[0]];
  tab[0] = tab[0] + 1;
  tab[2] = tab[2] + 1;
  return (ret);
}

char    *myRealloc(char *ret, int *tab, int *nb, char *buff)
{
  char  *save;
  int   i;

  i = -1;
  buff[*nb] = 0;
  ret[tab[2]] = '\0';
  tab[1] = tab[1] + 1;
  if ((save = xmalloc(sizeof(char) * READ_SIZE * tab[1] + 1)) == NULL)
    return (NULL);
  while (ret[++i])
    save[i] = ret[i];
  tab[0] = 0;
  free(ret);
  return (save);
}

char    *end(char *ret, int *tab, int *nb)
{
  tab[0] = tab[0] + 1;
  *nb = *nb - 1;
  ret[tab[2]] = '\0';
  return (ret);
}

char    *verif(char *ret, int *tab, int *nb, char *buff)
{
  if (tab[1] == 0)
    {
      if ((*nb = read(tab[3], buff, READ_SIZE)) <= 0)
	return (NULL);
      buff[*nb] = 0;
      tab[1] = 1;
    }
  if ((ret = xmalloc(sizeof(char) * READ_SIZE + 1)) == NULL)
    return (NULL);
  if (*nb <= 0 && tab[2] == 0)
    {
      if ((*nb = read(tab[3], buff, READ_SIZE)) <= 0)
	{
	  free(ret);
	  return (NULL);
	}
	buff[*nb] = 0;
      tab[0] = 0;
      if (buff[tab[0]] == '\0')
	return (get_next_line(tab[3]));
    }
  return (ret);
}

char    *get_next_line(const int fd)
{
  char          *ret;
  static int    tab[4];
  static int    nb = 0;
  static char   buff[READ_SIZE + 1];

  tab[2] = 0;
  tab[3] = fd;
  ret = NULL;
  if ((ret = verif(ret, &tab[0], &nb, &buff[0])) == NULL)
    return (NULL);
  while (buff[tab[0]] != '\n' && buff[tab[0]] != '\0')
    {
      ret = initialisation(&ret[0], &tab[0], &nb, &buff[0]);
      if (nb == 0)
	{
	  if ((nb = read(tab[3], buff, READ_SIZE)) <= 0)
	    {
	      ret[tab[2]] = '\0';
	      return (ret);
	    }
	  if ((ret = myRealloc(ret, &tab[0], &nb, &buff[0])) == NULL)
	    return (NULL);
	}
    }
  return (end(ret, &tab[0], &nb));
}
