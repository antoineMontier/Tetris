#include "Tetris.hpp"

using namespace std;

Tetris::Tetris(){
    s = new SDL_Screen();
}

Tetris::~Tetris(){
    delete(s);
}

void Tetris::run(){
    s->refresh();
}