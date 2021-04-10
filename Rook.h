#pragma once

#include "BoardCell.h"
#include "Piece.h"
#include "HasMoved.h"

class Rook: public Piece, public HasMoved
{
private:
	Rook();

public:
	Rook(Point position, Player* player);

	void Move(BoardCell* moveFrom, BoardCell* moveTo) override;
};

