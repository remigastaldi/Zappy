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
#include      "Utils.hpp"

Ai::Ai(int port, const std::string &teamName, const std::string &machine) noexcept
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
  _currentLevel(1),
  _eventCase(1)
{
  _eggEclosion = [&] (void) { this->eggEclosion(); };
}

Ai::~Ai()
{
  for (auto & it : _threads)
  {
    std::cout << "WAIT THREAD" << std::endl;
    it.join();
  }
  std::cout << "EXIT THREAD" << std::endl;
}

void      Ai::start(Ai::State state)
{
  try
  {
    switch (state)
    {
    case Ai::State::START:
      // take_all_food();
      primaryState();
      break;
    case Ai::State::INCANTATION:
      startIncantation();
      primaryState();
      break;
    case Ai::State::WALK_TO_BROADCASTER:
      walkToBroadcaster(_eventCase);
      primaryState();
      break;
    // case Ai::State::EGG_ECLOSION:
    //   eggEclosion();
    //   primaryState();
    }
  }
  catch (const Event::Dead &event)
  {
    std::cout << "[" << _fd << "] " << "Player " <<  _fd << " die" << std::endl;
  }
  catch (const Event::Ko &event)
  {
    std::cout << "[" << _fd << "] " << "Server return KO " << std::endl;
    start(Ai::State::START);
  }
  catch (const Event::GameOver &event)
  {
    std::cout << "[" << _fd << "] " << "Team : " << event.getTeamName() << " won"<< std::endl;
  }
  catch (const Event::Broadcast &event)
  {
    std::cout << "[" << _fd << "] " << "Broadcast : " << event.getCase() << std::endl;
    _eventCase = event.getCase();
    if (event.getCase() == 0)
    {
      start(Ai::State::INCANTATION);
    }
    else
      start(Ai::State::WALK_TO_BROADCASTER);
  }
  catch (const Event::DeadBroadcaster &event)
  {
    start(Ai::State::START);
  }
  // catch (const Event::Egg &event)
  // {
  //   start(Ai::State::EGG_ECLOSION);
  // }
}

void      Ai::take_all_food(void)
{
  for (int checkRotation = 0;  checkRotation < 3; ++checkRotation)
  {
    actualiseView();
    if (lookForFood())
      return;
    sendCommand("Right");
  }
  for (size_t i = 0; i < _currentLevel; ++i)
    _path.push_back(Ai::Direction::FORWARD);
  walkToDir();
  // return (take_all_food());
}

void      Ai::primaryState(void)
{
  actualiseInventory();
  if (_currentItems[Ai::Properties::FOOD] < 6)
  {
    take_all_food();
    return (primaryState());
  }
  else if (checkIfNeedResources())
  {
    for (int checkRotation = 0;  checkRotation < 3; ++checkRotation)
    {
      actualiseView();
      if (lookForResources())
        return (primaryState());
      // else if (lookForFood())
      //   return (primaryState());
      sendCommand("Right");
    }
    for (size_t i = 0; i < _currentLevel; ++i)
      _path.push_back(Ai::Direction::FORWARD);
    walkToDir();
    return (primaryState());
  }
  else
  {
    actualiseView();
    powerupState();
    return (primaryState());
  }
}

