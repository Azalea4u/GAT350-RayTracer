#include <iostream>
#include <SDL.h>
#include "Renderer.h"
#include "Random.h"
#include <ctime>
#include "Random.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;

    seedRandom(static_cast<unsigned int>(time(nullptr)));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("SDL Window", 400, 300);

    Canvas canvas(400, 300, renderer);

    bool quit = false;
    while (!quit)
    {
        canvas.Clear({ 0, 0, 0, 1 });
        for (int i = 0; i < 100; ++i)
        {
            canvas.DrawPoint({ random(0, 400), random(0, 300) }, { random(0, 255), random(0, 255), random(0, 255), 1 });
        }
        canvas.Update();

        renderer.PresentCanvas(canvas);

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
