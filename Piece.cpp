#include "Piece.hpp"

using namespace std;

Piece::Piece(int id){
    if(id < 0 || id > 6)
        x = 2;//std::cout << "error, out of range in Piece constructor" << std::endl;//throw new std::runtime_error("id is out of range in piece constructor");
    if(id == OOO){
        cells[0] = 0; cells[1] = 0;//top left
        cells[2] = 0+1; cells[3] = 0;//top rightg
        cells[4] = 0; cells[5] = 0+1;//down left
        cells[6] = 0+1; cells[7] = 0+1;//down right
        return;
    }else if(id == SSS){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 1; cells[3] = 0;//middle down
        cells[4] = 1; cells[5] = -1;//top middle
        cells[6] = 2; cells[7] = -1;//up left
        return;
    }else if(id == III){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 0; cells[3] = -1;
        cells[4] = 0; cells[5] = -2;
        cells[6] = 0; cells[7] = -3;//top
    }else if(id == ZZZ){
        cells[0] = 0; cells[1] = 0;//top left
        cells[2] = 1; cells[3] = 0;//top middle
        cells[4] = 1; cells[5] = 1;//bottom middle
        cells[6] = 2; cells[7] = 1;//down right
    }else if(id == LLL){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 0; cells[3] = -1;
        cells[4] = 0; cells[5] = -2;//top left
        cells[6] = 1; cells[7] = 0;//down right
    }else if(id == JJJ){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 1; cells[3] = 0;//down right
        cells[4] = 1; cells[5] = -1;
        cells[6] = 1; cells[7] = -2;//top right
    }else if(id == TTT){
        cells[0] = 0; cells[1] = 0;//top left
        cells[2] = 1; cells[3] = 0;//middle top
        cells[4] = 2; cells[5] = 0;//right top
        cells[6] = 1; cells[7] = 1;//middle down
    }
    color = (rand() % MAX_COLORS)  + 1;
}

int Piece::getCoefInTab(int index){
    if(index < 0 || index >= 8)
        throw std::invalid_argument("out of bounds of cells array in getCoefInTab method, Piece.cpp file\n");
    return cells[index];
}

Piece::~Piece(){
    //nothing to do
}

int Piece::getX()const{return x;}
int Piece::getY()const{std::cout << "eeeeeee y = " << y << "\n"; return y;}

void Piece::gravity(int power){
    y+=power;
}

int Piece::maxX() const{
    int xmax = 0;
    for(int i = 0 ; i < 8 ; i+=2)
        if(cells[i] > xmax)
            xmax = cells[i];
    return y + xmax;
}

int Piece::maxY() const{
    int ymax = 0;
    for(int i = 1 ; i < 8 ; i+=2)
        if(cells[i] > ymax)
            ymax = cells[i];
    return y + ymax;
}

int Piece::minX() const{
    int xmin = 0;
    for(int i = 0 ; i < 8 ; i+=2)
        if(cells[i] < xmin)
            xmin = cells[i];
    return y + xmin;
}

int Piece::minY() const{
    int ymin = 0;
    for(int i = 1 ; i < 8 ; i+=2)
        if(cells[i] < ymin)
            ymin = cells[i];
    return y + ymin;
}


void Piece::rotate(int id){
    
}

int Piece::getColor(){return color;}

void Piece::setColor(int color){color = color;}

void Piece::respawn(int ncolor, int nx, int ny, int id){
    x = nx;
    y = ny;
    color = ncolor;
    if(id == OOO){
        cells[0] = 0; cells[1] = 0;//top left
        cells[2] = 0+1; cells[3] = 0;//top rightg
        cells[4] = 0; cells[5] = 0+1;//down left
        cells[6] = 0+1; cells[7] = 0+1;//down right
        return;
    }else if(id == SSS){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 1; cells[3] = 0;//middle down
        cells[4] = 1; cells[5] = -1;//top middle
        cells[6] = 2; cells[7] = -1;//up left
        return;
    }else if(id == III){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 0; cells[3] = -1;
        cells[4] = 0; cells[5] = -2;
        cells[6] = 0; cells[7] = -3;//top
    }else if(id == ZZZ){
        cells[0] = 0; cells[1] = 0;//top left
        cells[2] = 1; cells[3] = 0;//top middle
        cells[4] = 1; cells[5] = 1;//bottom middle
        cells[6] = 2; cells[7] = 1;//down right
    }else if(id == LLL){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 0; cells[3] = -1;
        cells[4] = 0; cells[5] = -2;//top left
        cells[6] = 1; cells[7] = 0;//down right
    }else if(id == JJJ){
        cells[0] = 0; cells[1] = 0;//down left
        cells[2] = 1; cells[3] = 0;//down right
        cells[4] = 1; cells[5] = -1;
        cells[6] = 1; cells[7] = -2;//top right
    }else if(id == TTT){
        cells[0] = 0; cells[1] = 0;//top left
        cells[2] = 1; cells[3] = 0;//middle top
        cells[4] = 2; cells[5] = 0;//right top
        cells[6] = 1; cells[7] = 1;//middle down
    }
}

void Piece::setX(int nx){x = nx;}
void Piece::setY(int ny){y = ny;}


int Piece::pieceWidth(int id){
    switch(id){
        case OOO:
            return 2;
            break;
        
        case SSS:
            return 3;
            break;
                
        case III:
            return 1;
            break;
                    
        case ZZZ:
            return 3;
            break;
                    
        case LLL:
            return 2;
            break;
                    
        case JJJ:
            return 2;
            break;
                    
        case TTT:
            return 3;
            break;
        
        default:
            return -1;
            break;
    }
}

int Piece::pieceHeight(int id){
    switch(id){
        case OOO:
            return 2;
            break;
        
        case SSS:
            return 2;
            break;
                
        case III:
            return 3;
            break;
                    
        case ZZZ:
            return 2;
            break;
                    
        case LLL:
            return 3;
            break;
                    
        case JJJ:
            return 3;
            break;
                    
        case TTT:
            return 3;
            break;
        
        default:
            return -1;
            break;
    }
}
