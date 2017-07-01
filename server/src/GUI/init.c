/*
** init.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Jun 27 17:37:13 2017 sellet_f
** Last update Sat Jul  1 01:29:44 2017 sellet_f
*/

#include "GUI.h"


sfVector2f	initText(sfText **text, sfVector2f pos, t_gui *GUI)
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
  GUI-> _caseInfos.linemate = GUI->_caseInfos.deraumere = 0;
  GUI->_caseInfos.sibur = GUI->_caseInfos.mendiane = 0;
  GUI->_caseInfos.phiras = GUI->_caseInfos.thystame = GUI->_caseInfos.food = 0;
  GUI->_caseInfos.egg = 0;
  GUI->_interface = sfView_copy(sfRenderWindow_getView(GUI->_win));
  GUI->_camera = sfView_copy(GUI->_interface);
  vector.x = env->width / 2 * sfTexture_getSize(GUI->_grassTexture).x;
  vector.y = env->height / 2 * sfTexture_getSize(GUI->_grassTexture).y;
  sfView_setCenter(GUI->_camera, vector);
  return (true);
}

sfSprite	*initSprite(sfSprite *sprite, sfVector2f spritePos,
			    sfTexture *texture, enum Sprite type)
{
  sfVector2f	spriteScale;
  sfColor	spriteColor;

  spriteScale.x = 1;
  spriteScale.y = 1;
  if (type == MENU)
    spriteScale.y = 1.055;
  else if (type == PLAYER)
    spriteScale.y = spriteScale.x = 1.3;
  spriteColor.r = 255;
  spriteColor.g = 255;
  spriteColor.b = 255;
  spriteColor.a = type == INVENTORY ? 0 : 255;
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
	sfTexture_createFromFile("./server/media/playerInfos2.png", NULL)) ||
      !(GUI->_grassTexture =
	sfTexture_createFromFile("./server/media/grass2.jpg", NULL)) ||
      !(GUI->_resourcesTexture =
	sfTexture_createFromFile("./server/media/resources.png", NULL)) ||
      !(GUI->_playerTexture =
	sfTexture_createFromFile("./server/media/playersprite.png", NULL)))
    return (false);

  GUI->_pannelSprite = initSprite(GUI->_pannelSprite, spritePos, GUI->_pannelTexture, MENU);
  spritePos.x += 72;
  spritePos.y += 713;
  GUI->_playerInfoSprite = initSprite(GUI->_playerInfoSprite,
  				      spritePos, GUI->_playerInfoTexture, INVENTORY);
  GUI->_grassSprite = initSprite(GUI->_grassSprite, spritePos,
				 GUI->_grassTexture, DEFAULT);
  GUI->_resourcesSprite = initSprite(GUI->_resourcesSprite, spritePos,
				 GUI->_resourcesTexture, DEFAULT);
  GUI->_playerSprite = initSprite(GUI->_playerSprite, spritePos,
				 GUI->_playerTexture, PLAYER);
  return (true);
}
