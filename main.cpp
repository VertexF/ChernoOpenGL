#include <iostream> 
#include "SDL.h"
#include "GL/glew.h"
#include "IL/il.h"

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	glewInit();
	ilInit();

	std::cout << "Hello world!" << std::endl;

	return 0;
}