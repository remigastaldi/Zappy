//
// Ai.cpp for zappy in /home/gastal_r/rendu/Zappy/Ai/src
//
// Made by
// Login   <gastal_r>
//
// Started on  Wed Jun 21 13:20:37 2017
// Last update Wed Jun 21 13:20:39 2017
//


// To not forget to remove sleep
#include <chrono>
#include <thread>

#include      "Ai.hpp"
#include      "Utils.hpp"

Ai::Ai(int port, const std::string &machine, const std::string &teamName) noexcept
  : Communication(port, teamName, machine),
  _riseUpConditions({
  {1, {{Ai::Properties::NB_PLAYER, 1}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 0}, {Ai::Properties::SIBUR, 0}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0}}},
  {2, {{Ai::Properties::NB_PLAYER, 2}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 1}, {Ai::Properties::SIBUR, 1}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0}}},
  {3, {{Ai::Properties::NB_PLAYER, 2}, {Ai::Properties::LINEMATE, 2}, {Ai::Properties::DERAUMERE, 0}, {Ai::Properties::SIBUR, 1}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 2}, {Ai::Properties::THYSTAME, 0}}},
  {4, {{Ai::Properties::NB_PLAYER, 4}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 1}, {Ai::Properties::SIBUR, 2}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 1}, {Ai::Properties::THYSTAME, 0}}},
  {5, {{Ai::Properties::NB_PLAYER, 4}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 2}, {Ai::Properties::SIBUR, 1}, {Ai::Properties::MENDIANE, 3}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0}}},
  {6, {{Ai::Properties::NB_PLAYER, 6}, {Ai::Properties::LINEMATE, 1}, {Ai::Properties::DERAUMERE, 2}, {Ai::Properties::SIBUR, 3}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 1}, {Ai::Properties::THYSTAME, 0}}},
  {7, {{Ai::Properties::NB_PLAYER, 6}, {Ai::Properties::LINEMATE, 2}, {Ai::Properties::DERAUMERE, 2}, {Ai::Properties::SIBUR, 2}, {Ai::Properties::MENDIANE, 2}, {Ai::Properties::PHIRAS, 2}, {Ai::Properties::THYSTAME, 1}}},
  }),
  _currentItems({ {Ai::Properties::LINEMATE, 10}, {Ai::Properties::LINEMATE, 0}, {Ai::Properties::DERAUMERE, 0}, {Ai::Properties::SIBUR, 0}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0} }),
  _currentLevel(1)
{}

void      Ai::start(void) noexcept
{
  try
  {
    primaryState();
  }
  catch (const Event::Dead &event)
  {
    std::cout << "Player " <<  _machine << " die" << std::endl;
  }
  catch (const Event::Ko &event)
  {
    std::cout << "Server return KO " << std::endl;
    primaryState();
  }
  catch (const Event::GameOver &event)
  {
    std::cout << "Team : " << event.getTeamName() << " won"<< std::endl;
  }
  catch (const Event::Broadcast &event)
  {
    std::cout << "Broadcast : " << event.getCase() << std::endl;
    if (event.getCase() == 0)
    {
      sendCommand("Incantation");
    }
    else
      walkToBroadcaster(event.getCase());
    primaryState();
  }
  catch (const Event::DeadBroadcaster &event)
  {
    primaryState();
  }
}

void      Ai::primaryState(void) noexcept
{
  actualiseInventory();
  if (_currentItems[Ai::Properties::FOOD] < 5)
  {
    for (int checkRotation = 0;  checkRotation < 3; ++checkRotation)
    {
      actualiseView();
      if (lookForFood())
        return (primaryState());
      sendCommand("Right");
    }
    for (size_t i = 0; i < _currentLevel; ++i)
      _path.push_back(Ai::Direction::FORWARD);
    walkToDir();
    return (primaryState());
  }
  else if (checkIfNeedResources())
  {
    for (int checkRotation = 0;  checkRotation < 3; ++checkRotation)
    {
      actualiseView();
      if (lookForResources())
        return (primaryState());
      else if (lookForFood())
        return (primaryState());
      sendCommand("Right");
    }
    sendCommand("Forward");
    return (primaryState());
  }
  else
  {
    actualiseView();
    powerupState();
    return (primaryState());
  }
}

void      Ai::powerupState(void) noexcept
{
  // if (countPlayer() < _riseUpConditions[_currentLevel][Ai::Properties::NB_PLAYER])
  if (countPlayer() == 0)
  {
    sendCommand("Broadcast");
    powerupState();
  }
  else
  {
    sendCommand("Incantation");
  }
}

