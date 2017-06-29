/*
** GUI.h for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Jun 22 10:57:50 2017 sellet_f
** Last update Thu Jun 29 15:44:46 2017 sellet_f
*/

#ifndef __GUI_H__
# define __GUI_H__

# include <SFML/Audio.h>
# include <SFML/Graphics.h>
# include <stdbool.h>
# include <stdlib.h>

# include "utilities.h"

typedef enum		Sprite
  {
    DEFAULT,
    MENU,
    PLAYER
  }			Sprite;

typedef struct		s_gui
{
  sfRenderWindow	*_win;
  sfVideoMode		_mode;
  sfEvent		_event;
  sfView		*_camera;
  sfView		*_interface;

  sfTexture		*_pannelTexture;
  sfSprite		*_pannelSprite;
  sfTexture		*_playerInfoTexture;
  sfSprite		*_playerInfoSprite;
  sfTexture		*_grassTexture;
  sfSprite		*_grassSprite;
  sfTexture		*_playerTexture;
  sfSprite		*_playerSprite;
  sfTexture		*_resourcesTexture;
  sfSprite		*_resourcesSprite;

  sfFont		*_font;
  t_items		_caseInfos;
}			t_gui;

/* initGUI.c */
void		initValueResource(sfVector2f, sfText *, t_gui *, int);
sfVector2f  	initText(sfText **, sfVector2f, t_gui *);
bool		initTexture(t_gui *, sfVector2f);
bool		initGUI(t_gui *, t_env *);

/* GUI.c */
void		destroyGUI(t_gui *);
bool		inputsAndEvents(t_gui *, t_env *);
void		checkResources(t_gui *, int, int, t_env *);

/* drawGUI.c */
void		drawText(t_gui *);
void		drawMap(t_gui *, t_env*);
void		drawGUI(t_gui *, t_env *);

#endif
