/*
** init.c for Project-Master in /home/sellet_f/Projets/Tek2/Zappy
**
** Made by sellet_f
** Login   <flavien.sellet@epitech.eu>
**
** Started on  Tue Jun 27 17:37:13 2017 sellet_f
** Last update Sun Jul  2 17:48:12 2017 sellet_f
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

void		initUserInfos(t_gui *GUI)
{
  GUI->_userInfos.socket = -1;
  GUI->_userInfos.posY = GUI->_userInfos.posX = 0;
  GUI->_userInfos.graphicX = GUI->_userInfos.graphicY = 0;
  GUI->_userInfos.lvl = 0;
  GUI->_userInfos.teamName = NULL;
  GUI->_userInfos.direction = UP;
  GUI->_userInfos.food_timer = 0;
  GUI->_userInfos.lock = false;
  GUI->_userInfos.inventory.linemate = GUI->_userInfos.inventory.deraumere = 0;
  GUI->_userInfos.inventory.sibur = GUI->_userInfos.inventory.mendiane = 0;
  GUI->_userInfos.inventory.phiras = GUI->_userInfos.inventory.thystame = 0;
  GUI->_userInfos.inventory.egg = GUI->_userInfos.inventory.food = 0;
}

void		initCaseInfos(t_gui *GUI)
{
  GUI->_caseInfos.linemate = GUI->_caseInfos.deraumere = 0;
  GUI->_caseInfos.sibur = GUI->_caseInfos.mendiane = 0;
  GUI->_caseInfos.phiras = GUI->_caseInfos.thystame = GUI->_caseInfos.food = 0;
  GUI->_caseInfos.egg = GUI->_caseX = GUI->_caseY = 0;
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
  initCaseInfos(GUI);
  initUserInfos(GUI);
  GUI->_interface = sfView_copy(sfRenderWindow_getView(GUI->_win));
  GUI->_camera = sfView_copy(GUI->_interface);
  vector.x = env->width / 2 * sfTexture_getSize(GUI->_grassTexture).x;
  vector.y = env->height / 2 * sfTexture_getSize(GUI->_grassTexture).y;
  sfView_setCenter(GUI->_camera, vector);
  return (true);
}
