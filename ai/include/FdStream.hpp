//
// FdStream.hpp for Zappy in /home/gastal_r/rendu/Zappy/ai/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Tue Jun 27 15:28:46 2017 gastal_r
// Last update Tue Jun 27 16:10:33 2017 gastal_r
//

#ifndef       _FSTREAM_HPP_
#define       _FSTREAM_HPP_

#include      <iostream>
#include      <ext/stdio_filebuf.h>
#include      <memory>

class FdStream
{
public:
  explicit FdStream(int fd)
    : _inFileBuff(new __gnu_cxx::stdio_filebuf<char>(fd, std::ios::in)),
    _ouFileBuff(new __gnu_cxx::stdio_filebuf<char>(fd, std::ios::out)),
    _inStream(new std::istream(_inFileBuff.get())),
    _outStream(new std::ostream(_ouFileBuff.get()))
    {};

  std::istream *getInputStreamPtr(void) { return (_inStream.get()); };
  std::ostream *getOutputStreamPtr(void) { return (_outStream.get()); };

  void  operator<<(const std::string &str)
  {
    *_outStream << str << std::endl;
  }

  void operator>>(std::string &str)
  {
    std::getline(*_inStream, str, '\n');
  }

private:
  std::unique_ptr<__gnu_cxx::stdio_filebuf<char>> _inFileBuff;
  std::unique_ptr<__gnu_cxx::stdio_filebuf<char>> _ouFileBuff;

  std::unique_ptr<std::istream> _inStream;
  std::unique_ptr<std::ostream> _outStream;
};

#endif /* end of include guard: _FSTREAM_HPP_ */
