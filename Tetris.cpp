#include "Tetris.hpp"

using namespace std;

Tetris::Tetris(){
    srand(time(NULL));
    s = new SDL_Screen(1080, 720, "tetris", 60);
    FallingPiece = new Piece(ZZZ);
    last_piece_color = 0;
    last_shape = -1;
    FallingPiece->setX(2 + rand() % 3);
    FallingPiece->setY(2 + rand() % 3);
    resetMatrix();
    game_running = true;
    move_piece = NO_MOVE;
}

Tetris::~Tetris(){
    delete(FallingPiece);
    delete(s);
}

void Tetris::run(){
    generateNewPiece();

    while(s->isRunning()){

        if(game_running){
            s->bg(bg_Color.r, bg_Color.g, bg_Color.b);
            displayGrid(s->W()*GRID_WIDTH);
            displayFallingPiece(s->W()*GRID_WIDTH);
            displayMatrix(s->W()*GRID_WIDTH);
            applyGravity(FALLING_SPEED);
        }

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
                        case SDLK_z:
                            move_piece = RIGHT_MOVE;
                            break;
                        case SDLK_a:
                            move_piece = LEFT_MOVE;
                            break;
                        case SDLK_RIGHT:
                            move_piece = RIGHT_MOVE;
                            break;
                        case SDLK_LEFT:
                            move_piece = LEFT_MOVE;
                            break;

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
        s->refresh();
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
    /*for(int i=0; i<COLUMNS; i++)
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
    }*/
}

void Tetris::displayMatrix(unsigned int width_using){
    for(int i=0; i<COLUMNS; i++){
        for(int j=0; j<LINES; j++){
            //std::cout << "m[" << i << "][" << j << "] = "<< m[i][j] <<"\n";
            if(m[i][j] != 0){
                //std::cout << "aaa" << i << " " << j << std::endl;
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

    int randShape = last_shape;
    do{
        randShape = rand() % (TTT + 1);
    }while(randShape == last_shape);

    last_piece_color = randColor;
    last_shape = randShape;
    p_x = rand() % (COLUMNS - Piece::pieceWidth(randShape) + 1);
    p_y = -2;

    FallingPiece->respawn(randColor, p_x, p_y, randShape);

}

void Tetris::saveFellPiece(){
    int ox = FallingPiece->getX();
    int oy = FallingPiece->getY();
    if(ox < 0 || ox >= COLUMNS){
        throw new std::invalid_argument("x value is wrong");
    }else if(oy < 0 || oy >= LINES){
        throw new std::invalid_argument("y value is wrong");
    }
    int ccc = FallingPiece->getColor();
    m[ox][oy] = ccc;
    int x, y;
    for(int j = 2 ; j < 8 ; j++){
        if(j % 2 == 0)
            x = ox+FallingPiece->getCoefInTab(j);
        else if(j % 2 == 1){
            y = oy+FallingPiece->getCoefInTab(j);
            if(x < 0 || x >= COLUMNS){
                throw new std::invalid_argument("x value is wrong\n");
            }else if(y < 0 || y >= LINES){
                throw new std::invalid_argument("y value is wrong\n");
            }
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
                s->filledRect((p_x+x)*width_using/COLUMNS, (p_y+y)*s->H()/LINES, width_using/COLUMNS, s->H()/LINES, 2);
            }
        }
}

void Tetris::applyGravity(double strenght){
    if(!isOnFloor()){
        if(move_piece == RIGHT_MOVE){
            if(canMoveRight()){
                p_x++;
                FallingPiece->setX(FallingPiece->getX()+1);
            }
            move_piece = NO_MOVE;
        }else if(move_piece == LEFT_MOVE){
            if(canMoveLeft()){
                p_x--;
                FallingPiece->setX(FallingPiece->getX()-1);
            }
            move_piece = NO_MOVE;
        }
        p_y = p_y + strenght;
        FallingPiece->setY(int(p_y + FALLING_SPEED));
    }else if(FallingPiece->minY() >= 0){
        saveFellPiece();
        generateNewPiece();
    }else{
        game_running = false;
    }
}

bool Tetris::isOnFloor(){
    int ox = FallingPiece->getX(), oy = FallingPiece->getY(), x, y;
    for(int j = 0 ; j < 8 ; j++){
        if(j % 2 == 0){
            x = FallingPiece->getCoefInTab(j);//x
        }else{
            y = FallingPiece->getCoefInTab(j);//y
        }
        int tmpppp = FallingPiece->maxY();
        if(tmpppp >= LINES - 1){
            return true;
        }else if(ox + x < COLUMNS && ox + x >= 0 && oy + y + 1 >= 0 && oy + y + 1 < LINES && m[ox + x][oy + y + 1] != 0){
            return true;
        }
    }
    return false;
}

bool Tetris::isUpCeil(){
    int ox = FallingPiece->getX(), oy = FallingPiece->getY(), x, y;
    if(oy < 0)
        return true;
    for(int j = 0 ; j < 8 ; j++){
        if(j % 2 == 0){
            x = FallingPiece->getCoefInTab(j);//x
        }else{
            y = FallingPiece->getCoefInTab(j);//y
        }
        if(FallingPiece->maxY() >= LINES - 1){
            std::cout << "validate\n";
            return true;
        }else if(ox + x < COLUMNS && ox + x >= 0 && oy + y + 1 >= 0 && oy + y + 1 < LINES && m[ox + x][oy + y + 1] != 0){
            std::cout << "unvalidate\n";
            return true;
        }
    }
    std::cout << "ccc" << std::endl;
    return false;
}

bool Tetris::canMoveLeft(){
    if(FallingPiece->minX() <= 0)
        return false;
    int ox = FallingPiece->getX();
    int oy = FallingPiece->getY();
    int x, y;
    for(int j = 0 ; j < 8 ; j++){
        if(j % 2 == 0)
            x = FallingPiece->getCoefInTab(j);//x
        else
            y = FallingPiece->getCoefInTab(j);//y
        if(((p_y + y >= 0 && oy + y +1 < LINES) && m[ox + x - 1][int(p_y + y+1)] != 0) || ((p_y + y >= 0 && oy + y < LINES) && m[ox + x - 1][int(p_y + y)] != 0))
            return false;
    }
    return true;
}

bool Tetris::canMoveRight(){
    if(FallingPiece->maxX() >= COLUMNS-1)
        return false;
    int ox = FallingPiece->getX();
    int oy = FallingPiece->getY();
    int x, y;
    for(int j = 0 ; j < 8 ; j++){
        if(j % 2 == 0)
            x = FallingPiece->getCoefInTab(j);//x
        else
            y = FallingPiece->getCoefInTab(j);//y
        if(((p_y + y >= 0 && oy + y +1 < LINES) && m[ox + x + 1][int(p_y + y+1)] != 0) || ((p_y + y >= 0 && oy + y < LINES) && m[ox + x + 1][int(p_y + y)] != 0))
            return false;
    }
    return true;
}

void Tetris::checkAndRemoveLines(){
    //check
    bool full;
    for(int l = LINES-1 ; l >= 0 ; l--){
        full = true;
        for(int c = 0 ; c < COLUMNS ; c++){
            full = full && m[c][l] != 0;
        }
        if(full){
            deleteLine(l);
        }
    }

}

void Tetris::deleteLine(int line){ 
    if(line < 0 || line >= LINES)
        throw std::invalid_argument("line index out of range\n");
    for(int i = line; i > 0 ; i--)
        for(int c = 0 ; c < COLUMNS; c++)
            m[c][i] = m[c][i-1];
    for(int i = 0 ; i < COLUMNS ; i++)
        m[0][i] = 0;
}






