#include "DEBUG.h"
#include <iostream>

#include "Knight.h"

Knight::Knight(Point position, Player* player)
	: Piece::Piece(position, player)
{
	SetPieceID('n');
	m_NbOfDirections = 8;
	m_Directions = new Point[m_NbOfDirections];
	m_Directions[0] = Point(2, 1);
	m_Directions[1] = Point(-2, 1);
	m_Directions[2] = Point(2, -1);
	m_Directions[3] = Point(-2, -1);
	m_Directions[4] = Point(1, 2);
	m_Directions[5] = Point(-1, 2);
	m_Directions[6] = Point(1, -2);
	m_Directions[7] = Point(-1, -2);

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}
