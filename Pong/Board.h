#pragma once
#include <SDL.h>

class Board
{
private:
    double Player1_score;
    double Player2_score;
    SDL_Rect boardRect;
    SDL_Color boardColor;

public:
    Board(int x, int y, int w, int h, SDL_Color color);
    void render(SDL_Renderer* renderer);
};
