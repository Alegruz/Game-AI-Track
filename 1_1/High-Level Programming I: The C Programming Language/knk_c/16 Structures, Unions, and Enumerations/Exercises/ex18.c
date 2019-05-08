/* a */
typedef enum {
    EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
} Piece;

typedef enum {
    WHITE, BLACK
} Color;

/* b */
typedef struct {
    Piece piece;
    Color color;
} Square;

/* c d */
Square board[8][8] = {(Square) {ROOK, BLACK}, (Square) {KNIGHT, BLACK}, (Square) {BISHOP, BLACK}, {QUEEN, BLACK}, (Square) {KING, BLACK}, (Square) {BISHOP, BLACK}, (Square) {KNIGHT, BLACK}, (Square) {ROOK, BLACK},
                     (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK}, (Square) {PAWN, BLACK},
                     (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK},
                     (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK},
                     (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK},
                     (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK}, (Square) {EMPTY, BLACK},
                     (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE}, (Square) {PAWN, WHITE},
                     (Square) {ROOK, WHITE}, (Square) {KNIGHT, WHITE}, (Square) {BISHOP, WHITE}, {QUEEN, WHITE}, (Square) {KING, WHITE}, (Square) {BISHOP, WHITE}, (Square) {KNIGHT, WHITE}, (Square) {ROOK, WHITE}};
