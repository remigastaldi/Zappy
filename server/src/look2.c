/*
** look2.c for  in /home/puccio_c/rendu/PSU/Zappy
**
** Made by Cyril Puccio
** Login   <cyril.puccio@epitech.eu>
**
** Started on  Sat Jul  1 16:29:46 2017 Cyril Puccio
** Last update Sun Jul  2 22:06:55 2017 Matthias Prost
*/

#include "server.h"

int		get_number_of_visible_space(int level)
{
  int		nb;

  nb = 1;
  while (level >= 1)
    {
      nb += ((level * 2) + 1);
      level--;
    }
  return (nb);
}

int		get_player(t_env *env, t_users *user, int x, int y)
{
  int		i;
  int		nb;

  i = -1;
  nb = 0;
  while (++i < 255)
    {
      if (env->users[i].teamName != NULL
	  && env->users[i].socket != user->socket
	  && env->users[i].posX == x && env->users[i].posY == y)
	{
	  nb++;
	}
    }
  return (nb);
}

char		*ressource_to_string(t_env *env, t_users *user, int x, int y)
{
  char		*str;
  int		nb_item;
  int		player;
  t_items	tmp;

  str = NULL;
  player = get_player(env, user, x, y);
  tmp = env->map[y][x];
  nb_item = tmp.linemate + tmp.deraumere + tmp.sibur + tmp.food;
  nb_item += tmp.mendiane + tmp.phiras + tmp.thystame;
  while (nb_item-- != 0)
    {
      (player-- > 0 ? str = my_strcat(str, "player", -1, -1) :
       tmp.linemate-- > 0 ? str = my_strcat(str, "linemate", -1, -1) :
       tmp.deraumere-- > 0 ? str = my_strcat(str, "deraumere", -1, -1) :
       tmp.sibur-- > 0 ? str = my_strcat(str, "sibur", -1, -1) :
       tmp.mendiane-- > 0 ? str = my_strcat(str, "mendiane", -1, -1) :
       tmp.phiras-- > 0 ? str = my_strcat(str, "phiras", -1, -1) :
       tmp.thystame-- > 0 ? str = my_strcat(str, "thystame", -1, -1) :
       tmp.food-- > 0 ? str = my_strcat(str, "food", -1, -1) : 0);
      (nb_item  != 0 ? str = my_strcat(str, " ", -1, -1) : 0);
    }
  return (str);
}
