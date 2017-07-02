/*
** sprites.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Sun Jul  2 17:09:23 2017 sellet_f
** Last update Sun Jul  2 17:45:37 2017 sellet_f
*/

#include "GUI.h"

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

bool		setTextureValues(t_gui *GUI)
{
  if (!(GUI->_pannelTexture =
	sfTexture_createFromFile("./server/media/pannel.png", NULL)) ||
      !(GUI->_playerInfoTexture =
	sfTexture_createFromFile("./server/media/playerInfos.png", NULL)) ||
      !(GUI->_grassTexture =
	sfTexture_createFromFile("./server/media/grass.jpg", NULL)) ||
      !(GUI->_resourcesTexture =
	sfTexture_createFromFile("./server/media/resources.png", NULL)) ||
      !(GUI->_selectedGrassTexture =
	sfTexture_createFromFile("./server/media/highlightedGrass.jpg", NULL)) ||
      !(GUI->_selectedPlayerTexture =
	sfTexture_createFromFile("./server/media/highlightedPlayer.png", NULL)) ||
      !(GUI->_playerTexture =
	sfTexture_createFromFile("./server/media/playersprite.png", NULL)))
    return (false);
  return (true);
}

bool		initTexture(t_gui *GUI, sfVector2f spritePos)
{
  if (setTextureValues(GUI) == false)
    return (false);
  GUI->_pannelSprite = initSprite(GUI->_pannelSprite,
				  spritePos, GUI->_pannelTexture, MENU);
  spritePos.x += 72;
  spritePos.y += 713;
  GUI->_playerInfoSprite = initSprite(GUI->_playerInfoSprite,
  				      spritePos, GUI->_playerInfoTexture,
				      INVENTORY);
  GUI->_grassSprite = initSprite(GUI->_grassSprite, spritePos,
				 GUI->_grassTexture, DEFAULT);
  GUI->_selectedGrassSprite = initSprite(GUI->_selectedGrassSprite, spritePos,
				 GUI->_selectedGrassTexture, DEFAULT);
  GUI->_resourcesSprite = initSprite(GUI->_resourcesSprite, spritePos,
				 GUI->_resourcesTexture, DEFAULT);
  GUI->_playerSprite = initSprite(GUI->_playerSprite, spritePos,
				 GUI->_playerTexture, PLAYER);
  GUI->_selectedPlayerSprite = initSprite(GUI->_selectedPlayerSprite,
					  spritePos,
					  GUI->_selectedPlayerTexture,
					  PLAYER);
  return (true);
}
