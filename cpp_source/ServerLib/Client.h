#pragma once

class Client
{
public:
	void Init(std::string id, std::string pw);
private:
	std::string id;
	std::string pw;
};