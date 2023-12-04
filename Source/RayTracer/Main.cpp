#include <iostream>
#include "Renderer.h"
#include "MathUtils.h"
#include "Random.h"
#include "Canvas.h"
#include "Scene.h"
#include "Camera.h"
#include "Sphere.h"
#include "Object.h"
#include "Material.h"
#include <ctime>

int main(int, char**) {
    std::cout << "Hello World" << std::endl;
    ray::seedRandom(static_cast<unsigned int>(time(nullptr)));

    ray::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 400, 300);
    ray::Canvas canvas(400, 300, renderer);

    // Create camera and scene outside the main loop
    float aspectRatio = canvas.GetSize().x / static_cast<float>(canvas.GetSize().y);
    std::shared_ptr<ray::Camera> camera = std::make_shared<ray::Camera>(
        glm::vec3{ 0, 0, 1 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 }, 70.0f, aspectRatio
    );


    ray::Scene scene(20);
    scene.SetCamera(camera);

    //auto material = std::make_shared<ray::Lambertian>(ray::color3_t{ 1, 0, 0 });
    auto lambertian = std::make_shared<ray::Lambertian>(ray::color3_t{ 0, 0, 1 });
    auto metal = std::make_shared<ray::Metal>(ray::color3_t{ 1, 1, 1 }, 0.0f);

    // create objects -> add to scene
    for (int i = 0; i < 10; i++)
    {
        std::shared_ptr<ray::Material> material = (std::rand() % 2 == 0) ? std::dynamic_pointer_cast<ray::Material>(lambertian) : std::dynamic_pointer_cast<ray::Material>(metal);
        auto sphere = std::make_unique<ray::Sphere>(
            glm::vec3{ ray::random(-5, 5), ray::random(-5, 5), ray::random(-10, -5) },
            ray::random(0.5, 0.8),
            material
        );
        scene.AddObject(std::move(sphere));
    }

    canvas.Clear({ 0, 0, 0, 1 });
    scene.Render(canvas, 50);
    canvas.Update();

    bool quit = false;
    while (!quit) {
        // Process events
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
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

    renderer.Shutdown();

    return 0;
}
