#include "Ball.h"
#include <cstdlib>
#include <ctime>

void Ball::reset() {
    // Reset to center
    x = 400 - w / 2;
    y = 300 - h / 2;

    // Randomize direction
    vx = (std::rand() % 2 == 0) ? 4.0f : -4.0f;
    vy = static_cast<float>((std::rand() % 5) - 2);  // -2 to +2
}

int Ball::getX() const { return static_cast<int>(x); }
int Ball::getWidth() const { return static_cast<int>(w); }


Ball::Ball(float width, float height, SDL_Color color)
    : w(width), h(height), color(color)
{
    reset();  // center and randomize velocity
}


void Ball::update() {
    x += vx;
    y += vy;

    // Bounce off window borders 
    if (x <= 0 || x + w >= 800) vx = -vx;
    if (y <= 0 || y + h >= 600) vy = -vy;
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) };
    SDL_RenderFillRect(renderer, &rect);
}
