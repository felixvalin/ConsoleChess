#pragma once

#include <array>
#include <string>

#include "Board.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include "Pawn.h"

class GameManager;
class Piece;
class PieceState;

constexpr int max_nb_pieces = 16;

struct Move
{
	Point fromPoint;
	Point toPoint;

	Move()
	{
		fromPoint = Point(0, 0);
		toPoint = Point(0, 0);
	}
};

enum class PieceType
{
	Piece_Pawn,
	Piece_Rook,
	Piece_Bishop,
	Piece_Knight,
	Piece_Queen,
	Piece_King,
	Piece_NULL
};

class Player
{
private:
	// The pieces should be embedded in the player. Easier to save a state that way...
	Piece* m_Pieces[max_nb_pieces];
	int m_NbOfPieces;

	King* m_King;

	Board* m_Board;

	GameManager* m_Manager;

	Player* m_Opponent;

	std::string m_PlayerID;

	bool m_IsWhitePlayer;

public:
	Player();
	~Player();

	void Init(Board* board, Player* opponent, GameManager* manager, bool isWhitePlayer);
	void SetupBoard();

	void PreTurnSetup();
	void SetAllAttackedCells();

	bool MovePiece(Piece* piece, Point position);
	bool MakeMove(Move* moveToMake);

	inline bool IsWhitePlayer() const { return m_IsWhitePlayer; }
	inline std::string GetPlayerID() const { return m_PlayerID; }
	inline Player* GetOpponent() const { return m_Opponent; }

	inline Piece** GetPieces() { return m_Pieces; };
	void SetPieces(PieceState* states);
	inline int GetNbOfPieces() const { return m_NbOfPieces; }

	inline GameManager* GetGameManager() const { return m_Manager; }

	bool IsKingChecked() const;
	bool IsKingCheckMated();

	void PromotePawn(Pawn* pawn);

	void AddPiece(PieceType pieceType, Point position, int index = -1);
};

