#include "DEBUG.h"
#include <iostream>

#include "BoardCell.h"
#include "Board.h"
#include "Piece.h"

constexpr bool debug = false;

BoardCell::BoardCell()
	: m_Position(Point(0,0)), m_Occupant(nullptr), m_ParentBoard(nullptr)
{
	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

BoardCell::BoardCell(int index, Board* board)
	: BoardCell()
{
	m_Position = Board::GetPositionFromIndex(index);
	m_ParentBoard = board;
}

void BoardCell::Draw()
{
	if (debug)
	{
		if (IsUnderAttack())
		{
			std::cout << "|*";
		}
		else
		{
			std::cout << "| ";
		}
	}
	else
	{
		std::cout << "| ";
	}

	if (IsOccupied())
	{
		std::cout << m_Occupant->GetPieceID() << " ";
	}
	else
	{
		std::cout << "  ";
	}

	if (m_Position.x == Board::GetBoardWidth() - 1)
	{
		std::cout << "|" << std::endl;
	}
}

void BoardCell::ResetAttackers()
{
	for (int i = 0; i < m_NbOfAttackers; i++)
	{
		m_Attackers[i] = nullptr;
	}

	m_NbOfAttackers = 0;
}

void BoardCell::AddPiece(Piece* piece)
{
	if (m_Occupant)
	{
		m_Occupant->Kill();
	}

	m_Occupant = piece;
}

void BoardCell::RemovePiece(bool shouldKill /*= true*/)
{
	if (m_Occupant)
	{
		m_Occupant = nullptr;
	}
}