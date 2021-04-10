#pragma once

#include "Piece.h"
#include "HasMoved.h"

class King : public Piece, public HasMoved
{
private:
	King();

public:
	King(Point position, Player* player);

	void CheckPossibleMoves() override;

	void CheckCastleMoves();
	bool IsCastleMove(BoardCell* moveFrom, BoardCell* moveTo);
	void Move(BoardCell* moveFrom, BoardCell* moveTo) override;

	bool IsChecked() const;
};

/*
Thoughts for checks:

	- before each player turn: 
		- scan for checks
		- If K is checked:
			- Can K move
			- Can K kill attacker
			- Can others protect king?
			- Can others kill attacker

Each board cell, could have an Attackers list (max = 16):
	- Is king on attacked cell?
	- When checking moves -> Add a IsCellAttacked() step

These attackers lists should be updated at each player turn...
it would have to be reset every time. 







*/