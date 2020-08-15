#pragma once

#include <cstdlib>
#include <string>

class Piece
{


public:

	enum class Type
	{
		Pawn,
		Rook,
		Knight,
		Bishop,
		Queen,
		King,

		MAX_PIECES
	};
	enum class Move
	{
		Bash,
		Slice,
		Extra,
		Move,
		MAX_MOVES,

		//King moves will be "Destroy pawn, take 1/3 of max health damage", one for each type
		//Set dividing moves like PAWN_END
	};

	enum class Status
	{
		Poisoned,
		Bleeding,


		MAX_STATUSES
	};

	enum class AttackOutcome
	{
		Success,
		Miss,
		Super_Effective,

		MAX_OUTCOMES,
	};

private:

	Status m_status{};
	Type m_type{};
	Move m_moves[4]{};
	int m_maxHealth{};
	int m_currentHealth{};
	bool m_isWhite{};
	bool m_isNoPiece{};
	bool m_hasMoved{};
	bool m_usingSpecial{};
public:

	static const int pieceHealth[6];
	//Need to really update constructors
	Piece();
	Piece(Type type, Move move1, Move move2, Move move3, Move move4, int health, bool isWhite);

	virtual bool neighbor(int crow, int ccol, int nrow, int ncol);

	//Int gives code, miss/super effective/whatever
	AttackOutcome useMove(Piece& opponent, Move move);
	int getMaxHealth();
	int getCurrentHealth();

	Move getMove1();
	Move getMove2();
	Move getMove3();
	Move getMove4();

	Status getStatus();

	Type getType();

	bool isWhite();

	bool hasMoved();

	void moved();

	bool isUsingSpecial();

	bool isDead();

	void dealDamage(int amount);

	void allowMovement();

	void useSpecial();


	friend bool operator== (const Piece& piece1, const Piece& piece2);

	friend bool operator != (const Piece& piece1, const Piece& piece2);
};

std::string getDescription(Piece::Move move);

std::string printMove(Piece::Move move);

std::string printStatus(Piece::Status status);

int getRandomNumber(int min, int max);