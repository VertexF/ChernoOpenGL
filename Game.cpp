#include "Game.h"
#include <iostream> 
#include "GL/glew.h"
#include "IL/il.h"
#include "IL/ilu.h"


namespace gust
{
/******************************************************************************/
Game::Game(const std::string &title, int w, int h) : _running(true), 
_width(w), _height(h), _title(title), 
_ratio(static_cast<float>(_width) / static_cast<float>(_height)), 
_position{ -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f, }, 
    _buffer(0)
{
    setup();
}

/******************************************************************************/
Game::~Game()
{
}

/******************************************************************************/
//! @brief Sets up everything needed to render graphics.
void Game::setup() 
{
    //Sets up OpenGL to make it use the core profile.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "SDL failed to start" << std::endl;
    }
    else
    {
        //What these function do is set up the Attributes we are going to be working with.
        //There are default values to all these SDL_GL_ function.
        //This function works by taking in a attribute and then setting up the totally number of bits it will be using
        SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
        SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (_window == nullptr)
        {
            std::cerr << "Window could not be started for some reason" << std::endl;
        }
        else
        {
            //This is how we start up the render.
            _context = SDL_GL_CreateContext(_window);
            if (_context == nullptr)
            {
                std::cerr << "Context could not be started for some reason" << std::endl;
            }
            else
            {
                //This is the vsync to stop the ripped animations.
                if (SDL_GL_SetSwapInterval(1) < 0)
                {
                    std::cerr << "Warning: Unable to set VSync!" << std::endl;
                }

                //Here we are starting up glew.
                glewExperimental = GL_TRUE;
                GLenum error = glewInit();
                if (GLEW_OK != error)
                {
                    std::cerr << stderr << "You are have glew error :(" << std::endl;
                }

                //Checking version of OpenGL we can use.
                std::cout << glGetString(GL_VERSION) << std::endl;

                ilInit();
                iluInit();
                ilClearColour(255, 255, 255, 000);

                //Check for error
                ILenum ilError = ilGetError();
                if (ilError != IL_NO_ERROR)
                {
                    std::cerr << "Error initializing DevIL! " << iluErrorString(ilError) << std::endl;
                }

                glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
                glViewport(0, 0, _width, _height);
            }
        }
    }
}

/******************************************************************************/
//! @brief setups the state of OpenGL for rendering.
void Game::openGLSetUp() 
{
    glGenBuffers(1, &_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, _buffer);
    glBufferData(GL_ARRAY_BUFFER, _position.size() * sizeof(float), _position.data(), GL_STATIC_DRAW);
}

/******************************************************************************/
//! @brief handles events for our renderer in the main loop.
void Game::handleEvents() 
{
    while (SDL_PollEvent(&_input))
    {
        switch (_input.type)
        {
        case SDL_QUIT:
            _running = false;
            break;
        };
    }
}

/******************************************************************************/
//! @brief draws graphics in the main loop.
void Game::drawGraphics()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    SDL_GL_SwapWindow(_window);
}


/******************************************************************************/
//! @brief the main loop of the program.
void Game::mainLoop() 
{
    while (_running) 
    {
        handleEvents();
        drawGraphics();
    }
}

};