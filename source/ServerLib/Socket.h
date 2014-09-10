#pragma once

class Socket
{
public:
	void Init(boost::asio::io_service service);
	void Send();
	void HandleWrite(const boost::system::error_code& error, size_t bytesTransferred);

	boost::asio::ip::tcp::socket& GetSocket() const;
private:
	std::unique_ptr<boost::asio::ip::tcp::socket> socket;
	std::string message;
};

class SServer
{
public:
	void Init(int port);
	void StartAccept();

	void HandleAccept(const boost::system::error_code& error);
private:
	boost::asio::io_service service;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;

	Socket socket;
};