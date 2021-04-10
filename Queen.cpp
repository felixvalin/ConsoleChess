#include "DEBUG.h"
#include <iostream>

#include "Queen.h"

Queen::Queen(Point position, Player* player)
	: Piece(position, player)
{
	SetPieceID('q');
	m_NbOfDirections = 8;
	m_Directions = new Point[m_NbOfDirections];
	m_Directions[0] = Point(1, 0);
	m_Directions[1] = Point(-1, 0);
	m_Directions[2] = Point(0, 1);
	m_Directions[3] = Point(0, -1);
	m_Directions[4] = Point(1, 1);
	m_Directions[5] = Point(-1, 1);
	m_Directions[6] = Point(1, -1);
	m_Directions[7] = Point(-1, -1);

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

//void Queen::PromotePawn(Pawn* pawn)
//{
//
//}
