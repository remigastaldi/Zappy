/*
** GUI.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Jun 22 11:02:53 2017 sellet_f
** Last update Thu Jun 29 13:00:48 2017 sellet_f
*/

#include "GUI.h"

void			checkMovs(t_gui *GUI, sfVector2f vec)
{
  if (sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue ||
      sfKeyboard_isKeyPressed(sfKeyQ) == sfTrue)
    {
      vec.x = -5;
      sfView_move(GUI->_camera, vec);
    }
  else if (sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue ||
	   sfKeyboard_isKeyPressed(sfKeyD) == sfTrue)
    {
      vec.x = 5;
      sfView_move(GUI->_camera, vec);
    }
  else if (sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue ||
	   sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue)
    {
      vec.y = -5;
      sfView_move(GUI->_camera, vec);
    }
  else if (sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue ||
	   sfKeyboard_isKeyPressed(sfKeyS) == sfTrue)
    {
      vec.y = 5;
      sfView_move(GUI->_camera, vec);
    }
}

bool			checkClickedSprite(t_gui *GUI, t_env *env)
{
  sfVector2f		mouseInWorld;
  int			x;
  int			y;

  mouseInWorld = sfRenderWindow_mapPixelToCoords
    (GUI->_win, sfMouse_getPositionRenderWindow(GUI->_win), GUI->_camera);
  if ((mouseInWorld.x < 0 || mouseInWorld.x > env->width * 100) ||
      (mouseInWorld.y < 0 || mouseInWorld.y > env->height * 100))
    return (false);
  x = -1;
  while (++x < env->height)
    {
      y = -1;
      while (++y < env->width)
	if ((mouseInWorld.x > x * 100 && mouseInWorld.x < x * 100 + 100) &&
	    (mouseInWorld.y > y * 100 && mouseInWorld.y < y * 100 + 100))
	  {
	    GUI->_caseInfos = env->map[x][y];
	    return (true);
	  }
    }
  return (true);
}

bool			inputsAndEvents(t_gui *GUI, t_env *env)
{
  sfVector2f		vec;

  vec.x = 0;
  vec.y = 0;
  if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
    sfRenderWindow_close(GUI->_win);
  else if (sfMouse_isButtonPressed(sfMouseLeft) == sfTrue)
    checkClickedSprite(GUI, env);
  else
    checkMovs(GUI, vec);
  while (sfRenderWindow_pollEvent(GUI->_win, &GUI->_event))
    if (GUI->_event.type == sfEvtClosed)
      sfRenderWindow_close(GUI->_win);
    else if (GUI->_event.type == sfEvtMouseWheelMoved)
      sfView_zoom(GUI->_camera, 1 + GUI->_event.mouseWheel.delta * -0.1);
  return (true);
}

void		destroyGUI(t_gui *GUI)
{
  sfRenderWindow_destroy(GUI->_win);
  sfTexture_destroy(GUI->_grassTexture);
  sfSprite_destroy(GUI->_grassSprite);
  sfTexture_destroy(GUI->_pannelTexture);
  sfSprite_destroy(GUI->_pannelSprite);
  sfTexture_destroy(GUI->_playerInfoTexture);
  sfSprite_destroy(GUI->_playerInfoSprite);
  sfTexture_destroy(GUI->_stoneTexture);
  sfSprite_destroy(GUI->_stoneSprite);
  sfFont_destroy(GUI->_font);
  sfView_destroy(GUI->_camera);
  sfView_destroy(GUI->_interface);
}
