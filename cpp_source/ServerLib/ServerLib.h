#pragma once

#include <unordered_map>
#include <memory>
#include <functional>
#include <google/protobuf/message.h>

class ServerLib
{
public:
	typedef google::protobuf::Message MSG;
	typedef std::unique_ptr<MSG> UPtrMessage;

	typedef void (ServerLib::*packetHandler)(MSG&);
	typedef UPtrMessage (ServerLib::*packetGenerator)();
public:
	void Init();
	void Parse(int msg, int length, void* buffer);
	void Send(MSG& pks);

	void SetSendFunction(std::function<void(MSG&)> sendFunction);

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	template <class PKS>
	void RegisterHandler(MSG& pks);
	template <class PKS>
	UPtrMessage GenerateHandler();

	void CallPacketHandler(int msg);

	std::function<void(MSG&)> sendFunction;

	std::unordered_map<int, packetHandler> handlerList;
	std::unordered_map<int, packetGenerator> generatorList;
};