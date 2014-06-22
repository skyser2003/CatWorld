#pragma once

class Game
{
public:
	Game();
	~Game();

	template <class PKS>
	void OnPacket(PKS& pks);

private:

};