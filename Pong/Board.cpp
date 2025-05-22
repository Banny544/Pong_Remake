#include "Board.h"

Board::Board(int x, int y, int w, int h, SDL_Color color)
    : boardColor(color), Player1_score(0), Player2_score(0)
{
    boardRect = { x, y, w, h };
}

void Board::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, boardColor.r, boardColor.g, boardColor.b, boardColor.a);

    const int thickness = 4;

    // Top edge
    SDL_Rect top = { 0, 0, boardRect.w, thickness };
    SDL_RenderFillRect(renderer, &top);

    // Bottom edge
    SDL_Rect bottom = { 0, boardRect.h - thickness, boardRect.w, thickness };
    SDL_RenderFillRect(renderer, &bottom);

    // Left edge
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); //blue
    SDL_Rect left = { 0, 0, thickness, boardRect.h };
    SDL_RenderFillRect(renderer, &left);

    // Right edge
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);//red
    SDL_Rect right = { boardRect.w - thickness, 0, thickness, boardRect.h };
    SDL_RenderFillRect(renderer, &right);

    // Vertical center line
    int centerX = boardRect.w / 2;
    int center_line_thickness = 2;

    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 100);
    SDL_Rect lineRect = { centerX - center_line_thickness / 2, 0, center_line_thickness, boardRect.h };
    SDL_RenderFillRect(renderer, &lineRect);

}

