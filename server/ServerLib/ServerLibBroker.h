#pragma once

class ServerLib;

class ServerLibBroker
{
public:
	ServerLibBroker();
	~ServerLibBroker();

	void Init();
	void Destroy();

	void Parse(const std::string& uid, int msg, int length, void* buffer);

	void SetSendFunction(std::function<void(int, google::protobuf::Message&)> sendFunction);
	void SetRootPath(const std::string& rootPath);

private:
	std::unique_ptr<ServerLib> serverLib;
};