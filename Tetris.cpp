#include "Tetris.hpp"

using namespace std;

Tetris::Tetris(){
    s = new SDL_Screen(1080, 720, "tetris", 60);
    pieces = new LinkedList<Piece*>();
    FallingPiece = new Piece(III);
    last_piece_color = 0;
    resetMatrix();
}

Tetris::~Tetris(){
    delete(FallingPiece);
    delete(s);
    delete(pieces);
}

void Tetris::run(){
        generateNewPiece();

    while(s->isRunning()){

        s->bg(bg_Color.r, bg_Color.g, bg_Color.b);

        displayGrid(s->W()*GRID_WIDTH);

        displayFallingPiece(s->W()*GRID_WIDTH);
        displayMatrix(s->W()*GRID_WIDTH);
        applyGravity(0.05);

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
    for(int i = 0 ; i <= LINES ; i++){
        s->line(0, yyy - 1, width_using, yyy - 1);
        yyy += s->H()/LINES;
    }
    //vertical lines
    for(int i = 0 ; i <= COLUMNS ; i++){
        s->line(xxx, 0, xxx, s->H());
        xxx += width_using / COLUMNS;
    }
}

void Tetris::UpdateMatrix(){
    for(int i=0; i<COLUMNS; i++)
        for(int j=0; j<LINES; j++)
            m[i][j] = 0;//reset matrix

    int x, y;
    for(int i = 0 ; i < pieces->size() ; i++){
        x = pieces->get(i)->getX();
        y = pieces->get(i)->getY();
        m[x][y] = pieces->get(i)->getColor();
        for(int j = 2 ; j < 8 ; j++){
            if(j % 2 == 0)
                x = pieces->get(i)->getCoefInTab(j);
            else if(j % 2 == 1){
                y = pieces->get(i)->getCoefInTab(j);
                m[x][y] = pieces->get(i)->getColor();
            }
        }
    }
}

void Tetris::displayMatrix(unsigned int width_using){
    for(int i=0; i<COLUMNS; i++){
        for(int j=0; j<LINES; j++){
            std::cout << "m[" << i << "][" << j << "] = "<< m[i][j] <<"\n";
            if(m[i][j] != 0){
                std::cout << "aaa" << i << " " << j << std::endl;
                switch(m[i][j]){
                    case YELLOW:
                        s->setColor(255, 191, 0);
                        break;

                    case RED:
                        s->setColor(255, 0, 0);
                        break;

                    case GREEN:
                        s->setColor(0, 255, 0);
                        break;

                    case BLUE:
                        s->setColor(0, 0, 255);
                        break;

                    case LIGHT_BLUE:
                        s->setColor(0, 255, 255);
                        break;

                    case BLACK:
                        s->setColor(0, 0, 0);
                        break;

                    case MAGENTA:
                        s->setColor(255, 0, 255);
                        break;

                    case ORANGE:
                        s->setColor(255, 95, 31);
                        break;

                    case PINK:
                        s->setColor(255, 192, 203);
                        break;
                    
                    default:
                        throw std::runtime_error("Error in color gestion\n");
                        break;
                }
                s->filledRect(i*width_using/COLUMNS, j*s->H()/LINES, width_using/COLUMNS, s->H()/LINES, 5);
            }
        }
    }
}

void Tetris::generateNewPiece(){
    int randColor = last_piece_color;

    do{
        randColor = rand() % MAX_COLORS + 1;
    }while(randColor == last_piece_color);

    FallingPiece->respawn(randColor, 2, 4, OOO);
    p_x = 1;
    p_y = 2.2;
}

void Tetris::saveFellPiece(){
    int x,y;
    x = FallingPiece->getX();
    y = FallingPiece->getY();
    m[x][y] = FallingPiece->getColor();
    for(int j = 2 ; j < 8 ; j++){
        if(j % 2 == 0)
            x = FallingPiece->getCoefInTab(j);
        else if(j % 2 == 1){
            y = FallingPiece->getCoefInTab(j);
            m[x][y] = FallingPiece->getColor();
        }
    }
}

void Tetris::resetMatrix(){
    for(int i=0; i<COLUMNS; i++)
        for(int j=0; j<LINES; j++)
            m[i][j] = 0;//reset matrix
}

void Tetris::displayFallingPiece(unsigned int width_using){
    switch(FallingPiece->getColor()){
        case YELLOW:
            s->setColor(255, 191, 0);
            break;
        case RED:
            s->setColor(255, 0, 0);
            break;
        case GREEN:
            s->setColor(0, 255, 0);
            break;
        case BLUE:
            s->setColor(0, 0, 255);
            break;
        case LIGHT_BLUE:
            s->setColor(0, 255, 255);
            break;
        case BLACK:
            s->setColor(0, 0, 0);
            break;
        case MAGENTA:
            s->setColor(255, 0, 255);
            break;
        case ORANGE:
            s->setColor(255, 95, 31);
            break;
        case PINK:
            s->setColor(255, 192, 203);
            break;
        default:
            throw std::runtime_error("Error in color gestion\n");
            break;
    }
    int x, y;
    for(int j = 0 ; j < 8 ; j++){
            if(j % 2 == 0)
                x = FallingPiece->getCoefInTab(j);//x
            else if(j % 2 == 1){
                y = FallingPiece->getCoefInTab(j);//y
                s->filledRect((p_x+x)*width_using/COLUMNS, (p_y+y)*s->H()/LINES, width_using/COLUMNS, s->H()/LINES, 5);
            }
        }
}

void Tetris::applyGravity(double strenght){
    p_y += strenght;
}


