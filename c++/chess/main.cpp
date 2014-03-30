#include <iostream>
#include "chess.h"
#include "ChessRenderer.h"
#include "ConsoleChessRenderer.h"
#include "game.h"

using namespace std;
using namespace Chess;
using namespace Chess::Renderer;

int main()
{
	BaseRenderer * renderer = new ConsoleChessRenderer();
	Game game = Game(renderer);
	game.Start();
    int x = 0;
	cin >> x;

	delete renderer;
	return 0;
}

