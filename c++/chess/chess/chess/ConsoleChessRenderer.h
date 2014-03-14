#ifndef CONSOLECHESSRENDERER_H_INCLUDED
#define CONSOLECHESSRENDERER_H_INCLUDED

#include "ChessRenderer.h"

namespace Chess {
    namespace Renderer {
        enum ConsoleRowInnerType: int { Surround, Spacer, Content };
        class ConsoleChessRenderer: public BaseRenderer {
          private:
            void RenderBoardRowBorder();
            void RenderBoardRowInner(ConsoleRowInnerType type);
          protected:
            void RenderBoardRow(int offset);
          public:
            virtual void RenderBoard(Board * board);
        };
    }
}


#endif // CONSOLECHESSRENDERER_H_INCLUDED
