#include <fstream>
#include <cstdlib>
#include "Piece.h"
#include "Grid.h"
#include <iostream>


Piece Grid::noPiece{};

Grid::Grid()
	:
	board{}
{
	board[0][0] = Piece{ Piece::Type::Rook, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Rook)],  false };
	board[0][1] = Piece{ Piece::Type::Knight, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Knight)],  false };
	board[0][2] = Piece{ Piece::Type::Bishop, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Bishop)],  false };
	board[0][3] = Piece{ Piece::Type::King, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::King)],  false };
	board[0][4] = Piece{ Piece::Type::Queen, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Queen)],  false };
	board[0][5] = Piece{ Piece::Type::Bishop, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Bishop)],  false };
	board[0][6] = Piece{ Piece::Type::Knight, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Knight)],  false };
	board[0][7] = Piece{ Piece::Type::Rook, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Rook)],  false };

	for (int c{ 0 }; c < 8; ++c)
	{
		board[1][c] = Piece{ Piece::Type::Pawn, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Pawn)],  false };
	}
	for (int r{ 2 }; r < 6; ++r)
	{
		for (int c{ 0 }; c < 8; ++c)
		{
			board[r][c] = Piece{};
		}
	}
	for (int c{ 0 }; c < 8; ++c)
	{
		board[6][c] = Piece{ Piece::Type::Pawn, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Pawn)],  true };
	}

	board[7][0] = Piece{ Piece::Type::Rook, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Rook)],  true };
	board[7][1] = Piece{ Piece::Type::Knight, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Knight)],  true };
	board[7][2] = Piece{ Piece::Type::Bishop, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Bishop)],  true };
	board[7][3] = Piece{ Piece::Type::King, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::King)],  true };
	board[7][4] = Piece{ Piece::Type::Queen, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Queen)],  true };
	board[7][5] = Piece{ Piece::Type::Bishop, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Bishop)],  true };
	board[7][6] = Piece{ Piece::Type::Knight, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Knight)],  true };
	board[7][7] = Piece{ Piece::Type::Rook, static_cast<Piece::Move>(0), static_cast<Piece::Move>(1) , static_cast<Piece::Move>(2) , static_cast<Piece::Move>(3), Piece::pieceHealth[static_cast<int>(Piece::Type::Rook)],  true };

	//Need proper constructors
}

Grid::Grid(Loadout loadout)
	:
	board{}
{

}
Grid::Grid(Loadout loadout1, Loadout loadout2)
	:
	board{}
{

}

Piece& Grid::getPiece(int row, int col)
{
	return board[row][col];
}

void Grid::addPiece(Piece& p, int row, int col)
{
	board[row][col] = p;
}

void Grid::removePiece(int crow, int ccol)
{
	board[crow][ccol] = noPiece;
}


//Only call once battle is finished
void Grid::movePiece(int crow, int ccol, int nrow, int ncol)
{
	board[nrow][ncol] = board[crow][ccol];
	board[crow][ccol] = noPiece;
	board[nrow][ncol].moved();
	if (board[nrow][ncol].getType() == Piece::Type::King && ccol - ncol == 2)
	{
		//Left castle
		//Rook moves 2
		board[crow][2] = board[crow][0];
		board[crow][0] = noPiece;
		board[crow][2].moved();
		return;
	}
	if (board[nrow][ncol].getType() == Piece::Type::King && ncol - ccol == 2)
	{
		//Right castle
		//Rook moves 3
		board[crow][4] = board[crow][7];
		board[crow][7] = noPiece;
		board[crow][4].moved();
		return;
	}
	
}

