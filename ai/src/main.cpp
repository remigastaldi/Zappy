//
// main.cpp for Zappy in /home/gastal_r/rendu/Zappy/client/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Wed Jun 21 16:14:06 2017 gastal_r
// Last update Sun Jul  2 17:14:40 2017 gastal_r
//

#include      "Ai.hpp"

int           main(int ac, char *av[])
{
  std::string       host;
  std::string       name;
  int               port;

  if (ac != 7)
  {
    std::cout << "USAGE: ./zappy_ai -p port -n name -h machine" << std::endl;
    std::cout << "\tmachine is the name of the machine; localhost by default" << std::endl;
    std::cout << "\tname is the name of the team" << std::endl;
    std::cout << "\tport is the port number" << std::endl;
    return (0);
  }
  if (check_arg(av) == 1)
    return (0);
  port = checkPort(av);
  name = checkName(av);
  host = checkHost(av);
  try
  {
    Ai   ai(port, name.c_str(), host.c_str());
    ai.start(Ai::State::START);
  }
  catch (const Event::Exit &event)
  {
    std::cout << event.what() << std::endl;
  }
  return (0);
}
