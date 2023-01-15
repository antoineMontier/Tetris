#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "SDL_Screen.hpp"
#include "Piece.hpp"

class Tetris{

    private:
        SDL_Screen *s;
        const unsigned int tetris_lines = 10;
        const unsigned int tetris_columns = 5;
        int m[10][5];
        SDL_Event e;
        int m_x, m_y;



        const SDL_Color bg_Color = {128, 172, 255, 255};
        const SDL_Color lines_Color = {120, 120, 120, 255};

    public:

        Tetris();

        ~Tetris();

        void run();

        void displayGrid(unsigned int width_using);

};


#endif