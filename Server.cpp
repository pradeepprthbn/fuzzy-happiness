#include "Server.h"

session::session(tcp::socket socket) :
  socket_(std::move(socket))
{
}

server::server(boost::asio::io_context & io_context, short port) :
  acceptor_(io_context, tcp::endpoint(tcp::v4(), port))
{
  do_accept();
}

void session::start()
{
  do_read();
}

void session::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
    [this, self](boost::system::error_code ec, std::size_t length)
  {
    if (!ec)
    {
      do_calculate();
    }
  });
}

void session::do_write(std::size_t length)
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
    [this, self](boost::system::error_code ec, std::size_t /*length*/)
  {
    if (!ec)
    {
      do_read();
    }
  });
}

void session::do_calculate()
{

  std::string buffer = data_;
  buffer.pop_back();

  uint32_t value = UINT32_MAX;

  std::string reply;
  char sstring[50] = "Number received and the Max value";
  char number[10];

  sprintf(number, "%u", value);
  reply = strcat(sstring, number);

  uint32_t numberToCheck = boost::lexical_cast<uint32_t>(buffer);

  if (numberToCheck % 2 == 0)
  {
    sum = sum + numberToCheck;
    std::cout << "Number received is even and value" << " : " << sum << "\n";
  }
  else
  {
    sum = sum - numberToCheck;
    std::cout << "Number received is odd and value" << " : " << sum << "\n";
  }

  if (sum < UINT32_MAX)
  {
    do_write(max_length);
  }
  else
  {
    socket_.close();
  }
}

void server::do_accept()
{
  acceptor_.async_accept(
    [this](boost::system::error_code ec, tcp::socket socket)
  {
    if (!ec)
    {
      std::make_shared<session>(std::move(socket))->start();
    }

    do_accept();
  });
}



int main(int argc, char* argv[])
{
  try
  {

    boost::asio::io_context io_context;

    server s(io_context, 1234);

    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
