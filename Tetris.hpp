#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "SDL_Screen.hpp"
#include "Piece.hpp"
#include "LinkedList.cpp"

#define LINES 10
#define COLUMNS 5
#define GRID_WIDTH (.5)

class Tetris{

    private:
        SDL_Screen *s;
        int m[COLUMNS][LINES];
        SDL_Event e;
        int m_x, m_y;
        LinkedList<Piece*> * pieces;


        const SDL_Color bg_Color = {128, 172, 255, 255};
        const SDL_Color lines_Color = {120, 120, 120, 255};

    public:

        Tetris();

        ~Tetris();

        void run();

        void displayGrid(unsigned int width_using);

        void UpdateMatrix();

        void displayMatrix(unsigned int width_using);

};


#endif