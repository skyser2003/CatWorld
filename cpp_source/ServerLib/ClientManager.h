#pragma once

class ClientManager
{
public:
	typedef std::unordered_map<std::string, SPtrClient>::iterator iterator;
	typedef std::unordered_map<std::string, SPtrClient>::const_iterator const_iterator;
public:
	ClientManager();
	~ClientManager();

	SPtrClient CreateNewClient(const std::string& uid);
	SPtrClient Get(const std::string& uid);

	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;
	
private:
	std::unordered_map<std::string, SPtrClient> clientList;
};