void      Ai::powerupState(void)
{
  if (countPlayer() == 0)
  {
    sendCommand("Connect_nbr");
    if (std::stoi(_answer) > 0)
      forkPlayer();
  }
  while (countPlayer() < _riseUpConditions[_currentLevel][Ai::Properties::NB_PLAYER])
  {
    sendCommand("Broadcast");
    actualiseInventory();
    if (_currentItems[Ai::Properties::FOOD] < 6)
      take_all_food();
    actualiseView();
  }
  startIncantation();
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

void      Ai::actualiseInventory(void)
{
  sendCommand("Inventory");

  size_t posCase = 0;
  std::string item;
  size_t posItem;
  while ((posCase = _answer.find(",")) != std::string::npos)
  {
    item = _answer.substr(0, posCase);
    posItem = item.find(" ");
    std::string itemName(item.substr(0, posItem));
    item.erase(0, posItem + 1);
    std::cout << "[" << _fd << "] " << itemName << " " << item << std::endl;
    _currentItems[Utils::stringToEnum(itemName)] = std::stoi(item);
    _answer.erase(0, posCase + 2);
  }
  posItem = _answer.find(" ");
  std::string itemName(_answer.substr(0, posItem));
  _answer.erase(0, posItem + 1);
  std::cout << "[" << _fd << "] " << itemName << " " << _answer << std::endl;
  _currentItems[Utils::stringToEnum(itemName)] = std::stoi(_answer);
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

void    Ai::actualiseView(void)
{
  sendCommand("Look");

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

bool    Ai::lookForFood(void)
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
    sendCommand("Take " + Utils::enumToString(_objectToTake));
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

bool      Ai::lookForResources(void)
{
  size_t caseNbr = 0;
  for (const auto & caseIt : _view)
  {
    std::cout << "[" << _fd << "] " << "[" << caseNbr++ << "]";
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

  std::cout << "[" << _fd << "] " << "ressourceCase => " << resourceCase << std::endl;
  while (currentCase != resourceCase)
  {
    curMinOffsetX = offsetY * offsetY;
    curMaxOffsetX = curMinOffsetX + offsetY * 2;
    // std::cout << "[" << _fd << "] " << "curMinOffsetX: " << curMinOffsetX << std::endl;
    // std::cout << "[" << _fd << "] " << "curMaxOffsetX: " << curMaxOffsetX << std::endl;
    nextLineOffset = ((offsetY + 1) * (offsetY + 1)) + (offsetY > 0 ? offsetX + 1 : offsetX);
    std::cout << "[" << _fd << "] " << "currentCase: " << currentCase << std::endl;
    int direction = calculateDirection(resourceCase, (currentCase - 1 < curMinOffsetX ? currentCase : currentCase - 1), nextLineOffset,
      (currentCase + 1 > curMaxOffsetX ? currentCase : currentCase + 1));
    std::cout << "[" << _fd << "] " << "direction=> " << direction << std::endl;
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
      (curDirection == Ai::Direction::LEFT ? _path.push_back(Ai::Direction::RIGHT) : (void)0);
      (curDirection == Ai::Direction::RIGHT ? _path.push_back(Ai::Direction::LEFT) : (void)0);
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
  // std::cout << "[" << _fd << "] " << "a: " << a << "  b: " << b << "  c: " << c << std::endl;
  // std::cout << "[" << _fd << "] " << "aLength: " << aLength << "  bLength: " << bLength << "  cLength: " << cLength << std::endl;
  return ((aLength < bLength && aLength < cLength ? 0 : (bLength < aLength && bLength < cLength ? 1 : 2)));
}

void    Ai::walkToBroadcaster(int caseId)
{
std::cout << "CASE: " << caseId << std::endl;
_path.clear();
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

void    Ai::walkToDir(void)
{
  for (const auto & it : _path)
  {
    sendCommand(Utils::enumToString(it));
  }
  _path.clear();
}

void    Ai::startIncantation(void)
{
  sendCommand("Incantation");
  std::cout << "[" << _fd << "] " << _answer << std::endl;
  receiveCommand();
  std::cout << "[" << _fd << "] " << _answer << std::endl;
  _currentLevel++;
}

void    Ai::forkPlayer(void)
{
  sendCommand("Fork");
}

void    Ai::eggEclosion(void)
{
  _threads.push_back(std::thread([&]
  {
    try
    {
      std::unique_ptr<Ai> ai(new Ai(_port, _teamName, _machine));
      ai->start(Ai::State::START);
    }
    catch (const Event::Exit &event)
    {
      std::cout << event.what() << std::endl;
    }
  }));
}
