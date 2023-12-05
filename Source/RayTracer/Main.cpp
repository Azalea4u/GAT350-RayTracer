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
    renderer.CreateWindow("SDL Window", 800, 600);

    Canvas canvas(400, 300, renderer);

    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio);

    Scene scene; // sky color could be set with the top and bottom color
    scene.SetCamera(camera);

    // create Material
    // create material
    auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);

    // create objects -> add to scene
    for (int i = 0; i < 10; i++)
    {
        std::shared_ptr<Material> material = (rand() % 2 == 0) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
            //<use rand() and %to randomly pick the material>) ? std::dynamic_pointer_cast<Material>(lambertian) : std::dynamic_pointer_cast<Material>(metal);
        auto sphere = std::make_unique<Sphere>(glm::vec3{ random(-1, 1), random(-1, 1), random(-1, 1) }, random(0.1f, 0.5f), material);
        //<create the sphere with the material>;
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
        scene.Render(canvas, 50);
        canvas.Update();

        renderer.PresentCanvas(canvas);
    }

    // Shutdown renderer
    renderer.Shutdown();

    return 0;
}
