#include <iostream>
#include "Renderer.h"
#include "MathUtils.h"
#include "Random.h"
#include "Canvas.h"
#include <ctime>

int main(int, char**) {
    std::cout << "Hello World" << std::endl;
    ray::seedRandom(static_cast<unsigned int>(time(nullptr)));

    ray::Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Ray Tracer", 400, 300);
    ray::Canvas canvas(400, 300, renderer);

    bool quit = false;
    while (!quit) {
        // Process events
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        }

        // Clear the canvas
        canvas.Clear({ 0, 0, 0, 1 });

        // Draw random points to the canvas
        for (int i = 0; i < 1000; i++)
        {
            canvas.DrawPoint({ ray::random(0, 400), ray::random(0, 300) }, { ray::random01(), ray::random01(), ray::random01(), 1 });
        }

        // Update the canvas
        canvas.Update();

        // Use the renderer to present the canvas
        renderer.PresentCanvas(canvas);
    }

    renderer.Shutdown();

    return 0;
}
