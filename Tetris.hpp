#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "SDL_Screen.hpp"
#include "Piece.hpp"
#include "LinkedList.cpp"

#define LINES 10
#define COLUMNS 10
#define GRID_WIDTH (.5)
#define FALLING_SPEED (0.1)

#define NO_MOVE 0
#define RIGHT_MOVE (1)
#define LEFT_MOVE (-1)

class Tetris{

    private:
        SDL_Screen *s;
        int m[COLUMNS][LINES];
        SDL_Event e;
        int m_x, m_y;
        int last_piece_color;
        int last_shape;
        Piece* FallingPiece;
        double p_x, p_y;
        bool game_running;
        int move_piece;


        const SDL_Color bg_Color = {128, 172, 255, 255};
        const SDL_Color lines_Color = {120, 120, 120, 255};

    public:

        Tetris();

        ~Tetris();

        void run();

        void displayGrid(unsigned int width_using);

        void UpdateMatrix();

        void displayMatrix(unsigned int width_using);
        
        void generateNewPiece();

        void saveFellPiece();

        void resetMatrix();

        void displayFallingPiece(unsigned int width_using);

        void applyGravity(double strenght);

        bool isOnFloor();

        bool isUpCeil();
};


#endif