size_t    Ai::countPlayer(void) const noexcept
{
  size_t nb = 0;

  for (auto & it : _view.at(0))
  {
    if (it == Ai::Properties::NB_PLAYER)
      nb++;
  }
  return (nb);
}

void      Ai::actualiseInventory(void) noexcept
{
  sendCommand("Inventory");

  size_t posCase = 0;
  std::string item;
  while ((posCase = _answer.find(",")) != std::string::npos)
  {
    item = _answer.substr(0, posCase);
    size_t posItem = 0;
    posItem = item.find(" ");
    std::string itemName(item.substr(0, posItem));
    item.erase(0, posItem + 1);
    std::cout << itemName << std::endl;
    std::cout << item << std::endl;
    _currentItems[Utils::stringToEnum(itemName)] = std::stoi(item);
    _answer.erase(0, posCase + 2);
  }
}

bool      Ai::checkIfNeedResources(void) noexcept
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

void    Ai::actualiseView(void) noexcept
{
  sendCommand("Look");
  _answer = "player,,,thystame,,food,,,,,,linemate,,,,,";

  _view.clear();
  size_t posCase = 0;
  std::string currentCase;
  while ((posCase = _answer.find(",")) != std::string::npos)
  {
    currentCase = _answer.substr(0, posCase);
    size_t posItem = 0;
    std::vector<Ai::Properties> caseItems;
    if ((posItem = currentCase.find(" ")) != std::string::npos)
    {
      while ((posItem = currentCase.find(" ")) != std::string::npos)
      {
        std::string currentItem(currentCase.substr(0, posItem));
        caseItems.push_back(Utils::stringToEnum(currentItem));
        currentCase.erase(0, posItem + 1);
      }
    }
    caseItems.push_back(Utils::stringToEnum(currentCase));
    _view.push_back(caseItems);
    _answer.erase(0, posCase + 1);
  }
}

bool    Ai::lookForFood(void) noexcept
{
  int foodCase = findFoodCase();
  if (foodCase == -1)
    return (false);
  else if (foodCase == 0)
  {
    sendCommand("Take " + Utils::enumToString(_objectToTake));
  }
  else
  {
    calculatePath(foodCase);
    walkToDir();
    actualiseView();
    return (lookForFood());
  }
  return (true);
}

int       Ai::findFoodCase(void) noexcept
{
  size_t caseNbr = 0;
  for (const auto & currentCase : _view)
  {
    for (const auto & currentItem : currentCase)
    {
      if (currentItem == Ai::Properties::FOOD)
      {
        _objectToTake = Ai::Properties::FOOD;
        return (caseNbr);
      }
    }
    caseNbr++;
  }
  return (-1);
}

bool      Ai::lookForResources(void) noexcept
{
  size_t caseNbr(0);
  std::cout << "Look command result: " << std::endl;
  for (const auto & caseIt : _view)
  {
    std::cout << "[" << caseNbr++ << "]";
    for (const auto & item : caseIt)
    {
      std::cout << " " << (int) item << " ";
    }
    std::cout << std::endl;
  }
  int resourceCase = findNeededResourceCase();
  if (resourceCase == -1)
    return (false);
  else if (resourceCase == 0)
  {
    sendCommand("Take " + Utils::enumToString(_objectToTake));
  }
  else
  {
    calculatePath(resourceCase);
    walkToDir();
    actualiseView();
    return (lookForResources());
  }
  return (true);
}

int      Ai::findNeededResourceCase(void) noexcept
{
  size_t caseNbr = 0;
  for (const auto & currentCase : _view)
  {
    for (const auto & currentItem : currentCase)
    {
      if ((currentItem == Ai::Properties::LINEMATE) &&  _currentItems[Ai::Properties::LINEMATE] < _riseUpConditions[_currentLevel][Ai::Properties::LINEMATE])
      {
        _objectToTake = Ai::Properties::LINEMATE;
          return (caseNbr);
      }
      if ((currentItem == Ai::Properties::DERAUMERE) &&  _currentItems[Ai::Properties::DERAUMERE] < _riseUpConditions[_currentLevel][Ai::Properties::DERAUMERE])
      {
        _objectToTake = Ai::Properties::DERAUMERE;
          return (caseNbr);
      }
      if ((currentItem == Ai::Properties::SIBUR) &&  _currentItems[Ai::Properties::SIBUR] < _riseUpConditions[_currentLevel][Ai::Properties::SIBUR])
      {
        _objectToTake = Ai::Properties::SIBUR;
          return (caseNbr);
      }
      if ((currentItem == Ai::Properties::MENDIANE) &&  _currentItems[Ai::Properties::MENDIANE] < _riseUpConditions[_currentLevel][Ai::Properties::MENDIANE])
      {
        _objectToTake = Ai::Properties::MENDIANE;
          return (caseNbr);
      }
      if ((currentItem == Ai::Properties::PHIRAS) &&  _currentItems[Ai::Properties::PHIRAS] < _riseUpConditions[_currentLevel][Ai::Properties::PHIRAS])
      {
        _objectToTake = Ai::Properties::PHIRAS;
          return (caseNbr);
      }
      if ((currentItem == Ai::Properties::THYSTAME) &&  _currentItems[Ai::Properties::THYSTAME] < _riseUpConditions[_currentLevel][Ai::Properties::THYSTAME])
      {
        _objectToTake = Ai::Properties::THYSTAME;
          return (caseNbr);
      }
    }
    caseNbr++;
  }
  return (-1);
}

