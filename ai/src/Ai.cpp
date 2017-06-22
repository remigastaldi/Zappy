//
// Ai.cpp for zappy in /home/gastal_r/rendu/Zappy/Ai/src
//
// Made by
// Login   <gastal_r>
//
// Started on  Wed Jun 21 13:20:37 2017
// Last update Wed Jun 21 13:20:39 2017
//

#include      "Ai.hpp"

Ai::Ai(int port, char* machine) noexcept
  : Communication(port, machine),
  _riseUpConditions({
  {1, {{Ai::Properties::NB_PLAYER, 1}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 0}, {Ai::Properties::SIBUR, 0}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0}}},
  {2, {{Ai::Properties::NB_PLAYER, 2}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 1}, {Ai::Properties::SIBUR, 1}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0}}},
  {3, {{Ai::Properties::NB_PLAYER, 2}, {Ai::Properties::LINEMATE, 2}, {Ai::Properties::DERAUMERE, 0}, {Ai::Properties::SIBUR, 1}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 2}, {Ai::Properties::THYSTAME, 0}}},
  {4, {{Ai::Properties::NB_PLAYER, 4}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 1}, {Ai::Properties::SIBUR, 2}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 1}, {Ai::Properties::THYSTAME, 0}}},
  {5, {{Ai::Properties::NB_PLAYER, 4}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 2}, {Ai::Properties::SIBUR, 1}, {Ai::Properties::MENDIANE, 3}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0}}},
  {6, {{Ai::Properties::NB_PLAYER, 6}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 2}, {Ai::Properties::SIBUR, 3}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 1}, {Ai::Properties::THYSTAME, 0}}},
  {7, {{Ai::Properties::NB_PLAYER, 6}, {Ai::Properties::LINEMATE, 2}, {Ai::Properties::DERAUMERE, 2}, {Ai::Properties::SIBUR, 2}, {Ai::Properties::MENDIANE, 2}, {Ai::Properties::PHIRAS, 2}, {Ai::Properties::THYSTAME, 1}}},
  }),
  _currentLevel(1)
{}

void      Ai::start(void) noexcept
{
  try
  {
    lookForResources();
  }
  catch (const std::exception &error)
  {

  }
}

bool      Ai::needResources(void) noexcept
{
  if (_currentItems[Ai::Properties::LINEMATE] >= _riseUpConditions[_currentLevel][Ai::Properties::LINEMATE]
    && _currentItems[Ai::Properties::DERAUMERE] >= _riseUpConditions[_currentLevel][Ai::Properties::DERAUMERE]
    && _currentItems[Ai::Properties::SIBUR] >= _riseUpConditions[_currentLevel][Ai::Properties::SIBUR]
    && _currentItems[Ai::Properties::MENDIANE] >= _riseUpConditions[_currentLevel][Ai::Properties::MENDIANE]
    && _currentItems[Ai::Properties::PHIRAS] >= _riseUpConditions[_currentLevel][Ai::Properties::PHIRAS]
    && _currentItems[Ai::Properties::THYSTAME] >= _riseUpConditions[_currentLevel][Ai::Properties::THYSTAME])
    {
      return (false);
    }
  return (true);
}

bool      Ai::broadcast(void) noexcept
{
  return (true);
}

bool      Ai::lookForResources(void) noexcept
{
  std::string rawView("player,,,thystame,,mendiane phiras,,,,,thystame,,,,,,");

  std::vector<std::vector<std::string>>  view;

  size_t posCase = 0;
  std::string currentCase;
  while ((posCase = rawView.find(",")) != std::string::npos)
  {
    currentCase = rawView.substr(0, posCase);
    size_t posItem = 0;
    std::vector<std::string> caseItems;
    if ((posItem = currentCase.find(" ")) != std::string::npos)
    {
      while ((posItem = currentCase.find(" ")) != std::string::npos)
      {
        std::string currentItem(currentCase.substr(0, posItem));
        caseItems.push_back(currentCase);
        currentCase.erase(0, posItem + 1);
      }
    }
    caseItems.push_back(currentCase);
    view.push_back(caseItems);
    rawView.erase(0, posCase + 1);
  }
  size_t caseNbr(0);
  std::cout << "Look command result: " << std::endl;
  for (auto & it : view)
  {
    for (auto & it2 : it)
    {
      std::cout << "[" << caseNbr++ << "]" << it2 << std::endl;
    }
  }
  return (true);
}
