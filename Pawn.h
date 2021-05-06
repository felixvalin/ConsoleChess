#pragma once
#include "Piece.h"

enum class PieceType;

class Pawn : public Piece
{
private:
	Point m_Diagonals[2];
	int m_ForwardDirection;

	bool m_IsFirstMove;

	int m_PromotionRow;

public:
	Pawn(Player* player);
	~Pawn();

	// Very different rules compared to other pieces
	void CheckPossibleMoves() override;
	bool IsEnPassantMove(BoardCell* moveFrom, BoardCell* moveTo) const;

	bool IsLegalMove(Point point) override;
	void Move(BoardCell* moveFrom, BoardCell* moveTo) override;

	void SetAttackedCells() override;

	// Should return the promoted piece? or modify as argument?
	//void Promote(PromotionType type, Piece* promotedPiece) const;
	PieceType AskForPromotion();
	bool CanPromote() const;// { return m_Position.y == m_PromotionRow; }
};

