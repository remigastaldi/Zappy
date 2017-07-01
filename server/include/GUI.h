/*
** GUI.h for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Thu Jun 22 10:57:50 2017 sellet_f
** Last update Sat Jul  1 13:22:45 2017 sellet_f
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
    PLAYER,
    INVENTORY
  }			Sprite;

typedef enum		Resources
  {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    FOOD,
    EGG
  }			Resources;

typedef struct		s_mapResource
{
  int			left;
  int			top;
  int			width;
  int			height;
  int			x;
  int			y;
}			t_mapResource;

typedef struct		s_gui
{
  sfRenderWindow	*_win;
  sfVideoMode		_mode;
  sfEvent		_event;
  sfView		*_camera;
  sfView		*_interface;
  sfFont		*_font;

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

  t_items		_caseInfos;
  int			_caseX;
  int			_caseY;
  t_users		_userInfos;
}			t_gui;

/* init.c */
sfVector2f  	initText(sfText **, sfVector2f, t_gui *);
bool		initTexture(t_gui *, sfVector2f);
bool		initGUI(t_gui *, t_env *);

/* GUI.c */
void		drawGUI(t_gui *, t_env *);
void		checkMovs(t_gui *, sfVector2f);
bool		checkClickedSprite(t_gui *, t_env *);
bool		inputsAndEvents(t_gui *, t_env *);
void		destroyGUI(t_gui *);

/* map.c */
void		drawResources(t_gui *, int, int, enum Resources);
void		checkResources(t_gui *, int, int, t_env *);
void		drawMap(t_gui *, t_env*);

/* pannel.c */
void		initValueInventory(sfVector2f, sfText *, t_gui *, char *);
void		initValueResource(sfVector2f, sfText *, t_gui *, int);
void		drawInventoryResources(t_gui *, sfVector2f, sfText *);
void		drawInventory(t_gui *, sfVector2f, sfText *, t_env *);
void		drawText(t_gui *, t_env *);

/* users.c */
int		countNumberTeam(char *, t_env *);
void		drawPlayers(t_gui *, t_env *);
int		countPlayers(t_gui *, t_env *, bool);
void		checkPlayerOnTile(t_gui *, t_env *);
#endif
