#pragma once

class IServerLib
{
public:
	virtual void Init() = 0;
	virtual void Destroy() = 0;

	virtual void Parse(const std::string& uid, int msg, int length, void* buffer) = 0;
	
	virtual void SetSendFunction(std::function<void(int, google::protobuf::Message&)> sendFunction) = 0;
	virtual void SetRootPath(const std::string& rootPath) = 0;
};