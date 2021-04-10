#pragma once
#include "Pawn.h"
class IPromoteFromPawn
{
protected:
	virtual void PromotePawn(Pawn* pawn) = 0;
};

