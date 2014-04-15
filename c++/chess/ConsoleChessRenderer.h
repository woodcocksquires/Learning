#ifndef CONSOLECHESSRENDERER_H_INCLUDED
#define CONSOLECHESSRENDERER_H_INCLUDED

#include "ChessRenderer.h"
#include "chess.h"
#include <utility>

using namespace Chess;

namespace Chess {
    namespace Renderer {
        enum ConsoleRowInnerType: int { Surround, Spacer, Content };
        class ConsoleChessRenderer: public BaseRenderer {
          private:
            void RenderBoardRowBorder();
            void RenderBoardRowInner(ConsoleRowInnerType type, Board * board, int offset, bool inverse);
            void RenderBoardRowNonContent(int offset, bool inverse, bool isSpacer, Board * board);
            void RenderBoardRowNonContentColumn(int row, int col, bool inverse, bool isSpacer, Board * board);
            void RenderBoardRowContent(Board * board, int offset, bool inverse);
            void RenderBoardRowContentColumn(Board * board, int offset, int coloffset, bool inverse);
            void RenderBoardLabelRow(bool inverse);
          protected:
            void RenderBoardRow(Board * board, int offset, bool inverse);
          public:
            virtual ~ConsoleChessRenderer();
            virtual void RenderBoard(Board * board, bool inverse);
            virtual void StartGame();
            virtual PlayerType GetPlayerType(Colour colour);
            virtual pair<Move *, MovePieceResult> MakeMove(Colour colour, Board * board);
            virtual void RenderMessage(string message);
            virtual Piece * PromotePiece(Colour colour, Board * board);
            virtual void RenderMoves(vector<Move *> moves);
            bool ConfirmChoice(string message);
        };
    }
}


#endif // CONSOLECHESSRENDERER_H_INCLUDED
