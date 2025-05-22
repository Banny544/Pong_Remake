#include <iostream>
#include <SDL.h>
#include <cstdlib>  
#include <ctime>

#include "Board.h"
#include "Ball.h"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color White = { 255, 255, 255, 255 };
    Board board(0, 0, 800, 600, White);

    // Seed random once
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Generate random direction
    float vx = (std::rand() % 2 == 0) ? 4.0f : -4.0f;
    float vy = static_cast<float>((std::rand() % 5) - 2);  


    //spawn ball in the center of the board
    Ball ball(400, 300, 10, 10, vx, vy, White);  

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        ball.update();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        board.render(renderer);
        ball.render(renderer); 

        SDL_RenderPresent(renderer);
        SDL_Delay(16);  
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}