std::array<std::array<bool, 8>, 8> Grid::reachable(int row, int col)
{
	std::array<std::array<bool, 8>, 8> ans{};

	for (int i{ 0 }; i < 8; ++i)
	{
		for (int j{ 0 }; j < 8; ++j)
		{
			ans[i][j] = false;
		}
	}
	switch (board[row][col].getType())
	{
	case Piece::Type::Pawn:
		if (board[row][col].isWhite())
		{
			if (row > 0 && board[row - 1][col] == noPiece)
			{
				ans[row - 1][col] = true;
				if (row == 6 && board[4][col] == noPiece)
				{
					ans[4][col] = true;
				}
			}
			if (row > 0 && col > 0 && board[row - 1][col - 1] != noPiece && !board[row - 1][col - 1].isWhite())
			{
				ans[row - 1][col - 1] = true;
			}
			if (row > 0 && col < 7 && board[row - 1][col + 1] != noPiece && !board[row - 1][col + 1].isWhite())
			{
				ans[row - 1][col + 1] = true;
			}
		}
		else
		{
			if (row < 7 && board[row + 1][col] == noPiece)
			{
				ans[row + 1][col] = true;
				if (row == 1 && board[3][col] == noPiece)
				{
					ans[3][col] = true;
				}
			}
			if (row < 7 && col > 0 && board[row + 1][col - 1] != noPiece && board[row + 1][col - 1].isWhite())
			{
				ans[row + 1][col - 1] = true;
			}
			if (row < 7 && col < 7 && board[row + 1][col + 1] != noPiece && board[row + 1][col + 1].isWhite())
			{
				ans[row + 1][col + 1] = true;
			}
		}
		break;

	case Piece::Type::Rook:

		for (int r{ row - 1 }; r >= 0; --r)
		{
			if (board[r][col] == noPiece)
			{
				ans[r][col] = true;
			}
			else if (board[row][col].isWhite() == board[r][col].isWhite())
			{
				break;
			}
			else
			{
				ans[r][col] = true;
				break;
			}
		}
		for (int r{ row + 1 }; r < 8; ++r)
		{
			if (board[r][col] == noPiece)
			{
				ans[r][col] = true;
			}
			else if (board[row][col].isWhite() == board[r][col].isWhite())
			{
				break;
			}
			else
			{
				ans[r][col] = true;
				break;
			}
		}
		for (int c{ col - 1 }; c >= 0; --c)
		{
			if (board[row][c] == noPiece)
			{
				ans[row][c] = true;
			}
			else if (board[row][col].isWhite() == board[row][c].isWhite())
			{
				break;
			}
			else
			{
				ans[row][c] = true;
				break;
			}
		}
		for (int c{ col + 1 }; c < 8; ++c)
		{
			if (board[row][c] == noPiece)
			{
				ans[row][c] = true;
			}
			else if (board[row][col].isWhite() == board[row][c].isWhite())
			{
				break;
			}
			else
			{
				ans[row][c] = true;
				break;
			}
		}

		break;

	case Piece::Type::Bishop:
		for (int i{ 1 }; row + i < 8 && col + i < 8; ++i)
		{
			if (board[row + i][col + i] == noPiece)
			{
				ans[row + i][col + i] = true;
			}
			else if (board[row + i][col + i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row + i][col + i] = true;
				break;
			}
		}
		for (int i{ 1 }; row - i >= 0 && col - i >= 0; ++i)
		{
			if (board[row - i][col - i] == noPiece)
			{
				ans[row - i][col - i] = true;
			}
			else if (board[row - i][col - i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row - i][col - i] = true;
				break;
			}
		}
		for (int i{ 1 }; row - i >= 0 && col + i < 8; ++i)
		{
			if (board[row - i][col + i] == noPiece)
			{
				ans[row - i][col + i] = true;
			}
			else if (board[row - i][col + i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row - i][col + i] = true;
				break;
			}
		}
		for (int i{ 1 }; row + i < 8 && col - i >= 0; ++i)
		{
			if (board[row + i][col - i] == noPiece)
			{
				ans[row + i][col - i] = true;
			}
			else if (board[row + i][col - i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row + i][col - i] = true;
				break;
			}
		}
		break;

	case Piece::Type::Knight:
		if (row + 2 < 8 && col + 1 < 8 && (board[row + 2][col + 1] == noPiece || board[row + 2][col + 1].isWhite() != board[row][col].isWhite()))
		{
			ans[row + 2][col + 1] = true;
		}
		if (row + 1 < 8 && col + 2 < 8 && (board[row + 1][col + 2] == noPiece || board[row + 1][col + 2].isWhite() != board[row][col].isWhite()))
		{
			ans[row + 1][col + 2] = true;
		}
		if (row + 2 < 8 && col - 1 >= 0 && (board[row + 2][col - 1] == noPiece || board[row + 2][col - 1].isWhite() != board[row][col].isWhite()))
		{
			ans[row + 2][col - 1] = true;
		}
		if (row + 1 < 8 && col - 2 >= 0 && (board[row + 1][col - 2] == noPiece || board[row + 1][col - 2].isWhite() != board[row][col].isWhite()))
		{
			ans[row + 1][col - 2] = true;
		}
		if (row - 2 >= 0 && col + 1 < 8 && (board[row - 2][col + 1] == noPiece || board[row - 2][col + 1].isWhite() != board[row][col].isWhite()))
		{
			ans[row - 2][col + 1] = true;
		}
		if (row - 1 >= 0 && col + 2 < 8 && (board[row - 1][col + 2] == noPiece || board[row - 1][col + 2].isWhite() != board[row][col].isWhite()))
		{
			ans[row - 1][col + 2] = true;
		}
		if (row - 2 >= 0 && col - 1 >= 0 && (board[row - 2][col - 1] == noPiece || board[row - 2][col - 1].isWhite() != board[row][col].isWhite()))
		{
			ans[row - 2][col - 1] = true;
		}
		if (row - 1 >= 0 && col - 2 >= 0 && (board[row - 1][col - 2] == noPiece || board[row - 1][col - 2].isWhite() != board[row][col].isWhite()))
		{
			ans[row - 1][col - 2] = true;
		}
		break;

	case Piece::Type::Queen:
		for (int r{ row - 1 }; r >= 0; --r)
		{
			if (board[r][col] == noPiece)
			{
				ans[r][col] = true;
			}
			else if (board[row][col].isWhite() == board[r][col].isWhite())
			{
				break;
			}
			else
			{
				ans[r][col] = true;
				break;
			}
		}
		for (int r{ row + 1 }; r < 8; ++r)
		{
			if (board[r][col] == noPiece)
			{
				ans[r][col] = true;
			}
			else if (board[row][col].isWhite() == board[r][col].isWhite())
			{
				break;
			}
			else
			{
				ans[r][col] = true;
				break;
			}
		}
		for (int c{ col - 1 }; c >= 0; --c)
		{
			if (board[row][c] == noPiece)
			{
				ans[row][c] = true;
			}
			else if (board[row][col].isWhite() == board[row][c].isWhite())
			{
				break;
			}
			else
			{
				ans[row][c] = true;
				break;
			}
		}
		for (int c{ col + 1 }; c < 8; ++c)
		{
			if (board[row][c] == noPiece)
			{
				ans[row][c] = true;
			}
			else if (board[row][col].isWhite() == board[row][c].isWhite())
			{
				break;
			}
			else
			{
				ans[row][c] = true;
				break;
			}
		}
		for (int i{ 1 }; row + i < 8 && col + i < 8; ++i)
		{
			if (board[row + i][col + i] == noPiece)
			{
				ans[row + i][col + i] = true;
			}
			else if (board[row + i][col + i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row + i][col + i] = true;
				break;
			}
		}
		for (int i{ 1 }; row - i >= 0 && col - i >= 0; ++i)
		{
			if (board[row - i][col - i] == noPiece)
			{
				ans[row - i][col - i] = true;
			}
			else if (board[row - i][col - i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row - i][col - i] = true;
				break;
			}
		}
		for (int i{ 1 }; row - i >= 0 && col + i < 8; ++i)
		{
			if (board[row - i][col + i] == noPiece)
			{
				ans[row - i][col + i] = true;
			}
			else if (board[row - i][col + i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row - i][col + i] = true;
				break;
			}
		}
		for (int i{ 1 }; row + i < 8 && col - i >= 0; ++i)
		{
			if (board[row + i][col - i] == noPiece)
			{
				ans[row + i][col - i] = true;
			}
			else if (board[row + i][col - i].isWhite() == board[row][col].isWhite())
			{
				break;
			}
			else
			{
				ans[row + i][col - i] = true;
				break;
			}
		}
		break;

	case Piece::Type::King:
		for (int i{ -1 }; i < 2; ++i)
		{
			if (row + i >= 0  && row + i < 8 && col - 1 >= 0 && (board[row + i][col - 1] == noPiece || board[row + i][col - 1].isWhite() != board[row][col].isWhite()))
			{
				ans[row + i][col - 1] = true;
			}
			if (row + i >= 0 && row + i < 8 && col + 1 < 8 && (board[row + i][col + 1] == noPiece || board[row + i][col + 1].isWhite() != board[row][col].isWhite()))
			{
				ans[row + i][col + 1] = true;
			}
		}
		if (row + 1 < 8 && (board[row + 1][col] == noPiece || board[row + 1][col].isWhite() != board[row][col].isWhite()))
		{
			ans[row + 1][col] = true;
		}
		if (row - 1 >= 0 && (board[row - 1][col] == noPiece || board[row - 1][col].isWhite() != board[row][col].isWhite()))
		{
			ans[row - 1][col] = true;
		}


		//Castle
		if (board[row][col].isWhite())
		{
			if (!board[row][col].hasMoved() && !board[7][0].hasMoved())
			{
				if (board[7][1] == noPiece && board[7][2] == noPiece)
				{
					ans[7][1] = true;
				}
			}
			if (!board[row][col].hasMoved() && !board[7][7].hasMoved())
			{
				if (board[7][4] == noPiece && board[7][5] == noPiece && board[7][6] == noPiece)
				{
					ans[7][5] = true;
				}
			}
		}
		else
		{
			if (!board[row][col].hasMoved() && !board[0][0].hasMoved())
			{
				if (board[0][1] == noPiece && board[0][2] == noPiece)
				{
					ans[0][1] = true;
				}
			}
			if (!board[row][col].hasMoved() && !board[0][7].hasMoved())
			{
				if (board[0][4] == noPiece && board[0][5] == noPiece && board[0][6] == noPiece)
				{
					ans[0][5] = true;
				}
			}
		}
		break;
	}

	return ans;
}