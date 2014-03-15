#ifndef CONSOLECHESSRENDERER_H_INCLUDED
#define CONSOLECHESSRENDERER_H_INCLUDED

#include "ChessRenderer.h"

namespace Chess {
    namespace Renderer {
        enum ConsoleRowInnerType: int { Surround, Spacer, Content };
        class ConsoleChessRenderer: public BaseRenderer {
          private:
            void RenderBoardRowBorder();
            void RenderBoardRowInner(ConsoleRowInnerType type, Board * board, int offset, bool inverse);
            void RenderBoardRowNonContent(int offset, bool inverse, bool isSpacer);
            void RenderBoardRowNonContentColumn(int row, int col, bool inverse, bool isSpacer);
            void RenderBoardRowContent(Board * board, int offset, bool inverse);
            void RenderBoardRowContentColumn(Board * board, int offset, int coloffset, bool inverse);
            void RenderBoardLabelRow(bool inverse);
            Colour GetSquareColour(int rowOffset, int colOffset);
          protected:
            void RenderBoardRow(Board * board, int offset, bool inverse);
          public:
            virtual void RenderBoard(Board * board, bool inverse);
        };
    }
}


#endif // CONSOLECHESSRENDERER_H_INCLUDED
