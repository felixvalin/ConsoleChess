#pragma once
#include "Piece.h"

class PieceState
{
private:
	Piece* m_Piece;
	Point m_Position;
	bool m_IsDead;

public:
	PieceState();

	void Init(Piece* piece);

	inline Piece* GetPiece() const { return m_Piece; }
	inline Point GetPosition() const { return m_Position; }
	inline bool IsDead() const { return m_IsDead; }
};

