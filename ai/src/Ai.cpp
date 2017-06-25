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
  _currentItems({ {Ai::Properties::LINEMATE, 0}, {Ai::Properties::DERAUMERE, 0}, {Ai::Properties::SIBUR, 0}, {Ai::Properties::MENDIANE, 0}, {Ai::Properties::PHIRAS, 0}, {Ai::Properties::THYSTAME, 0} }),
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
  }
  catch (const Event::GameOver &event)
  {
    std::cout << "Team : " << event.getTeamName() << std::endl;
  }
  catch (const Event::Broadcast &event)
  {
    std::cout << "EVENT " << event.getCase() << std::endl;
  }
}

const std::string &Ai::checkIfEventMessage(std::string &message)
{
  if (message.find("dead") != std::string::npos)
    throw Event::Dead();
  else if (message.find("ko") != std::string::npos)
    throw Event::Ko();
  else if (message.find("game over") != std::string::npos)
  {
    message.erase(0, message.find("game over") + 9);
    throw Event::GameOver(message);
  }
  else if (message.find("message") != std::string::npos)
  {
    if ((size_t)message.at(message.find_first_of("12345678")) == _currentLevel)
      throw Event::Broadcast((size_t)message.at(message.find_last_of("12345678")) == _currentLevel);
  }
  return (message);
}


void      Ai::primaryState(void) noexcept
{
  if (checkIfNeedResources())
  {
    for (int checkRotation = 0;  checkRotation < 3; ++checkRotation)
    {
      if (lookForResources())
        return (primaryState());
      //TODO send 90° rotation to server
    }
    //TODO send forward to server
    primaryState();
  }
  else
  {
    powerupState();
  }
}

void      Ai::powerupStateFirstCheck(void) noexcept
{
  if (countPlayer() < _riseUpConditions[_currentLevel][Ai::Properties::NB_PLAYER])
  {
    //TODO fork player
    powerupState();
  }
  else
    startIncantation();
}

void      Ai::powerupState(void) noexcept
{
  if (countPlayer() < _riseUpConditions[_currentLevel][Ai::Properties::NB_PLAYER])
  {
    //TODO launch broadcast
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    powerupState();
  }
  else
    startIncantation();
}

void      Ai::startIncantation(void) noexcept
{

}

size_t    Ai::countPlayer(void) noexcept
{
  size_t nb = 0;
  std::vector<std::vector<Ai::Properties>> view(getLookView());

  for (auto & it : view.at(0))
  {
    if (it == Ai::Properties::NB_PLAYER)
      nb++;
  }
  return (nb);
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

const std::vector<std::vector<Ai::Properties>> Ai::getLookView(void) noexcept
{
  //TODO get look result from server
  std::string rawView("player,,,thystame,,food,,,,,,linemate,,,,,");

  std::vector<std::vector<Ai::Properties>>  view;

  size_t posCase = 0;
  std::string currentCase;
  while ((posCase = rawView.find(",")) != std::string::npos)
  {
    currentCase = rawView.substr(0, posCase);
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
    view.push_back(caseItems);
    rawView.erase(0, posCase + 1);
  }
  return (view);
}

bool      Ai::lookForResources(void) noexcept
{
  std::vector<std::vector<Ai::Properties>>  view(getLookView());

  size_t caseNbr(0);
  std::cout << "Look command result: " << std::endl;
  for (auto & it : view)
  {
    std::cout << "[" << caseNbr++ << "]";
    for (auto & it2 : it)
    {
      std::cout << " " << (int) it2 << " ";
    }
    std::cout << std::endl;
  }
  int resourceCase = findNeededResourceCase(view);
  if (resourceCase == -1)
    return (false);
  else if (resourceCase == 0)
  {
    //TODO send request to take object to server
  }
  else
  {
    calculatePath(resourceCase);
    walkToResource();
    return (lookForResources());
  }
  return (true);
}

int      Ai::findNeededResourceCase(const std::vector<std::vector<Ai::Properties>>  &view) noexcept
{
  size_t caseNbr = 0;
  for (auto & currentCase : view)
  {
    for (auto & currentItem : currentCase)
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
  _path.clear();
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

void    Ai::walkToResource(void) noexcept
{
  for (auto & it : _path)
  {
    //TODO send to server
    (void)it;
  }
}
