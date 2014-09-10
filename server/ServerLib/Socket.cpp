#include "stdafx.h"
#include "Socket.h"

using boost::asio::ip::tcp;

void Socket::Init(boost::asio::io_service service)
{
	socket.reset(new tcp::socket(service));
}

void Socket::Send()
{
	boost::asio::async_write(*socket, boost::asio::buffer(message),
		boost::bind(&Socket::HandleWrite, this,
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void Socket::HandleWrite(const boost::system::error_code& error, size_t bytesTransferred)
{
}

boost::asio::ip::tcp::socket& Socket::GetSocket() const
{
	return *socket.get();
}

void SServer::Init(int port)
{
	acceptor.reset(new tcp::acceptor(service, tcp::endpoint(tcp::v4(), port)));
}

void SServer::StartAccept()
{
	acceptor->async_accept(socket.GetSocket(),
		boost::bind(&SServer::HandleAccept, this, boost::asio::placeholders::error));
}

void SServer::HandleAccept(const boost::system::error_code& error)
{

}