#include "DEBUG.h"
#include <iostream>

#include "Bishop.h"

Bishop::Bishop(Point position, Player* player)
	: Piece::Piece(position, player)
{
	SetPieceID('b');
	m_NbOfDirections = 4;
	m_Directions = new Point[m_NbOfDirections];
	m_Directions[0] = Point( 1,  1);
	m_Directions[1] = Point(-1,  1);
	m_Directions[2] = Point( 1, -1);
	m_Directions[3] = Point(-1, -1);

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}