/*
** GUI.h for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Jun 22 10:57:50 2017 sellet_f
** Last update Sat Jun 24 14:06:33 2017 Leo Hubert Froideval
*/

#ifndef __GUI_H__
# define __GUI_H__

# include <SFML/Audio.h>
# include <SFML/Graphics.h>
# include <stdbool.h>

typedef struct		s_gui
{
  sfRenderWindow	*_win;
  sfVideoMode		_mode;
  sfEvent	      	_event;

  sfTexture		    *_pannelTexture;
  sfSprite		    *_pannelSprite;

  sfTexture		    *_playerInfoTexture;
  sfSprite		    *_playerInfoSprite;
}			        t_gui;

bool                initGUI(t_gui *);

#endif
