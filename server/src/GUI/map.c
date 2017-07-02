/*
** map.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Thu Jun 29 17:16:57 2017 sellet_f
** Last update Sun Jul  2 17:47:15 2017 sellet_f
*/

#include "GUI.h"

t_mapResource		spriteValues[] = {
  {0, 37, 18, 25, 2, 2},
  {30, 4, 18, 30, 40 , 2},
  {60, 77, 17, 25, 81, 2},
  {30, 70, 19, 32, 2, 35},
  {0, 0, 16, 31, 2, 67},
  {60, 1, 17, 31, 81, 40},
  {60, 40, 20, 22, 78, 76},
  {0, 69, 23, 33, 40, 66}
};

void			drawResource(t_gui *GUI, int x, int y, enum Resources res)
{
  sfIntRect		spritePos;
  sfVector2f		posOnMap;

  posOnMap.x = x * sfSprite_getGlobalBounds(GUI->_grassSprite).width
    + spriteValues[res].x;
  posOnMap.y = y * sfSprite_getGlobalBounds(GUI->_grassSprite).height
    + spriteValues[res].y;
  spritePos.left = spriteValues[res].left;
  spritePos.top = spriteValues[res].top;
  spritePos.width = spriteValues[res].width;
  spritePos.height = spriteValues[res].height;
  sfSprite_setPosition(GUI->_resourcesSprite, posOnMap);
  sfSprite_setTextureRect(GUI->_resourcesSprite, spritePos);
  sfRenderWindow_drawSprite(GUI->_win, GUI->_resourcesSprite, NULL);
}

void			checkResources(t_gui *GUI, int y, int x, t_env *env)
{
  if (env->map[y][x].linemate > 0)
    drawResource(GUI, x, y, LINEMATE);
  if (env->map[y][x].deraumere > 0)
    drawResource(GUI, x, y, DERAUMERE);
  if (env->map[y][x].sibur > 0)
    drawResource(GUI, x, y, SIBUR);
  if (env->map[y][x].mendiane > 0)
    drawResource(GUI, x, y, MENDIANE);
  if (env->map[y][x].phiras > 0)
    drawResource(GUI, x, y, PHIRAS);
  if (env->map[y][x].thystame > 0)
    drawResource(GUI, x, y, THYSTAME);
  if (env->map[y][x].food > 0)
    drawResource(GUI, x, y, FOOD);
  if (env->map[y][x].egg > 0)
    drawResource(GUI, x, y, EGG);
}

void			drawMap(t_gui *GUI, t_env *env, int y)
{
  sfVector2f		tilePos;
  int			x;

  y = -1;
  while (++y < env->height)
    {
      x = -1;
      while (++x < env->width)
	{
          tilePos.x = x * sfSprite_getGlobalBounds(GUI->_grassSprite).width;
	  tilePos.y = y * sfSprite_getGlobalBounds(GUI->_grassSprite).height;
	  if (x == GUI->_caseX && y == GUI->_caseY)
	    {
	      sfSprite_setPosition(GUI->_selectedGrassSprite, tilePos);
	      sfRenderWindow_drawSprite(GUI->_win,
					GUI->_selectedGrassSprite, NULL);
	    }
	  else
	    {
	      sfSprite_setPosition(GUI->_grassSprite, tilePos);
	      sfRenderWindow_drawSprite(GUI->_win, GUI->_grassSprite, NULL);
	    }
	  checkResources(GUI, y, x, env);
	}
    }
}
