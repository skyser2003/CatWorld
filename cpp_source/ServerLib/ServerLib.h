#pragma once

#include <unordered_map>
#include <memory>
#include <google/protobuf/message.h>

class ServerLib
{
public:
	typedef std::unique_ptr<google::protobuf::Message> UPtrMessage;

	typedef void (ServerLib::*packetHandler)(google::protobuf::Message&);
	typedef UPtrMessage (ServerLib::*packetGenerator)();
public:
	void Init();
	void Parse(int msg, int length, void* buffer);

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	template <class PKS>
	void RegisterHandler(google::protobuf::Message& pks);
	template <class PKS>
	UPtrMessage GenerateHandler();

	void CallPacketHandler(int msg);

	std::unordered_map<int, packetHandler> handlerList;
	std::unordered_map<int, packetGenerator> generatorList;
};