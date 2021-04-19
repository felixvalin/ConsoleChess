#pragma once

#include "PieceState.h"
#include "Player.h"

class Board;

class GameState
{
private:
	//PieceState m_WhitePieceStates[max_nb_pieces];
	//PieceState m_BlackPieceStates[max_nb_pieces];
	PieceState m_PieceStates[max_nb_pieces * 2];

	bool m_IsWhitesTurn = false;

	GameState();

public:
    GameState(bool isWhitesTurn, const Board* board);

	void UpdatePieces(Player& whitePlayer, Player& blackPlayer);
	void UpdatePieces(Board& board) const;

	Piece* GetPieceOn(Point position) const;
	const PieceState* GetPieceState(Piece* piece) const;
};

