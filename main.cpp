#include <iostream> 
#include "SDL.h"
#include "GL/glew.h"
#include "IL/il.h"
#include "IL/ilu.h"

namespace 
{

    SDL_GLContext _context;
    SDL_Window* _window;
    SDL_Event _input;

    //title of the window.
    std::string _title;
    float _ratio;

    //Height and width of the screen.
    int _height;
    int _width;

    bool _running;
}

/******************************************************************************/
void setup()
{
    //This sets up what openGL version we are going to use, in this case it's 3.3 that why it say that.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
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

                //Make sure OpenGL 3.3 is supported
                if (!GLEW_VERSION_3_2)
                {
                    printf("OpenGL 3.2 not supported!\n");
                }

                ilInit();
                iluInit();
                ilClearColour(255, 255, 255, 000);

                //Check for error
                ILenum ilError = ilGetError();
                if (ilError != IL_NO_ERROR)
                {
                    std::cerr << "Error initializing DevIL! " << iluErrorString(ilError) << std::endl;
                }
            }
        }
    }
}

void handleEvents()
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

int main(int argc, char* argv[])
{
    setup();
    _running = true;
    _height = 600;
    _width = 800;
    _title = "Window";
    _ratio = (static_cast<float>(_width) / static_cast<float>(_height));
    glClearColor(0.9f, 0.95f, 1.0f, 1.0f);
    glViewport(0, 0, _width, _height);

    while (_running) 
    {
        handleEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(_window);
    }

	return 0;
}