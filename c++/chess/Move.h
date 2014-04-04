#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include "Chess.h"
#include "Board.h"

namespace Chess {
    class Move {
      private:
        int startBoardPosition, endBoardPosition;
        bool pieceTaken;
        bool kingChecked;
        bool queenSideCastle;
        bool pawnPromotion;
        char pieceIdentifier;
        Colour colour;
      public:
        Move(int _startBoardPosition, int _endBoardPosition, bool _pieceTaken, char _pieceIdentifier, Colour _colour);
        string ToString();
        void SetPawnPromotion(Piece * piece);
        void SetKingChecked(bool queenSide);
    };
};

#endif // MOVE_H_INCLUDED


