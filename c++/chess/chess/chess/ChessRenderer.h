#ifndef CHESSRENDERER_H_INCLUDED
#define CHESSRENDERER_H_INCLUDED

#include "Board.h"

namespace Chess {
    namespace Renderer {
        class BaseRenderer {
          public:
            virtual void RenderBoard(Board * board) = 0;
        };
    }
}



#endif // CHESSRENDERER_H_INCLUDED
