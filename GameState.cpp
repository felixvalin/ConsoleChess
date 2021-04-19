#include "DEBUG.h"
#include <iostream>

#include "Board.h"
#include "GameState.h"

GameState::GameState()
{
}

//GameState::GameState(bool isWhitesTurn, Player& whitePlayer, Player& blackPlayer)
//	: m_IsWhitesTurn(isWhitesTurn)
//{
//	for (int i = 0; i < max_nb_pieces; i++)
//	{
//        if (Piece* whitePiece = whitePlayer.GetPieces()[i])
//            m_WhitePieceStates[i].Init(whitePiece);
//		if (Piece* blackPiece = blackPlayer.GetPieces()[i])
//			m_BlackPieceStates[i].Init(blackPiece);
//	}
//
//	if (DEBUG)
//		std::cout << typeid(this).name() << " has been created! " << std::endl;
//}

GameState::GameState(bool isWhitesTurn, const Board* board)
    : m_IsWhitesTurn(isWhitesTurn)
{
	int pieceStateIndex = 0;

    for (unsigned int i = 0; i < Board::GetBoardSize(); i++)
    {
		if (Piece* piece = board->GetPieceAt(Board::GetPositionFromIndex(i)))
		{
            m_PieceStates[pieceStateIndex].Init(piece);
			pieceStateIndex++;
		}
    }

    if (DEBUG)
        std::cout << typeid(this).name() << " has been created! " << std::endl;
}

void GameState::UpdatePieces(Player& whitePlayer, Player& blackPlayer)
{
	//whitePlayer.SetPieces(m_WhitePieceStates);
	//blackPlayer.SetPieces(m_BlackPieceStates);
}

void GameState::UpdatePieces(Board& board) const
{
	board.SetState(*this);
}

Piece* GameState::GetPieceOn(Point position) const
{
	//Piece* whitePiece = nullptr;
	//Piece* blackPiece = nullptr;

	//for (int i = 0; i < max_nb_pieces; i++)
	//{
	//	if (m_WhitePieceStates[i].GetPosition() == position)
	//	{
	//		whitePiece = m_WhitePieceStates[i].GetPiece();
	//	}

	//	if (!whitePiece)
 //       {
 //           if (m_BlackPieceStates[i].GetPosition() == position)
 //           {
 //               return m_BlackPieceStates[i].GetPiece();
 //           }
 //       }

	//	else
	//	{
	//		return whitePiece;
	//	}
	//}

	for (unsigned int i = 0; i < Board::GetBoardSize(); i++)
	{
		if (m_PieceStates[i].GetPosition() == position)
		{
			return m_PieceStates[i].GetPiece();
		}
	}

	return nullptr;
}

const PieceState* GameState::GetPieceState(Piece* piece) const
{
	//PieceState result;

	//for (int i = 0; i < max_nb_pieces; i++)
	//{
	//	if (m_WhitePieceStates[i].GetPiece() == piece)
 //       {
 //           return &m_WhitePieceStates[i];
 //       }

	//	if (m_BlackPieceStates[i].GetPiece() == piece)
	//	{
	//		return &m_BlackPieceStates[i];
	//	}
	//}

	for (unsigned int i = 0; i < Board::GetBoardSize(); i++)
	{
		if (m_PieceStates[i].GetPiece() == piece)
		{
			return &m_PieceStates[i];
		}
	}

	return nullptr;
}
