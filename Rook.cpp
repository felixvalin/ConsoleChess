#include "DEBUG.h"
#include <iostream>

#include "Rook.h"

Rook::Rook(Player* player)
	: Piece(player), HasMoved()
{
	SetPieceID('r');
	m_NbOfDirections = 4;
	m_Directions = new Point[m_NbOfDirections];
	m_Directions[0] = Point(1, 0);
	m_Directions[1] = Point(-1, 0);
	m_Directions[2] = Point(0, 1);
	m_Directions[3] = Point(0, -1);

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

void Rook::Move(BoardCell* moveFrom, BoardCell* moveTo)
{
	Piece::Move(moveFrom, moveTo);
	
	// For castling
	CheckFirstMove();
}