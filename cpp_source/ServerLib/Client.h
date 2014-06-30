#pragma once

class ServerLib;
class FieldObject;

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

	std::shared_ptr<FieldObject> pc;
};