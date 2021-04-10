#pragma once

#include "Pawn.h"
#include "Piece.h"
//#include "PromoteFromPawn.h"

class Queen : public Piece//, public IPromoteFromPawn
{
private:
	Queen();

public:
	Queen(Point position, Player* player);

	//void PromotePawn(Pawn* pawn) override;
};

