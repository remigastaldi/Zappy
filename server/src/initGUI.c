/*
** initGUI.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Tue Jun 27 17:37:13 2017 sellet_f
** Last update Tue Jun 27 17:40:08 2017 sellet_f
*/

#include "GUI.h"

void			initValueResource(sfVector2f pos, sfText *text,
					  t_gui *GUI, int resource)
{
  char			str[4];

  sfText_setPosition(text, pos);
  sprintf(str, "%d", resource);
  sfText_setString(text, str);
  sfRenderWindow_drawText(GUI->_win, text, NULL);
}

sfVector2f		initText(sfText **text, sfVector2f pos, t_gui *GUI)
{
  *text = sfText_create();
  sfText_setCharacterSize(*text, 20);
  sfText_setFont(*text, GUI->_font);
  pos.x = 1450;
  pos.y = 170;
  return (pos);
}

bool		initGUI(t_gui *GUI, t_env *env)
{
  sfVector2f	vector;

  if (!(GUI->_font = sfFont_createFromFile("./server/media/interface.ttf")))
    return (false);
  GUI->_mode.width = 1920;
  GUI->_mode.height = 1080;
  vector.x = GUI->_mode.width * 0.69895;
  vector.y = 0;
  GUI->_mode.bitsPerPixel = 32;
  if ((GUI->_win = sfRenderWindow_create(GUI->_mode, "Zappy",
					 sfResize | sfClose, NULL)) == NULL)
    return (false);
  initTexture(GUI, vector);

  GUI->_interface = sfView_copy(sfRenderWindow_getView(GUI->_win));
  GUI->_camera = sfView_copy(GUI->_interface);
  vector.x = env->width / 2 * sfTexture_getSize(GUI->_grassTexture).x;
  vector.y = env->height / 2 * sfTexture_getSize(GUI->_grassTexture).y;
  sfView_setCenter(GUI->_camera, vector);
  return (true);
}

sfSprite	*initSprite(sfSprite *sprite, sfVector2f spritePos,
			    sfTexture *texture, bool isMenu)
{
  sfVector2f	spriteScale;
  sfColor	spriteColor;

  spriteScale.x = 1;
  if (isMenu == true)
    spriteScale.y = 1.055;
  else
    spriteScale.y = 1;
  spriteColor.r = 255;
  spriteColor.g = 255;
  spriteColor.b = 255;
  spriteColor.a = 255;

  sprite = sfSprite_create();
  sfSprite_setTexture(sprite, texture, sfTrue);
  sfSprite_setScale(sprite, spriteScale);
  sfSprite_setPosition(sprite, spritePos);
  sfSprite_setColor(sprite, spriteColor);
  return (sprite);
}

bool	initTexture(t_gui *GUI, sfVector2f spritePos)
{
  if (!(GUI->_pannelTexture =
       sfTexture_createFromFile("./server/media/pannel.png", NULL)) || 
      !(GUI->_playerInfoTexture =
	sfTexture_createFromFile("./server/media/playerFound.png", NULL)) ||
      !(GUI->_grassTexture =
	sfTexture_createFromFile("./server/media/grass.jpg", NULL)) ||
      !(GUI->_stoneTexture =
	sfTexture_createFromFile("./server/media/stone.jpg", NULL)))
    return (false);

  GUI->_pannelSprite = initSprite(GUI->_pannelSprite, spritePos, GUI->_pannelTexture, true);
  spritePos.x = GUI->_mode.height * 0.73489;
  spritePos.y = GUI->_mode.width * 0.66851;
  GUI->_playerInfoSprite = initSprite(GUI->_playerInfoSprite,
  				      spritePos, GUI->_playerInfoTexture, false);
  GUI->_grassSprite = initSprite(GUI->_grassSprite, spritePos,
				 GUI->_grassTexture, false);
  GUI->_stoneSprite = initSprite(GUI->_stoneSprite, spritePos,
				 GUI->_stoneTexture, false);
  return (true);
}
