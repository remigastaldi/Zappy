
#ifndef COMMUNICATION_HPP
# define COMMUNICATION_HPP

class   Communication
{
private:
  std::string   cmd;
  std::string   answer;
  int           port;
  std::string   machine;
public:
  void  receive_cmd(std::string);
  std::string   wait_cmd();
};

#endif //COMMUNICATION_HPP
