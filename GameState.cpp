#include "DEBUG.h"
#include <iostream>

#include "Board.h"
#include "GameState.h"

GameState::GameState()
{
}

GameState::GameState(bool isWhitesTurn, const Board* board)
    : m_IsWhitesTurn(isWhitesTurn)
{
    for (unsigned int boardIndex = 0; boardIndex < Board::GetBoardSize(); boardIndex++)
    {
        if (Piece* piece = board->GetPieceAt(Board::GetPositionFromIndex(boardIndex)))
        {
            m_BoardState[boardIndex] = piece;
        }
        else
        {
            m_BoardState[boardIndex] = nullptr;
        }
    }

    m_LastPieceMoved = board->GetLastPieceMoved();

    if (DEBUG)
        std::cout << typeid(this).name() << " has been created! " << std::endl;
}