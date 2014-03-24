#ifndef CHESSRENDERER_H_INCLUDED
#define CHESSRENDERER_H_INCLUDED

#include "Board.h"
#include "Chess.h"

using namespace Chess;

namespace Chess {
    namespace Renderer {
        class BaseRenderer {
          public:
            virtual void RenderBoard(Board * board, bool inverse) = 0;
            virtual void StartGame() = 0;
            virtual PlayerType GetPlayerType(Colour colour) = 0;
            virtual MovePieceResult MakeMove(Colour colour, Board * board) = 0;
            virtual void RenderMessage(string message) = 0;
            virtual void RenderMoves() = 0;
            virtual ~BaseRenderer();
        };
    }
}



#endif // CHESSRENDERER_H_INCLUDED
