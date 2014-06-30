#pragma once

class Client
{
public:
	Client();
	~Client();

	void Init(std::string id, std::string pw);

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	std::string id;
	std::string pw;
};