void      Ai::calculatePath(int resourceCase) noexcept
{
  int   offsetX = 0;
  int   offsetY = 0;
  int   nextLineOffset = 0;
  int   curMaxOffsetX = 0;
  int   curMinOffsetX = 0;
  int   currentCase = 0;
  Ai::Direction curDirection = Ai::Direction::FORWARD;

  std::cout << "ressourceCase => " << resourceCase << std::endl << std::endl;
  while (currentCase != resourceCase)
  {
    curMinOffsetX = offsetY * offsetY;
    curMaxOffsetX = curMinOffsetX + offsetY * 2;
    // std::cout << "curMinOffsetX: " << curMinOffsetX << std::endl;
    // std::cout << "curMaxOffsetX: " << curMaxOffsetX << std::endl;
    nextLineOffset = ((offsetY + 1) * (offsetY + 1)) + (offsetY > 0 ? offsetX + 1 : offsetX);
    std::cout << "currentCase: " << currentCase << std::endl;
    int direction = calculateDirection(resourceCase, (currentCase - 1 < curMinOffsetX ? currentCase : currentCase - 1), nextLineOffset,
      (currentCase + 1 > curMaxOffsetX ? currentCase : currentCase + 1));
    std::cout << "direction=> " << direction << std::endl;
    if (direction == 0)
    {
      offsetX -= 1;
      currentCase -= 1;
      curDirection != Ai::Direction::LEFT ? _path.push_back(Ai::Direction::LEFT) : (void)0;
      curDirection = Ai::Direction::LEFT;
    }
    else if (direction == 1)
    {
      offsetY += 1;
      offsetX += 1;
      currentCase = offsetY * offsetY + offsetX;
      curDirection != Ai::Direction::UP ? _path.push_back(Ai::Direction::UP) : (void)0;
      curDirection = Ai::Direction::UP;
    }
    else if (direction == 2)
    {
      offsetX += 1;
      currentCase += 1;
      curDirection != Ai::Direction::RIGHT ? _path.push_back(Ai::Direction::RIGHT) : (void)0;
      curDirection = Ai::Direction::RIGHT;
    }
    _path.push_back(Ai::Direction::FORWARD);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout  << std::endl;
  }
}

int     Ai::calculateDirection(int destination, int a, int b, int c) noexcept
{
  int aLength = destination - a;
  int bLength = destination - b;
  int cLength = destination - c;

  aLength < 0 ? aLength *= -1 : 0;
  bLength < 0 ? bLength *= -1 : 0;
  cLength < 0 ? cLength *= -1 : 0;
  // std::cout << "a: " << a << "  b: " << b << "  c: " << c << std::endl;
  // std::cout << "aLength: " << aLength << "  bLength: " << bLength << "  cLength: " << cLength << std::endl;
  return ((aLength < bLength && aLength < cLength ? 0 : (bLength < aLength && bLength < cLength ? 1 : 2)));
}

void    Ai::walkToBroadcaster(int caseId) noexcept
{
  if (caseId == 1 || caseId == 2 || caseId == 8)
    _path.push_back(Ai::Direction::FORWARD);
  else if (caseId == 3)
  {
    _path.push_back(Ai::Direction::LEFT);
    _path.push_back(Ai::Direction::FORWARD);
  }
  else if (caseId == 7)
  {
    _path.push_back(Ai::Direction::RIGHT);
    _path.push_back(Ai::Direction::FORWARD);
  }
  if (caseId == 4 || caseId == 5 || caseId == 6)
  {
    _path.push_back(Ai::Direction::RIGHT);
    _path.push_back(Ai::Direction::RIGHT);
    _path.push_back(Ai::Direction::FORWARD);
  }
  walkToDir();
}

void    Ai::walkToDir(void) noexcept
{
  for (const auto & it : _path)
  {
    sendCommand(Utils::enumToString(it));
  }
  _path.clear();
}
