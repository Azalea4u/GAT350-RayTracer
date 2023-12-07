#include "Renderer.h"
#include "Canvas.h"
#include "Random.h"
#include "Camera.h"
#include "Scene.h"
#include "Material.h"
#include "Sphere.h"
#include "Random.h"
#include "Plane.h"
//#include "Triangle.h"
#include "Mesh.h"

#include <iostream>
#include <SDL.h>
#include <ctime>
#include <glm/gtx/quaternion.hpp>

void InitScene01(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    // create objects -> add to scene
    for (int x = -10; x < 12; x++)
    {
        for (int z = -10; z < 12; z++)
        {
            std::shared_ptr<Material> material;

            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);

            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));
}

void InitScene02(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 2, 10 }, glm::vec3{ 0, 1, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);
    scene.SetCamera(camera);

    //auto triangle = std::make_unique<Triangle>(glm::vec3{ -1, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 2, 0 }, std::make_shared<Lambertian>(color3_t{ 1, 0, 0 }));
    //scene.AddObject(std::move(triangle));

    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, std::make_shared<Lambertian>(color3_t{ 0.2f }));
    scene.AddObject(std::move(plane));

    auto lightMaterial = std::make_shared<Emissive>(color3_t(1.0f, 1.0f, 1.0f), 50.0f);
    auto mesh = std::make_unique<Mesh>(lightMaterial);
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    scene.AddObject(std::move(mesh));
}

//CornellBox
void InitSceneCornellBox(Scene& scene, const Canvas& canvas)
{
    float aspectRatio = canvas.GetSize().x / canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(
        glm::vec3{ 0, 0.5, 4 }, // Position the camera to capture more of the scene
        glm::vec3{ 0, 0, -1 },  // Look towards the center of the scene
        glm::vec3{ 0, 1, 0 },   // Up direction
        40.0f,                  // Field of view
        aspectRatio
    );
    scene.SetCamera(camera);

    // Materials
    auto redMaterial = std::make_shared<Lambertian>(color3_t(0.65f, 0.05f, 0.05f));
    auto greenMaterial = std::make_shared<Lambertian>(color3_t(0.12f, 0.45f, 0.15f));
    auto whiteMaterial = std::make_shared<Lambertian>(color3_t(0.73f, 0.73f, 0.73f));
    auto lightMaterial = std::make_shared<Emissive>(color3_t(1.0f, 1.0f, 1.0f), 50.0f);

    // Walls
    auto leftWall = std::make_unique<Plane>(glm::vec3{ -1.0f, 0.0f, 0.0f }, glm::vec3{ 1.0f, 0.0f, 0.0f }, redMaterial);
    auto rightWall = std::make_unique<Plane>(glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec3{ -1.0f, 0.0f, 0.0f }, greenMaterial);
    auto backWall = std::make_unique<Plane>(glm::vec3{ 0.0f, 0.0f, -1.0f }, glm::vec3{ 0.0f, 0.0f, 1.0f }, whiteMaterial);
    auto floor = std::make_unique<Plane>(glm::vec3{ 0.0f, -0.5f, 0.0f }, glm::vec3{ 0.0f, -1.0f, 0.0f }, whiteMaterial);
    auto ceiling = std::make_unique<Plane>(glm::vec3{ 0.0f, 1.5f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f }, whiteMaterial);

    // Small area light on the ceiling
    auto light = std::make_unique<Mesh>(lightMaterial);
    light->Load("models/quad-1.obj", glm::vec3{ 0, 1.5f, 0.0f }, glm::vec3{ 90, 0, 0 });

    // Objects
    auto sphere = std::make_unique<Sphere>(glm::vec3{ 0.2f, 0.0f, 0.7f }, 0.3f, whiteMaterial);
    auto cube = std::make_unique<Mesh>(whiteMaterial);
    cube->Load("models/cube.obj", glm::vec3{ 0.1f, 0.0f, 0.1f }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0.5f });

    // Adding objects to the scene
    scene.AddObject(std::move(leftWall));
    scene.AddObject(std::move(rightWall));
    scene.AddObject(std::move(backWall));
    scene.AddObject(std::move(floor));
    scene.AddObject(std::move(ceiling));
    scene.AddObject(std::move(light)); // This should be a small rectangle, not the whole ceiling
    scene.AddObject(std::move(sphere));
    scene.AddObject(std::move(cube));
}

int main(int argc, char* argv[])
{
    const int width = 400;
    const int height = 300;
    const int samples = 150;
    const int depth = 15;

    seedRandom(static_cast<unsigned int>(time(nullptr)));

    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", width, height);

    Canvas canvas(width, height, renderer);
    Scene scene(glm::vec3{ 1.0f }, glm::vec3{ 0.5f, 0.7f, 1.0f });

    InitSceneCornellBox(scene, canvas);
      
    /*
    float aspectRatio = canvas.GetSize().x / (float)canvas.GetSize().y;
    std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec3{ 0, 1, 10 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 20.0f, aspectRatio);

    scene.SetCamera(camera);

    //create material
    auto lambertian = std::make_shared<Lambertian>(color3_t{ 0, 0, 1 });
    auto metal = std::make_shared<Metal>(color3_t{ 1, 1, 1 }, 0.0f);
    
    // create objects -> add to scene
    for (int x = -10; x < 10; x++)
    {
        for (int z = -10; z < 10; z++)
        {
            std::shared_ptr<Material> material;
    
            // create random material
            float r = random01();
            if (r < 0.3f)		material = std::make_shared<Lambertian>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }));
            else if (r < 0.6f)	material = std::make_shared<Metal>(color3_t{ random(0.5f, 1.0f) }, random(0, 0.5f));
            else if (r < 0.9f)	material = std::make_shared<Dielectric>(color3_t{ 1.0f }, random(1.1f, 2));
            else				material = std::make_shared<Emissive>(glm::rgbColor(glm::vec3{ random(0, 360), 1.0f, 1.0f }), 5.0f);
    
            // set random sphere radius
            float radius = random(0.2f, 0.3f);
            // create sphere using random radius and material
            auto sphere = std::make_unique<Sphere>(glm::vec3{ x + random(-0.5f, 0.5f), radius, z + random(-0.5f, 0.5f) }, radius, material);
            // add sphere to the scene
            scene.AddObject(std::move(sphere));
        }
    }
    
    auto material = std::make_shared<Lambertian>(color3_t{ 0.2f });
    auto plane = std::make_unique<Plane>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
    scene.AddObject(std::move(plane));

    auto mesh = std::make_unique<Mesh>(std::make_shared<Lambertian>(color3_t{ 0, 0, 1 }));
    mesh->Load("models/cube.obj", glm::vec3{ 0, 0.5f, 0 }, glm::vec3{ 0, 45, 0 });
    scene.AddObject(std::move(mesh));

    */

    //auto triangle = std::make_unique<Triangle>(glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 0, 0 }, glm::vec3{ 0, 1, 0 }, material);
    //scene.AddObject(std::move(triangle));

    // render scene
    canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, samples, depth);
    canvas.Update();

    bool quit = false;
    while (!quit)
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

        renderer.PresentCanvas(canvas);
    }

    // Shutdown renderer
    renderer.Shutdown();

    return 0;
}

