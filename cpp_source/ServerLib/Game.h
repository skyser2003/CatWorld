#pragma once

class Client;
class ClientManager;

class Game
{
public:
	Game();
	~Game();

	template <class PKS>
	void OnPacket(PKS& pks);
private:
	std::unique_ptr<ClientManager> cm;
};