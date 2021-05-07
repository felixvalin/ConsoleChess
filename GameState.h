#pragma once

#include "Player.h"
#include "Board.h"

class Board;

class GameState
{
private:
	Piece* m_BoardState[64];

	Piece* m_LastPieceMoved = nullptr;

	GameState();

public:
    GameState(const Board* board);

	inline Piece* GetPiece(int index) const { return m_BoardState[index]; }
	inline Piece* GetLastPieceMoved() const { return m_LastPieceMoved; }
};

