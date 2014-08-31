#pragma once

class Socket
{
public:

private:
	boost::asio::io_service service;
	boost::asio::ip::tcp::acceptor acceptor;
};