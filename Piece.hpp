#ifndef PIECE_HPP
#define PIECE_HPP

#define OOO 0
#define SSS 1
#define III 2
#define ZZZ 3
#define LLL 4
#define JJJ 5
#define TTT 6

class Piece{

    private:
        int x, y;
        int cells[6*2];//store the x1, y1 then x2, y2 ...

    public:

        Piece(int id);

        ~Piece();





};
#endif