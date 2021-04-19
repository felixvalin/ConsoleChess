#pragma once

class Board;
class Piece;

constexpr int max_nb_of_attackers = 16;

struct Point
{
	int x;
	int y;

	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	Point()
	{
		x = -1;
		y = -1;
	}

	Point operator+(Point p)
	{
		return { p.x + x, p.y + y };
	}

	Point operator-(Point p)
	{
		return { x - p.x, y - p.y };
	}

	Point operator*(int integer)
	{
		return { x * integer, y * integer };
	}

	bool operator==(Point p)
	{
		return x == p.x && y == p.y;
	}
};

class BoardCell
{
private:
	Point m_Position;
	Piece* m_Occupant;
	Board* m_ParentBoard;

	Piece* m_Attackers[max_nb_of_attackers] = { nullptr };
	int m_NbOfAttackers = 0;

public:
	BoardCell();
	BoardCell(int index, Board* board);

	void Draw();

	inline Point GetPosition() { return m_Position; }
	inline Piece* GetOccupant() const { return m_Occupant; }
	inline bool IsOccupied() { return m_Occupant != nullptr; }

	inline Piece* const * GetAttackers() const { return m_Attackers; }
	inline void AddAttacker(Piece* attacker) { m_Attackers[m_NbOfAttackers++] = attacker; }
	void ResetAttackers();
	inline bool IsUnderAttack() { return m_NbOfAttackers != 0; }

	void RemovePiece(bool shouldKill = true);

	void AddPiece(Piece* piece);
};

