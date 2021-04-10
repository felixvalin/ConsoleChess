#include "DEBUG.h"
#include <iostream>

#include "GameState.h"

GameState::GameState()
{
}

GameState::GameState(bool isWhitesTurn, Player& whitePlayer, Player& blackPlayer)
	: m_IsWhitesTurn(isWhitesTurn)
{
	for (int i = 0; i < max_nb_pieces; i++)
	{
		if (Piece* whitePiece = whitePlayer.GetPieces()[i])
			m_WhitePieceStates[i].Init(whitePiece);
		if (Piece* blackPiece = blackPlayer.GetPieces()[i])
			m_BlackPieceStates[i].Init(blackPiece);
	}

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

void GameState::UpdatePieces(Player& whitePlayer, Player& blackPlayer)
{
	whitePlayer.SetPieces(m_WhitePieceStates);
	blackPlayer.SetPieces(m_BlackPieceStates);
}

void GameState::UpdatePieces(Board& board) const
{
	board.SetState(*this);
}

Piece* GameState::GetPieceOn(Point position) const
{
	for (int i = 0; i < max_nb_pieces; i++)
	{
		if (m_WhitePieceStates[i].GetPosition() == position)
		{
			return m_WhitePieceStates[i].GetPiece();
		}

		if (m_BlackPieceStates[i].GetPosition() == position)
		{
			return m_BlackPieceStates[i].GetPiece();
		}
	}

	return nullptr;
}