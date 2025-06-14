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
    
    void setPlayer1Score(int score);
    void setPlayer2Score(int score);

    int getPlayer1Score() const;
    int getPlayer2Score() const;

    bool checkWallCollision(int ballX, int ballWidth);


};
