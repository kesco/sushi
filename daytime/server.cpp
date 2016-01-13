#include <ctime>
#include <cstdint>
#include <iostream>
#include <string>
#include <memory>
#include <functional>
#include <boost/asio.hpp>

namespace ba = boost::asio;
namespace bs = boost::system;

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std;
  time_t now = time(nullptr);
  return ctime(&now);
}

struct connection
  : std::enable_shared_from_this<connection>
{
public:
  typedef std::shared_ptr<connection> pointer;
  static pointer create(ba::io_service& io_service)
  {
    return pointer(new connection(io_service));
  }

  void start()
  {
    message_ = make_daytime_string();
    ba::async_write(socket_, ba::buffer(message_),
                    std::bind(&connection::handle_write, shared_from_this(),
                              std::placeholders::_1, std::placeholders::_2));
  }

  tcp::socket& socket()
  {
    return socket_;
  }
private:
  connection(ba::io_service& io_service): socket_(io_service)
  {
  }

  void handle_write(const boost::system::error_code&, size_t)
  {
  }

  tcp::socket socket_;
  std::string message_;
};

struct server
{
public:
  server(ba::io_service& io_service)
    : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8000))
  {
    start_accept();
  }
private:
  void start_accept()
  {
    connection::pointer conn = connection::create(acceptor_.get_io_service());
    acceptor_.async_accept(conn->socket(),
                           std::bind(&server::handle_accept, this, conn, std::placeholders::_1));
  }

  void handle_accept(connection::pointer conn, const boost::system::error_code& error)
  {
    if (!error) conn->start();
    start_accept();
  }

  tcp::acceptor acceptor_;
};


int main()
{
  try
  {
    ba::io_service io_service;
    server server(io_service);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
