#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>

#define OOO 0
#define SSS 1
#define III 2
#define ZZZ 3
#define LLL 4
#define JJJ 5
#define TTT 6

#ifndef RIGHT
    #define RIGHT 1
#endif
#ifndef LEFT
    #define LEFT 2
#endif
#define MAX_COLORS 9
#define YELLOW 1
#define RED 2
#define GREEN 3
#define BLUE 4
#define LIGHT_BLUE 5
#define BLACK 6
#define MAGENTA 7
#define ORANGE 8
#define PINK 9

class Piece{

    private:
        int x, y;
        int cells[5*2];//store the x1, y1 then x2, y2 ...
        int color;

    public:

        Piece(int id);

        void respawn(int ncolor, int nx, int ny, int id);

        ~Piece();

        int getX() const;
        int getY() const;
        void setX(int nx);
        void setY(int ny);

        int getCoefInTab(int index);

        void gravity(int power);

        int maxX() const;
        int maxY() const;
        int minX() const;
        int minY() const;

        void rotate(int id);

        int getColor();

        void setColor(int color);

        static int pieceWidth(int id);
        static int pieceHeight(int id);


};
#endif