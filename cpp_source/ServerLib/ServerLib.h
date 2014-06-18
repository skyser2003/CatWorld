#pragma once

#include <unordered_map>
#include <google/protobuf/message.h>

class ServerLib
{
public:
	typedef void (ServerLib::*packetHandler)(::google::protobuf::Message&);
public:
	void Init();
	void Parse(int msg, int length, void* buffer);

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	template <class PKS>
	void RegisterHandler(google::protobuf::Message& pks);
	std::unordered_map<int, packetHandler> handlerList;
};