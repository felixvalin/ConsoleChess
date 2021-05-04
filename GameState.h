#pragma once

#include "Player.h"
#include "Board.h"

class Board;

class GameState
{
private:
	//PieceState m_WhitePieceStates[max_nb_pieces];
	//PieceState m_BlackPieceStates[max_nb_pieces];
	/*PieceState m_PieceStates[max_nb_pieces * 2];*/

	Piece* m_BoardState[64];

	bool m_IsWhitesTurn = false;

	GameState();

public:
    GameState(bool isWhitesTurn, const Board* board);

	inline Piece* GetPiece(int index) const { return m_BoardState[index]; }
	//void UpdatePieces(Player& whitePlayer, Player& blackPlayer);
	//void UpdatePieces(Board& board) const;

	//Piece* GetPieceOn(Point position) const;
	//const PieceState* GetPieceState(Piece* piece) const;
};

