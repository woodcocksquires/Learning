#include <iostream>
#include "chess.h"
#include "ChessRenderer.h"
#include "ConsoleChessRenderer.h"
#include "game.h"
#include "aitypejarvis.h"
#include <ctime>


using namespace std;
using namespace Chess;
using namespace Chess::Renderer;

int main()
{
	srand(time(NULL));
	BaseRenderer * renderer = new ConsoleChessRenderer();
	Game game = Game(renderer);
	game.AddAIPlayer(new AIType_Jarvis());
	game.Start();
    int x = 0;
	cin >> x;

	delete renderer;
	return 0;
}

