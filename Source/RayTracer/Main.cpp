#include <iostream>
#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Random.h"
#include <SDL.h>
#include <ctime>

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;

    seedRandom(static_cast<unsigned int>(time(nullptr)));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("SDL Window", 1200, 900);

    Canvas canvas(1200, 900, renderer);

    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

    Scene scene; // sky color could be set with the top and bottom color
    scene.SetCamera(camera);

    // create Material
    auto material = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });

    // create objects -> add to scene
    for (int i = 0; i < 15; ++i)
    {
        // randomize position and radius
        auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1)}, random(0.1f, 0.5f), material);
        scene.AddObject(std::move(sphere));
    }

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

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    }
                    break;
            }
            break;
        }
      
        // render scene
        canvas.Clear({ 0, 0, 0, 1 });   
        scene.Render(canvas);
        canvas.Update();

        renderer.PresentCanvas(canvas);
    }

    // Shutdown renderer
    renderer.Shutdown();

    return 0;
}
