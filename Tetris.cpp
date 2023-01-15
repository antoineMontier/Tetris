#include "Tetris.hpp"

using namespace std;

Tetris::Tetris(){
    s = new SDL_Screen(1080, 720, "tetris", 60);
}

Tetris::~Tetris(){
    delete(s);
}

void Tetris::run(){
    while(s->isRunning()){

        s->bg(bg_Color.r, bg_Color.g, bg_Color.b);

        displayGrid(s->W()*.5);






        while (SDL_PollEvent(&e)){//possible to wait for an event with SDL_WaitEvent
            switch (e.type){

                case SDL_WINDOWEVENT:
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED)
                        s->updateSize();
                    break;

                case SDL_QUIT:
                    s->stopRunning(); // quit the program if the user closes the window
                    break;

                case SDL_MOUSEMOTION:
                    m_x = e.button.x;
                    m_y = e.button.y;
                    break;

                case SDL_KEYDOWN: // SDL_KEYDOWN : hold a key            SDL_KEYUP : release a key
                    switch (e.key.keysym.sym){ // returns the key ('0' ; 'e' ; 'SPACE'...)

                    case SDLK_ESCAPE:
                        s->stopRunning();
                        break;

                    default:
                        break;
                    }

                case SDL_KEYUP:
                    switch (e.key.keysym.sym){

                        default:
                            break;
                    }

                default:
                    break;
            }
        }
        s->refreshAndDetails();
    }
}

void Tetris::displayGrid(unsigned int width_using){
    //horizontal lines
    int xxx = 0;
    int yyy = 0;
    s->setColor(lines_Color); 
    for(int i = 0 ; i <= (int)tetris_lines ; i++){
        s->line(0, yyy - 1, width_using, yyy - 1);
        yyy += s->H()/tetris_lines;
    }
    //vertical lines
    for(int i = 0 ; i <= (int)tetris_columns ; i++){
        s->line(xxx, 0, xxx, s->H());
        xxx += width_using / tetris_columns;
    }
}








