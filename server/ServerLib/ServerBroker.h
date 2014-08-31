#pragma once

#include "IServerLib.h"

class ServerBroker final : public IServerLib
{
public:
	virtual void Init() override;
	virtual void Destroy() override;

	virtual void Parse(const std::string& uid, int msg, int length, void* buffer) override;

	virtual void SetSendFunction(std::function<void(int, google::protobuf::Message&)> sendFunction) override;
	virtual void SetRootPath(const std::string& rootPath) override;
private:
	std::unique_ptr<IServerLib> serverLib;
};