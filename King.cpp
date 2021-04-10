#include "DEBUG.h"
#include <iostream>

#include "King.h"
#include "Rook.h"

King::King(Point position, Player* player)
	: Piece(position, player), HasMoved()
{
	SetPieceID('k');
	m_NbOfDirections = 8;
	m_Directions = new Point[m_NbOfDirections];
	m_Directions[0] = Point(1, 0);
	m_Directions[1] = Point(-1, 0);
	m_Directions[2] = Point(0, 1);
	m_Directions[3] = Point(0, -1);
	m_Directions[4] = Point(1, 1);
	m_Directions[5] = Point(-1, 1);
	m_Directions[6] = Point(1, -1);
	m_Directions[7] = Point(-1, -1);

	if (DEBUG)
		std::cout << typeid(this).name() << " has been created! " << std::endl;
}

void King::CheckPossibleMoves()
{
	Piece::CheckPossibleMoves();

	// Check for Castling
	CheckCastleMoves();
}

void King::CheckCastleMoves()
{
	int castleSide = 1;

	if (!GetHasMoved())
	{
		do
		{
			Point castleDirection = Point(castleSide, 0);
			for (Point currentPos = GetPosition() + castleDirection; !Board::IsOutOfBoard(currentPos); currentPos = currentPos + castleDirection)
			{
				BoardCell* currentCell = m_Board->GetBoardCell(currentPos);
				if (currentCell->IsOccupied())
				{
					if (Rook* rook = dynamic_cast<Rook*>(currentCell->GetOccupant()))
					{
						if (!rook->GetHasMoved())
						{
							m_PossibleMoves[m_PossibleMovesIndex] = GetPosition() + castleDirection*2;
							m_PossibleMovesIndex++;
						}
					}
					break;
				}
			}
			castleSide *= -1;
		} while (castleSide != 1);
	}
}

void King::Move(BoardCell* moveFrom, BoardCell* moveTo)
{
	Piece::Move(moveFrom, moveTo);

	if (IsCastleMove(moveFrom, moveTo))
	{
		Point horizontalCellDirection = Point(1, 0);

		if (GetPosition().x == 6)
		{
			BoardCell* kingRookCell = m_Board->GetBoardCell(GetPosition() + horizontalCellDirection);
			BoardCell* castledRookCell = m_Board->GetBoardCell(GetPosition() + horizontalCellDirection*-1);
			kingRookCell->GetOccupant()->Move(kingRookCell, castledRookCell);
		}
		else
		{
			BoardCell* queenRookCell = m_Board->GetBoardCell(GetPosition() + horizontalCellDirection*-2);
			BoardCell* castledRookCell = m_Board->GetBoardCell(GetPosition() + horizontalCellDirection);
			queenRookCell->GetOccupant()->Move(queenRookCell, castledRookCell);
		}
	}

	// For castling
	CheckFirstMove();
}

bool King::IsCastleMove(BoardCell* moveFrom, BoardCell* moveTo)
{
	int movementDistance = moveFrom->GetPosition().x - moveTo->GetPosition().x;
	return movementDistance == 2 || movementDistance == -2;
}

bool King::IsChecked() const
{
	return m_Board->GetBoardCell(GetPosition())->IsUnderAttack();
}