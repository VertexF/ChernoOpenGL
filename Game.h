#ifndef GAME_HDR
#define GAME_HDR

#include <string>
#include <array>
#include <memory>
#include "SDL.h"

namespace gust
{

class Shader;

class Game
{
public:
    Game(const std::string& title, int w, int h);
    ~Game();

    void mainLoop();
private:
    void setup();

    void handleEvents();
    void drawGraphics();

    SDL_GLContext _context;
    SDL_Window* _window;
    SDL_Event _input;

    bool _running;
    int _height;
    int _width;
    std::string _title;
    float _ratio;

    std::unique_ptr<Shader> _shader;
};

}

#endif //GAME_HDR