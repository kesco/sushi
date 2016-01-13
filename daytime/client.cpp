#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

namespace ba = boost::asio;

int main()
{
  using boost::asio::ip::tcp;
  ba::io_service io_service;
  tcp::resolver resolver(io_service);
  tcp::resolver::query query("127.0.0.1", "8000");
  tcp::resolver::iterator iter = resolver.resolve(query);
  tcp::socket socket(io_service);
  ba::connect(socket, iter);

  for (;;)
  {
    boost::array<char, 128> buf;
    boost::system::error_code error;

    size_t len = socket.read_some(ba::buffer(buf), error);
    if (error == ba::error::eof) 
    {
      break;
    } 
    std::cout.write(buf.data(), len);
  }
  return 0;
}
