#include <iostream>
#include "chess.h"
#include "chesspieces.h"
#include "chessutils.h"
#include "board.h"
#include "literals.h"

using namespace std;
using namespace Chess;

int main()
{
	Board * board = new Board();
	board->Render();
	delete board;
	cout << Utility::PieceColourStrings[1];
		int x = 0;
	cin >> x;

	return 0;
}

