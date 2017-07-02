/*
** users.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Sat Jul  1 01:19:42 2017 sellet_f
** Last update Sun Jul  2 17:20:09 2017 sellet_f
*/

#include "GUI.h"

int			countNumberTeam(char *str, t_env  *env)
{
  int			i;
  int			counter;

  counter = 0;
  i = -1;
  while (++i != MAX_FD)
    if (env->users[i].socket != -1 && env->users[i].teamName != NULL && str
      && strcmp(env->users[i].teamName, str) == 0)
      counter++;
  return (counter);
}

void			checkPlayerInfos(t_users user, sfIntRect *spritePos, bool checkLvl)
{
  spritePos->top = 0;
  if (checkLvl == true)
    spritePos->left = (user.lvl - 1) * 32;
  else
    {
      spritePos->left = 0;
      if (user.lvl % 2 == 0)
	spritePos->left = 32;
    }
  if (user.direction == LEFT)
    spritePos->top += 32;
  else if (user.direction == RIGHT)
    spritePos->top += 64;
  else if (user.direction == UP)
    spritePos->top += 96;
}

void			drawPlayers(t_gui *GUI, t_env *env, int i)
{
  sfIntRect		spritePos;
  sfVector2f		pos;
  spritePos.width = spritePos.height = 32;
  while (++i < MAX_FD)
    if (env->users[i].socket != -1 && env->users[i].teamName)
      {
	checkPlayerInfos(env->users[i], &spritePos, true);
	pos.x = env->users[i].posX * sfSprite_getGlobalBounds
	  (GUI->_grassSprite).width + env->users[i].graphicX;
	pos.y = env->users[i].posY *sfSprite_getGlobalBounds
	  (GUI->_grassSprite).height
	  + env->users[i].graphicY;
	sfSprite_setPosition(GUI->_playerSprite, pos);
	sfSprite_setTextureRect(GUI->_playerSprite, spritePos);
	sfRenderWindow_drawSprite(GUI->_win, GUI->_playerSprite, NULL);
	if (sfSprite_getColor(GUI->_playerInfoSprite).a == 255 &&
	    env->users[i].socket == GUI->_userInfos.socket)
	  {
	    checkPlayerInfos(env->users[i], &spritePos, false);
	    sfSprite_setPosition(GUI->_selectedPlayerSprite, pos);
	    sfSprite_setTextureRect(GUI->_selectedPlayerSprite, spritePos);
	    sfRenderWindow_drawSprite(GUI->_win, GUI->_selectedPlayerSprite
				      , NULL);
	  }
      }
}

int			countPlayers(t_gui *GUI, t_env *env, bool fillGUI)
{
  int			nb;
  int			i;

  i = -1;
  nb = 0;
  while (++i < MAX_FD)
    if (env->users[i].socket != -1
	&& env->users[i].posY == GUI->_caseY
	&& env->users[i].posX == GUI->_caseX)
      {
	if (nb == 0 && fillGUI == true)
	  GUI->_userInfos = env->users[i];
	nb++;
      }
  return (nb);
}

void			checkPlayerOnTile(t_gui *GUI, t_env *env)
{
  sfColor		color;

  color.r = 255;
  color.g = 255;
  color.b = 255;
  color.a = 255;
  if (countPlayers(GUI, env, true) > 0)
    sfSprite_setColor(GUI->_playerInfoSprite, color);
  else
   {
      color.a = 0;
      sfSprite_setColor(GUI->_playerInfoSprite, color);
    }
}
