/*
** GUI.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Thu Jun 22 11:02:53 2017 sellet_f
** Last update Thu Jun 22 20:46:10 2017 sellet_f
*/

#include "GUI.h"

sfSprite	*initSprite(sfSprite *sprite, sfVector2f spritePos, sfTexture *texture)
{
  sfVector2f	spriteScale;
  sfColor	spriteColor;

  spriteScale.x = 1;
  spriteScale.y = 1.055;
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
  if ((GUI->_pannelTexture =
       sfTexture_createFromFile("./server/media/pannel4.png", NULL)) == NULL)
    return (false);
  GUI->_pannelSprite = initSprite(GUI->_pannelSprite, spritePos, GUI->_pannelTexture);
  if ((GUI->_playerInfoTexture =
       sfTexture_createFromFile("./server/media/playerFound.png", NULL)) == NULL)
    return (false);
  spritePos.x = 1411;
  spritePos.y = 702;
  GUI->_playerInfoSprite = initSprite(GUI->_playerInfoSprite, spritePos, GUI->_playerInfoTexture);
  return (true);
}

bool		initGUI(t_gui *GUI)
{
  sfVector2f	spritePos;

  spritePos.x = 1342;
  spritePos.y = 0;
  GUI->_mode.width = 1920;
  GUI->_mode.height = 1080;
  GUI->_mode.bitsPerPixel = 32;
  if ((GUI->_win = sfRenderWindow_create(GUI->_mode, "Zappy", sfFullscreen, NULL)) == NULL)
    return (false);
  initTexture(GUI, spritePos);
  return (true);
}
