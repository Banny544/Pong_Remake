#include "Ball.h"

Ball::Ball(float startX, float startY, float width, float height, float velX, float velY, SDL_Color color)
    : x(startX), y(startY), w(width), h(height), vx(velX), vy(velY), color(color)
{}

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
