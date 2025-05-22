#include "Paddle.h"


// Constructor: initialize paddle position, size, speed, and color
Paddle::Paddle(int x, int y, int w, int h, int speed, SDL_Color color)
    : x(x), y(y), w(w), h(h), speed(speed), color(color) {}

// Move paddle up by its speed (prevent going off-screen)
void Paddle::moveUp() {
    if (y > 0)
        y -= speed;
}

// Move paddle down by its speed (prevent going off-screen)
void Paddle::moveDown(int windowHeight) {
    if (y + h < windowHeight)
        y += speed;
}

// Render the paddle as a filled rectangle using its color
void Paddle::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(renderer, &rect);
}

// Return the paddle's SDL_Rect for collision checks
SDL_Rect Paddle::getRect() const {
    return { x, y, w, h };
}
