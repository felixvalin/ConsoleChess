#pragma once

#include "BoardCell.h"
#include "Piece.h"

class Bishop : public Piece
{
private:
	Bishop();

public:
	Bishop(Point position, Player* player);
};