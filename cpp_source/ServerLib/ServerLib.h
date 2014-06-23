#pragma once

#include <unordered_map>
#include <memory>
#include <functional>
#include <google/protobuf/message.h>

class Game;

class ServerLib
{
public:
	ServerLib();
	~ServerLib();

	typedef google::protobuf::Message MSG;
	typedef std::unique_ptr<MSG> UPtrMessage;

	typedef void (ServerLib::*packetHandler)(MSG&);
	typedef UPtrMessage (ServerLib::*packetGenerator)();
public:
	void Init();
	void Destroy();

	void Parse(int msg, int length, void* buffer);
	void Send(MSG& pks);

	void SetSendFunction(std::function<void(int, MSG&)> sendFunction);

	template <class PKS>
	void OnPacket(PKS& pks)
	{
		game->OnPacket(pks);
	}
private:
	template <class PKS>
	void RegisterHandler(MSG& pks);
	template <class PKS>
	UPtrMessage GenerateHandler();

	void CallPacketHandler(int msg);

	// Packet
	std::function<void(int, MSG&)> sendFunction;

	std::unordered_map<int, packetHandler> handlerList;
	std::unordered_map<int, packetGenerator> generatorList;

	std::unordered_map<std::string, int> msgList;

	// Game
	std::unique_ptr<Game> game;
};