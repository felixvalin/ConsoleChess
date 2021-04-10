#pragma once

#include "Piece.h"
#include "HasMoved.h"

class Knight : public Piece, public HasMoved
{
private:
	Knight();

public:
	Knight(Point position, Player* player);
};

