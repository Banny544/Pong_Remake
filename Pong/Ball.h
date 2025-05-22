#pragma once
#include <SDL.h>

class Ball {
private:
    float x, y;
    float w, h;
    float vx, vy;
    SDL_Color color;

public:
    Ball(float width, float height, SDL_Color color);
 

    void update();
    void render(SDL_Renderer* renderer);
   
    int getX() const;
    int getWidth() const;

    void reset();

    void bounceLeft();
    int getY() const;
    int getHeight() const;

    void bounceRight();



};
