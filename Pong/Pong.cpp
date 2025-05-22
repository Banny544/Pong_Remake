#include <iostream>
#include <windows.h>

#include <SDL.h>
#include <cstdlib>  
#include <ctime>

#include "Board.h"
#include "Ball.h"
#include <array>


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Color White = { 255, 255, 255, 255 };
    Board board(0, 0, 800, 600, White);

   
    Ball ball(10, 10, White);

    ball.reset();

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
        if (board.checkWallCollision(ball.getX(), ball.getWidth())) {
            SDL_Delay(500);  // pause for .5 second after scoring
            ball.reset();     // reset to center

            if (board.getPlayer1Score() > 9) {
                MessageBoxA(nullptr, "Red Team Wins!", "You Win", MB_OK | MB_ICONINFORMATION);
                running = false;
            }
            else if (board.getPlayer2Score() > 9) {
                MessageBoxA(nullptr, "Blue Team Wins!", "You Lose", MB_OK | MB_ICONWARNING);
                running = false;
        }

        }


        SDL_RenderPresent(renderer);
        SDL_Delay(16);  
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}