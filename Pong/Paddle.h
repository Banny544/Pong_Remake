#pragma once
#include <SDL.h>

class Paddle {
private:
    int x, y;
    int w, h;
    int speed;
    SDL_Color color;

public:
    Paddle(int x, int y, int w, int h, int speed, SDL_Color color);
    void moveUp();
    void moveDown(int windowHeight);
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
};
