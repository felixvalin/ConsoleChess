#pragma once

#include "Player.h"
#include "Board.h"

class Board;

class GameState
{
private:
	Piece* m_BoardState[64];

	bool m_IsWhitesTurn = false;

	GameState();

public:
    GameState(bool isWhitesTurn, const Board* board);

	inline Piece* GetPiece(int index) const { return m_BoardState[index]; }
};

