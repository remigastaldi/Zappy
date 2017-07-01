/*
** pannel.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
** 
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
** 
** Started on  Sat Jul  1 01:16:35 2017 sellet_f
** Last update Sat Jul  1 01:37:08 2017 sellet_f
*/

#include "GUI.h"

void			initValueInventory(sfVector2f pos, sfText *text,
					  t_gui *GUI, char *str)
{
  sfText_setPosition(text, pos);
  sfText_setString(text, str);
  sfRenderWindow_drawText(GUI->_win, text, NULL);
}

void			initValueResource(sfVector2f pos, sfText *text,
					  t_gui *GUI, int resource)
{
  char			str[4];

  bzero(str, 4);
  sfText_setPosition(text, pos);
  sprintf(str, "%d", resource);
  sfText_setString(text, str);
  sfRenderWindow_drawText(GUI->_win, text, NULL);
}


void			drawInventoryResources(t_gui *GUI, sfVector2f pos,
					       sfText *text)
{
  pos.y += 148;
  pos.x += 33;
  sfText_setCharacterSize(text, 50);
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.phiras);
  pos.y += 115;
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.linemate);
  pos.x += 165;
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.sibur);
  pos.x += 170;
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.mendiane);
  pos.y -= 115;
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.deraumere);
  pos.x -= 170;
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.thystame);
  pos.y -= 115;
  pos.x -= 5;
  initValueResource(pos, text, GUI, GUI->_userInfos.inventory.food);
}

void			drawInventory(t_gui *GUI, sfVector2f pos,
				      sfText *text, t_env *env)
{
  if (sfSprite_getColor(GUI->_playerInfoSprite).a == 255)
    {
      pos.y = 730;
      pos.x = 1800;
      initValueInventory(pos, text, GUI, "X = ");
      pos.x += 40;
      initValueResource(pos, text, GUI, GUI->_userInfos.posX);
      pos.y += 40;
      initValueResource(pos, text, GUI, GUI->_userInfos.posY);
      pos.x -= 40;
      initValueInventory(pos, text, GUI, "Y = ");
      pos.x -= 350;
      initValueResource(pos, text, GUI, countNumberTeam(GUI->_userInfos.teamName, env));
      pos.x += 50;
      initValueInventory(pos, text, GUI, " / ");
      pos.x += 50;
      initValueResource(pos, text, GUI, env->clientsNb);
      sfText_setCharacterSize(text, 30);
      pos.y -= 50;
      pos.x -= 100;
      initValueInventory(pos, text, GUI, GUI->_userInfos.teamName);
      drawInventoryResources(GUI, pos, text);
    }
  sfText_destroy(text);
}

void			drawText(t_gui *GUI, t_env *env)
{
  sfText		*text;
  sfVector2f		pos;

  pos = initText(&text, pos, GUI);
  initValueResource(pos, text, GUI, GUI->_caseInfos.sibur);
  pos.x = 1590;
  initValueResource(pos, text, GUI, GUI->_caseInfos.linemate);
  pos.x = 1755;
  initValueResource(pos, text, GUI, GUI->_caseInfos.deraumere);
  pos.x = 1450;
  pos.y = 320;
  initValueResource(pos, text, GUI, GUI->_caseInfos.phiras);
  pos.x = 1590;
  initValueResource(pos, text, GUI, GUI->_caseInfos.mendiane);
  pos.x = 1755;
  initValueResource(pos, text, GUI, GUI->_caseInfos.thystame);
  pos.y = 455;
  pos.x = 1450;
  initValueResource(pos, text, GUI, GUI->_caseInfos.food);
  pos.x = 1590;
  initValueResource(pos, text, GUI, GUI->_caseInfos.egg);
  pos.x = 1755;
  initValueResource(pos, text, GUI, countPlayers(GUI, env, false));
  drawInventory(GUI, pos, text, env);
}
