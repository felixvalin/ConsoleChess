#pragma once
#include "PieceState.h"
#include "Player.h"

class GameState
{
private:
	PieceState m_WhitePieceStates[max_nb_pieces];
	PieceState m_BlackPieceStates[max_nb_pieces];

	bool m_IsWhitesTurn = false;

	GameState();

public:
	GameState(bool isWhitesTurn, Player& whitePlayer, Player& blackPlayer);

	void UpdatePieces(Player& whitePlayer, Player& blackPlayer);
	void UpdatePieces(Board& board) const;

	Piece* GetPieceOn(Point position) const;
};

