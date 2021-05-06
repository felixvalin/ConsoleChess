#pragma once

#include <array>

#include "BoardCell.h"
#include "Piece.h"

class GameState;

class Board
{
private:
	static const unsigned int s_BoardWidth = 8;
	static const unsigned int s_BoardSize = 64;
	BoardCell m_Cells[s_BoardSize];

	Piece* m_LastPieceMoved = nullptr;

public: 
	Board();
	~Board();

	static Point GetPositionFromIndex(int cellIndex);
	static int GetIndexFromPosition(Point position);
	inline static int GetRowIndexFromAlphaCoord(char letter) { return letter > 'z' ? letter - 'A' : letter - 'a'; };
	inline static int GetColIndexFromNumCoord(char numeral) { return GetBoardWidth() - (numeral - '0'); }
	
	static void PrintHorizontalLine();

	static inline const unsigned int GetBoardWidth() { return s_BoardWidth; }
	static inline const unsigned int GetBoardSize() { return s_BoardSize; }
	static bool IsOutOfBoard(Point position);

	inline BoardCell* GetBoardCell(int index) { return m_Cells+index; }
	// POS IS NOT RIGHT HERE !!!!!
	inline BoardCell* GetBoardCell(Point pos) { return m_Cells + Board::GetIndexFromPosition(pos); }
	inline BoardCell* GetBoardCell(const Piece* piece) { return m_Cells + GetIndexFromPosition(GetPiecePosition(piece)); }
	inline BoardCell* GetBoardCells() { return m_Cells; }

	inline const Piece* GetLastPieceMoved() const { return m_LastPieceMoved; }
	inline void SetLastPieceMoved(Piece* piece) { m_LastPieceMoved = piece; }

	void Draw(bool shouldClearBuffer = true);

	void AddPiece(Piece* piece, Point position);
	Piece* GetPieceAt(Point position) const;
	Point GetPiecePosition(const Piece* piece) const;
	void SetState(const GameState& state);

	void ResetAttackedCells();
};



