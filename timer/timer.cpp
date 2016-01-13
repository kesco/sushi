#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace ba = boost::asio;
namespace bp = boost::posix_time;
namespace bs = boost::system;

struct Logger
{
public:
  Logger(ba::io_service& io)
    : strand_(io)
    , timer_(io, bp::seconds(1))
    , timer_other_(io, bp::seconds(1))
    , count_(0)
  {
    timer_.async_wait(strand_.wrap(boost::bind(&Logger::log, this)));
    timer_other_.async_wait(strand_.wrap(boost::bind(&Logger::log_other, this)));
  }

  ~Logger()
  {
    std::cout << "Final Count: " << count_ << std::endl;
  }

  void log()
  {
    if (count_ > 5)
      return;
    std::cout << "Timer Count: " << count_ << std::endl;
    count_ = count_ + 1;
    timer_.expires_at(timer_.expires_at() + bp::seconds(1));
    timer_.async_wait(strand_.wrap(boost::bind(&Logger::log, this)));
  }

  void log_other()
  {
    if (count_ > 5)
      return;
    std::cout << "Other Timer Count: " << count_ << std::endl;
    count_ = count_ + 1;
    timer_other_.expires_at(timer_other_.expires_at() + bp::seconds(1));
    timer_other_.async_wait(strand_.wrap(boost::bind(&Logger::log_other, this)));
  }

private:
  ba::io_service::strand strand_;
  ba::deadline_timer timer_;
  ba::deadline_timer timer_other_;
  int count_;
};

int main()
{
  ba::io_service io;
  Logger log(io);
  boost::thread thread(boost::bind(&ba::io_service::run, &io));
  // io.run();
  thread.join();
  return 0;
}
