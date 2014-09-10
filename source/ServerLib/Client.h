#pragma once

class ServerLib;
class FieldObject;

class Client
{
public:
	static const int PositionPacketCooltime = 100;
public:
	Client();
	~Client();

	void Init(ServerLib* game, std::string id, std::string pw);
	void Send(int msg, google::protobuf::Message& pks);

	void SetPC(SPtrObj& pc) { this->pc = pc; }
	SPtrObj GetPC() const { return pc; }

	void SendMapEnterPacket();
	void Update(int dt);

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	ServerLib* server;

	std::string id;
	std::string pw;

	SPtrObj pc;

	int positionCooltime;

};