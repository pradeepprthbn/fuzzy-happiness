#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#define max_length 1024

using boost::asio::ip::tcp;

class server
{
public:
  server(boost::asio::io_context& , short );

private:
  void do_accept();

  tcp::acceptor acceptor_;
};

class session
  : public std::enable_shared_from_this<session>
{
public:
  session(tcp::socket );
  void start();

private:
  void do_read();
  void do_write(std::size_t);
  void do_calculate();
  
  tcp::socket socket_;
  char data_[max_length];
  uint32_t sum;

};


