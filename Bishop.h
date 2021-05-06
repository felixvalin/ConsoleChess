#pragma once

#include "BoardCell.h"
#include "Piece.h"

class Bishop : public Piece
{
private:
	Bishop();

public:
	Bishop(Player* player);
};