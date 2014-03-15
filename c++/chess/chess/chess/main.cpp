#include <iostream>
#include "chess.h"
#include "chesspieces.h"
#include "chessutils.h"
#include "board.h"
#include "literals.h"
#include "ChessRenderer.h"
#include "ConsoleChessRenderer.h"

using namespace std;
using namespace Chess;
using namespace Chess::Renderer;

int main()
{
	Board * board = new Board();
	BaseRenderer * renderer = new ConsoleChessRenderer();
	renderer->RenderBoard(board, false);
	cout << endl;
	board->MovePiece("E2","E4");
	renderer->RenderBoard(board, true);

    int x = 0;
	cin >> x;

    delete board;
	delete renderer;
	return 0;
}

