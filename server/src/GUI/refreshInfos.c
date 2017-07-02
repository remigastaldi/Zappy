/*
** refreshInfos.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Sat Jul  1 15:33:49 2017 sellet_f
** Last update Sat Jul  1 16:03:26 2017 sellet_f
*/

#include "GUI.h"

void		refreshInfos(t_gui *GUI, t_env *env)
{
  sfColor	color;
  int		i;

  i = -1;
  GUI->_caseInfos = env->map[GUI->_caseY][GUI->_caseX];
  if (GUI->_userInfos.socket != -1)
    {
      while (++i < MAX_FD)
  	if (GUI->_userInfos.socket == env->users[i].socket)
  	  {
  	    GUI->_userInfos = env->users[i];
  	    break;
  	  }
      if (i == MAX_FD)
  	{
  	  color = sfSprite_getColor(GUI->_playerInfoSprite);
  	  color.a = 0;
  	  sfSprite_setColor(GUI->_playerInfoSprite, color);
  	}
    }
}
