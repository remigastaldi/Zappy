/*
** to_wordtab.c for Zappy
**
** Made by Matthias Prost
** Login   <matthias.prost@epitech.eu@epitech.eu>
**
** Started on  Sat Jun 24 14:45:00 2017 Matthias Prost
** Last update Sat Jun 24 14:45:04 2017 Matthias Prost
*/

#include "utilities.h"

void 		freeTab(char **tab)
{
	int 	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

int			myCount(char *str, char c)
{
  int		i;
  int		count;

  i = count = 0;
  while (str[i] != '\0')
    {
      while (str[i] && (str[i] == c || str[i] == '\t'))
				i++;
      if (str[i])
				count++;
      if (str[i] != '\0')
				i++;
    }
  return (count);
}

int			lenTab(const char *str, char c)
{
  int		i;

  i = -1;
  while (str[++i] != '\0' && str[i] != c && str[i] != '\t');
  return (i);
}

char		**toWordtab(char *str, char c)
{
	int		i;
	int		j;
	int		z;
  char	**tab;

  i = 0;
  z = -1;
  if ((tab = malloc((myCount(str, c) + 1) * sizeof(*tab))) == NULL)
    exit(-1);
  while (str[i])
    {
      j = 0;
      while (str[i] && (str[i] == c || str[i] == ' ' || str[i] == '\t'))
				++i;
      if ((tab[++z] = malloc((lenTab(&str[i], c) + 1) * sizeof(**tab))) == NULL)
				exit(-1);
      while (str[i] && str[i] != c && str[i] != ' ' && str[i] != '\t')
				tab[z][j++] = str[i++];
      tab[z][j] = '\0';
      while (str[i] && (str[i] == c || str[i] == ' ' || str[i] == '\t'))
				++i;
    }
  tab[z + 1] = '\0';
  return (tab);
}
