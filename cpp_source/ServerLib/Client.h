#pragma once

class ServerLib;

class Client
{
public:
	Client();
	~Client();

	void Init(ServerLib* game, std::string id, std::string pw);
	void Send(int msg, google::protobuf::Message& pks);

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	ServerLib* server;

	std::string id;
	std::string pw;
};