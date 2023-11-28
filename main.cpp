#include "game/Game.h"


int main() {

	Game* _game = nullptr;

	_game = new Game();
	_game->run();
	delete _game;

	return 0;
}