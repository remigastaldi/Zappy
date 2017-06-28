/*
** GUI.h for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Jun 22 10:57:50 2017 sellet_f
** Last update Wed Jun 28 11:23:58 2017 gastal_r
*/

#ifndef __GUI_H__
# define __GUI_H__

# include <SFML/Audio.h>
# include <SFML/Graphics.h>
# include <stdbool.h>
# include <stdlib.h>

# include "utilities.h"


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
  sfTexture		*_stoneTexture;
  sfSprite		*_stoneSprite;

  sfFont		*_font;
  t_items		_caseInfos;
}			t_gui;

/* initGUI.c */
void		initValueResource(sfVector2f, sfText *, t_gui *, int);
void  	initText(sfText **, sfVector2f *, t_gui *);
bool		initGUI(t_gui *, t_env *);
sfSprite	*initSprite(sfSprite *, sfVector2f, sfTexture *, bool);
bool		initTexture(t_gui *, sfVector2f);

/* GUI.c */
void		destroyGUI(t_gui *);
bool		inputsAndEvents(t_gui *, t_env *);

/* drawGUI.c */
void		drawMap(t_gui *, t_env*);
void		drawText(t_gui *);
void		drawGUI(t_gui *, t_env *);

#endif
