#include <memory>
#include "Game.h"

int main(int argc, char* argv[])
{
	std::unique_ptr<gust::Game> game = std::make_unique<gust::Game>("Window", 800, 600);
	game->mainLoop();

	return 0;
}