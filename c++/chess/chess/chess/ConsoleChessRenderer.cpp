#include <iostream>
#include "ConsoleChessRenderer.h"
#include "Board.h"

using namespace Chess::Renderer;


void ConsoleChessRenderer::RenderBoard(Board * board) {
    RenderBoardRow(0);
}

void ConsoleChessRenderer::RenderBoardRow(int offset){
    RenderBoardRowBorder();



    RenderBoardRowBorder();
}

void ConsoleChessRenderer::RenderBoardRowBorder(){
    cout << "   ";
    for(int c=1; c<=8; c++)
    {
        cout << "+------";
        if(c==8){
            cout << "+";
        }
    }
    cout << endl;
}

void ConsoleChessRenderer::RenderBoardRowInner(ConsoleRowInnerType type){
    switch(type)
    {
        case ConsoleRowInnerType::Surround:
            cout << "stuff";
            break;
    }
}
