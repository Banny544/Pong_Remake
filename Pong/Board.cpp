#include "Board.h"
#include <array>

void Board::setPlayer1Score(int score) {
    Player1_score = score;
}

void Board::setPlayer2Score(int score) {
    Player2_score = score;
}

int Board::getPlayer1Score() const {
    return static_cast<int>(Player1_score);
}

int Board::getPlayer2Score() const {
    return static_cast<int>(Player2_score);
}

const std::array<std::array<bool, 7>, 10> segmentMap = { {
    {1,1,1,1,1,1,0}, // 0
    {0,1,1,0,0,0,0}, // 1
    {1,1,0,1,1,0,1}, // 2
    {1,1,1,1,0,0,1}, // 3
    {0,1,1,0,0,1,1}, // 4
    {1,0,1,1,0,1,1}, // 5
    {1,0,1,1,1,1,1}, // 6
    {1,1,1,0,0,0,0}, // 7
    {1,1,1,1,1,1,1}, // 8
    {1,1,1,1,0,1,1}  // 9
} };

void drawSegment(SDL_Renderer* renderer, SDL_Rect rect) {
    SDL_RenderFillRect(renderer, &rect);
}

// -------- Segment Mapping for 7-Segment Digits --------


/*
   -- A --
  |       |
  F       B
  |       |
   -- G --
  |       |
  E       C
  |       |
   -- D --
*/

// Draw one filled rectangle segment
void drawDigit(SDL_Renderer* renderer, int digit, int x, int y, int scale, SDL_Color color) {
    if (digit < 0 || digit > 9) return;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    int s = scale;
    SDL_Rect A = { x + s, y, s * 3, s };
    SDL_Rect B = { x + s * 4, y + s, s, s * 3 };
    SDL_Rect C = { x + s * 4, y + s * 5, s, s * 3 };
    SDL_Rect D = { x + s, y + s * 8, s * 3, s };
    SDL_Rect E = { x, y + s * 5, s, s * 3 };
    SDL_Rect F = { x, y + s, s, s * 3 };
    SDL_Rect G = { x + s, y + s * 4, s * 3, s };

    const std::array<bool, 7>& segs = segmentMap[digit];
    if (segs[0]) drawSegment(renderer, A);
    if (segs[1]) drawSegment(renderer, B);
    if (segs[2]) drawSegment(renderer, C);
    if (segs[3]) drawSegment(renderer, D);
    if (segs[4]) drawSegment(renderer, E);
    if (segs[5]) drawSegment(renderer, F);
    if (segs[6]) drawSegment(renderer, G);
}

// Constructor for board
Board::Board(int x, int y, int w, int h, SDL_Color color)
    : boardColor(color), Player1_score(0), Player2_score(0)
{
    boardRect = { x, y, w, h };
}


// Render the game board with borders and score display
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

    SDL_SetRenderDrawColor(renderer, 75,75,75, 25);
    SDL_Rect lineRect = { centerX - center_line_thickness / 2, 0, center_line_thickness, boardRect.h };
    SDL_RenderFillRect(renderer, &lineRect);

    SDL_Color Score = { 255, 255, 255, 255 }; // white

    drawDigit(renderer, static_cast<int>(Player1_score) % 10, 250, 50, 5, Score);
    drawDigit(renderer, static_cast<int>(Player2_score) % 10, 500, 50, 5, Score);

}

// Check if ball touched left or right wall and update score
bool Board::checkWallCollision(int ballX, int ballWidth) {
    int rightWallX = boardRect.w;
    int leftWallX = 0;

    if (ballX <= leftWallX) {
        Player2_score += 1;
        return true;   // Red missed ? Blue scores
    }
    else if (ballX + ballWidth >= rightWallX) {
        Player1_score += 1;
        return true;  // Blue missed ? Red scores
    }
    return false;
}

