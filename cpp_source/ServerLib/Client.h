#pragma once

class Client
{
public:
	Client();
	~Client();

	void Init(std::string id, std::string pw);
private:
	std::string id;
	std::string pw;
};