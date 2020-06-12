#pragma once

#include <memory>

#include "Piece.h"

const int BOARD_WIDTH = 10;
const int BOARD_HEIGTH = 20;
const int BLOCK_SIZE = 16;

class Board
{
public:
	Board(const Board& other) = delete;
	Board& operator=(const Board& other) = delete;
	~Board();
	static Board* GetInstance();
	bool AddPiece(Piece*&& piece, unsigned char x, unsigned char y);
	bool IsGameOver() const;
	void DeleteLine(unsigned char line);
	void DeletePossibleLines();
	bool IsFreeBlock(unsigned char x, unsigned char y) const;
	bool IsPossibleMovement(ePieceType pieceType, eRotationType rotationType, unsigned char x, unsigned char y);
private:
	Board() {};
	static Board* mInstance;
	static Piece*** mBoard;
	static Piece* mFallingPiece;
};
