#pragma once

enum class ePieceType
{
	SQUARE,
	I,
	L,
	L_MIRRORED,
	N,
	N_MIRRORED,
	T
};

enum class eRotationType
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
};

extern const char G_PIECES[7 /* pieces */][4 /* rotations */][5 /* columns */][5 /* rows */];

extern const char G_PIECES_LIMIT[7 /* pieces */][4 /* rotations */][4 /* directions */][2 /* limits */];

class Piece
{
public:
	Piece(ePieceType pieceType);
	Piece(ePieceType pieceType, eRotationType rotationType);
	Piece(const Piece& other) = default;
	Piece& operator=(const Piece& other) = default;
	~Piece() = default;

	const ePieceType& GetPieceType() const;
	const eRotationType& GetRotationType() const;
	const char& GetBlock(unsigned char x, unsigned char y) const;
private:
	ePieceType mPieceType;
	eRotationType mRotationType;
	char mPiece[5][5];
};