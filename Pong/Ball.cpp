#include "Ball.h"
#include <cstdlib>
#include <ctime>


int Ball::getX() const { return static_cast<int>(x); }
int Ball::getWidth() const { return static_cast<int>(w); }

int Ball::getY() const { return static_cast<int>(y); }
int Ball::getHeight() const { return static_cast<int>(h); }

// Start ball in center with random direction
void Ball::reset() {
    // Reset to center
    x = 400 - w / 2;
    y = 300 - h / 2;

    // Random horizontal direction (left or right)
    vx = (std::rand() % 2 == 0) ? 4.0f : -4.0f;

    // Random vertical offset between -2 and +2
    vy = static_cast<float>((std::rand() % 5) - 2);  // -2 to +2
}

// Constructor: set size and color, then reset position
Ball::Ball(float width, float height, SDL_Color color)
    : w(width), h(height), color(color)
{
    reset();  // center and randomize velocity
}


// Update ball position and bounce off top/bottom edges
void Ball::update() {
    x += vx;
    y += vy;

    // Bounce off window borders 
    if (x <= 0 || x + w >= 800) vx = -vx;
    if (y <= 0 || y + h >= 600) vy = -vy;
}

// Render the ball as a white square
void Ball::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = { static_cast<int>(x), static_cast<int>(y), static_cast<int>(w), static_cast<int>(h) };
    SDL_RenderFillRect(renderer, &rect);
}


// Bounce ball to the left
void Ball::bounceLeft() {
    vx = -std::abs(vx);  
}


// Bounce ball to the right
void Ball::bounceRight() {
    vx = std::abs(vx);
}