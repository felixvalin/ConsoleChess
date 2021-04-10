#pragma once
#include <ctype.h>

#include "BoardCell.h"
#include "Board.h"

class Player;
class PieceState;

constexpr unsigned int max_possible_moves = 27;

class Piece
{
protected:
	char m_PieceID;
	Point m_Position;

	// Changing this from heap-allocated to stack is a really good thing since we reset it
	// for every piece, every time we switch player turn! so 16 heap-allocations avoided per turn!
	Point m_PossibleMoves[max_possible_moves];
	int m_PossibleMovesIndex;

	Point* m_Directions;
	int m_NbOfDirections;

	Board* m_Board;
	
	Player* m_Player;

	bool m_IsDead = false;

	Piece();

public:
	Piece(Point position, Player* player);
	~Piece();

	void Init(Board* board);

	inline char GetPieceID() { return m_PieceID; }
	void SetPieceID(char id);
	inline Point GetPosition() const { return m_Position; }
	inline void SetPosition(const Point& point) { m_Position = point; }
	bool IsWhitePiece() const;
	inline const Point* GetPossibleMoves() const { return m_PossibleMoves; }
	inline int GetNbOfMoves() const { return m_PossibleMovesIndex; }

	// These should be named Vision instead of Possible Moves 
	// since we check if move is legal outside this function now
	virtual void CheckPossibleMoves();
	void ResetPossibleMoves();

	virtual bool IsLegalMove(Point point);
	virtual void Move(BoardCell* moveFrom, BoardCell* moveTo);
	virtual void Move(BoardCell* moveTo);
	void Move(const PieceState& state);

	bool IsLastPieceMoved() const;

	inline bool IsDead() const { return m_IsDead; }
	inline void Kill() { m_IsDead = true; }

	// This is the first part for Checks (will allow player to see if king is in check (or check mate)!
	virtual void SetAttackedCells();
};


