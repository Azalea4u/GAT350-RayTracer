#include <iostream>
#include <SDL.h>
#include "Renderer.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("SDL Window", 400, 300);

    bool quit = false;
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            SDL_Event event;
            SDL_PollEvent(&event);
            switch (event.type)
            {
                case SDL_QUIT:
					quit = true;
					break;
            }
        }
    }

    // Shutdown renderer
    renderer.Shutdown();

    return 0;
}
