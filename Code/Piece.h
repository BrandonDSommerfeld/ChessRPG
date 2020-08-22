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
		Distract,
		FindWeakness,
		PureSkill,
		Cripple,
		Demolition,
		Backstab,
		LastResort,
		RecklessSwing,
		PAWN_END,

		PrepareDefenses,
		BoilingOil,
		ArrowSalvo,
		PristineDefense,
		Caltrops,
		Pikemen,
		PerfectlyConstructed,
		NoxiousFumes,
		ThrowRock,
		FalseSurrender,
		ROOK_END,

		Charge,
		Duel,
		Infiltrate,
		SharpenSword,
		Slash,
		Amputate,
		AttackWeakness,
		Horsemanship,
		WildSwing,
		StudyOpponent,
		KNIGHT_END,

		Heal,
		Purge,
		Jericho,
		DarkCurse,
		ProfaneRitual,
		PrayToRNGesus,
		Smite,
		Excommunicate,
		HolyLight,
		BlindingLight,
		BISHOP_END,

		Guards,
		PawnGuards,
		RookGuards,
		KnightGuards,
		BishopGuards,
		CutthroatPolitics,
		QUEEN_END,

		ObliterateRook,
		ObliterateKnight,
		ObliterateBishop,
		ObliterateQueen,
		ObliteratePawn,
		ObliterateKing,
		KING_END,

		MAX_MOVES,
	};

	enum class Status
	{
		Cursed,
		Bleeding,
		Burning,

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
	bool m_reducingDamage{};
	bool m_addingDamage{};
	int m_statusTurns{};
	int m_dodgeChance{};
	int m_critChance{};
	int m_jerichoCount{};
public:

	static const int pieceHealth[6];

	Piece();
	Piece(Type type, Move move1, Move move2, Move move3, Move move4, bool isWhite);

	virtual bool neighbor(int crow, int ccol, int nrow, int ncol);

	AttackOutcome useMove(Piece& opponent, Move move);
	int getMaxHealth();
	int getCurrentHealth();

	Move getMove(int move);

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

	void setStatus(Status status);

	int getStatusTurns();

	void decrementStatusTurns();

	void setStatusTurns(int turns);

	void reset();

	std::string getName();


	friend bool operator== (const Piece& piece1, const Piece& piece2);

	friend bool operator != (const Piece& piece1, const Piece& piece2);
};

std::string getDescription(Piece::Move move);

std::string printMove(Piece::Move move);

std::string printStatus(Piece::Status status);

std::string printType(Piece::Type type);

int getRandomNumber(int min, int max);