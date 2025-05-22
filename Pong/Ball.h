#pragma once
#include <SDL.h>

class Ball {
private:
    float x, y;
    float w, h;
    float vx, vy;
    SDL_Color color;

public:
    Ball(float startX, float startY, float width, float height, float velX, float velY, SDL_Color color);
    void update();
    void render(SDL_Renderer* renderer);
};
