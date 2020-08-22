#pragma once

#include <fstream>
#include <array>
#include "Piece.h"


struct Loadout
{
	//First 4 are pawn, then rook, then knight, then bishop, then queen, then king
	//Set aside certain ranges in Piece::Move for certain pieces?
	//Make a Piece::Move::RookStart
	Piece::Move moves[24];
};

class Grid
{
private:
	

	Piece board[8][8];

public:
	static Piece noPiece;
	Grid();
	Grid(Loadout loadout1, Loadout loadout2);

	Piece& getPiece(int row, int col);

	void addPiece(Piece& p, int row, int col);

	void movePiece(int crow, int ccol, int nrow, int ncol);

	void removePiece(int crow, int ccol);

	std::array<std::array<bool, 8>, 8> reachable(int row, int col);
};

