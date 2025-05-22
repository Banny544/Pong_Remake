#include <iostream>
#include <windows.h>

#include <SDL.h>
#include <cstdlib>  
#include <ctime>

#include "Board.h"
#include "Ball.h"
#include <array>

#include "Paddle.h"


int main(int argc, char* argv[]) {
    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Create game window and renderer
    SDL_Window* window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    // Set up game objects
    SDL_Color White = { 255, 255, 255, 255 };
    Board board(0, 0, 800, 600, White);

    // Initialize ball
    Ball ball(10, 10, White);
    ball.reset();

    bool running = true;
    SDL_Event e;

    // Create red paddle (right side, player-controlled)
    Paddle rightPaddle(780, 250, 10, 100, 5, White);  // red paddle on the right

    // Create blue paddle (left side, AI-controlled)
    Paddle leftPaddle(10, 250, 10, 100, 3, White); // blue paddle on the lefft

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;

        }

        // Player input (arrow keys control right paddle)
        const Uint8* keystates = SDL_GetKeyboardState(NULL);
        if (keystates[SDL_SCANCODE_UP])
            rightPaddle.moveUp();
        if (keystates[SDL_SCANCODE_DOWN])
            rightPaddle.moveDown(600); // 600 = window height

        // Update ball position
        ball.update();

        // AI for left (blue) paddle: follow ball vertically
        int ballCenterY = ball.getY() + ball.getHeight() / 2;
        int paddleCenterY = leftPaddle.getRect().y + leftPaddle.getRect().h / 2;

        if (ballCenterY < paddleCenterY)
            leftPaddle.moveUp();
        else if (ballCenterY > paddleCenterY)
            leftPaddle.moveDown(600); // 600 = window height

        // Get SDL_Rects for collision detection
        SDL_Rect ballRect = { ball.getX(), ball.getY(), ball.getWidth(), ball.getHeight() };
        SDL_Rect paddleRect = rightPaddle.getRect();
        SDL_Rect leftPaddleRect = leftPaddle.getRect();

        // Collision: Ball hits right paddle ? bounce left
        if (SDL_HasIntersection(&ballRect, &paddleRect)) {
            ball.bounceLeft();
        }

        // Collision: Ball hits left paddle ? bounce right
        if (SDL_HasIntersection(&ballRect, &leftPaddleRect)) {
            ball.bounceRight();  
        }

        // Clear screen (black)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw all game objects
        board.render(renderer);
        rightPaddle.render(renderer);
        leftPaddle.render(renderer);
        ball.render(renderer); 

        

        if (board.checkWallCollision(ball.getX(), ball.getWidth())) {
            SDL_Delay(500);  // pause for .5 second after scoring
            ball.reset();     // reset to center

            // End game if someone reaches score 10
            if (board.getPlayer2Score() > 9) {
                MessageBoxA(nullptr, "Red Team Wins!", "You Win", MB_OK | MB_ICONINFORMATION);
                running = false;
            }
            else if (board.getPlayer1Score() > 9) {
                MessageBoxA(nullptr, "Blue Team Wins!", "You Lose", MB_OK | MB_ICONWARNING);
                running = false;
            }
    
        }

        // Present rendered frame
        SDL_RenderPresent(renderer);

        // Frame delay for ~60 FPS
        SDL_Delay(16);  
    }

    // Cleanup SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}