#ifndef TETRIS_HPP
#define TETRIS_HPP

#include "SDL_Screen.hpp"

class Tetris{

    private:
        SDL_Screen *s;

    public:

        Tetris();

        ~Tetris();

        void run();

};


#endif