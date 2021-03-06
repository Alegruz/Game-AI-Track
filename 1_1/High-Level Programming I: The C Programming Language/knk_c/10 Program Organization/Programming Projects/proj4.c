/* Classifies a poker hand */

#include <stdbool.h>    /* C99 only */
#include <stdio.h>
#include <stdlib.h>

#define NUM_RANKS 13
#define NUM_SUITS 4
#define NUM_CARDS 5

/* external variables */
bool royal, straight, flush, four, three;
int pairs;  /* can be 0, 1, or 2 */

/* prototypes */
void read_cards(int [][2]);
void analyze_hand(int [][2]);
void print_result(void);
void quicksort(int [][2], int, int);
int split(int [][2], int, int);

/**********************************************************
 * main: Calls read_cards, analyze_hand, and print_result *
 *       repeatedly.                                      *
 **********************************************************/
int main(void) {
    int hand[NUM_CARDS][2] = {{}};

    for (;;) {
        read_cards(hand);
        analyze_hand(hand);
        print_result();
    }
}

/**********************************************************
 * read_cards: Reads the cards into the external          *
 *             variables num_in_rank and num_in_suit;     *
 *             checks for bad cards and duplicate cards.  *
 **********************************************************/
void read_cards(int hand[][2]) {
    char ch, rank_ch, suit_ch;
    int rank, suit;
    bool bad_card, card_exists = false;
    int cards_read = 0;

    while (cards_read < NUM_CARDS) {
        bad_card = false;
        card_exists = false;

        printf("Enter a card: ");

        rank_ch = getchar();
        switch (rank_ch) {
        case '0':           exit(EXIT_SUCCESS);
        case '2':           rank = 0; break;
        case '3':           rank = 1; break;
        case '4':           rank = 2; break;
        case '5':           rank = 3; break;
        case '6':           rank = 4; break;
        case '7':           rank = 5; break;
        case '8':           rank = 6; break;
        case '9':           rank = 7; break;
        case 't': case 'T': rank = 8; break;
        case 'j': case 'J': rank = 9; break;
        case 'q': case 'Q': rank = 10; break;
        case 'k': case 'K': rank = 11; break;
        case 'a': case 'A': rank = 12; break;
        default:            bad_card = true;
        }

        suit_ch = getchar();
        switch (suit_ch) {
        case 'c': case 'C': suit = 0; break;
        case 'd': case 'D': suit = 1; break;
        case 'h': case 'H': suit = 2; break;
        case 's': case 'S': suit = 3; break;
        default:            bad_card = true;
        }

        while ((ch = getchar()) != '\n')
            if (ch != ' ') bad_card = true;

        if (!bad_card)
            for (int card = 0; card < cards_read; ++card) {
                if (hand[card][0] == rank && hand[card][1] == suit)
                    card_exists = true;
            }

        if (bad_card)
            printf("Bad card; ignored.\n");
        else if (card_exists)
            printf("Duplicate card; ignored.\n");
        else {
            hand[cards_read][0] = rank;
            hand[cards_read][1] = suit;
            cards_read++;
        }
    }
}

/**********************************************************
 * analyze_hand: Determines whether the hand contains a   *
 *               straight, a flush, four-of-a-kind,       *
 *               and/or three-of-a-kind; determines the   *
 *               number of pairs; stores the results into *
 *               the external variables straight, flush,  *
 *               four, three, and pairs.                  *
 **********************************************************/
void analyze_hand(int hand[][2]) {
    royal = false;
    straight = false;
    flush = false;
    four = false;
    three = false;
    pairs = 0;

    quicksort(hand, 0, NUM_CARDS - 1);

    /* check for flush */
    int num_same_suit = 1;
    for (int card = 0; card < NUM_CARDS - 1 && (hand[card][1] == hand[card + 1][1]); ++card)
        num_same_suit++;
    if (num_same_suit == NUM_CARDS)
        flush = true;

    /* check for straight */
    int num_consec = 1;
    for(int card = 0; card < NUM_RANKS - 1 && hand[card + 1][0] - hand[card][0] == 1; card++)
        num_consec++;
    if (num_consec == NUM_CARDS) {
        straight = true;
        if (hand[0][0] == 8)
            royal = true;
        return;
    }

    /* check for 4-of-a-kind, 3-of-a-kind, and pairs */
    int times[5] = {};
    int index = 0;
    for (int card = 0; card < NUM_CARDS - 1; card++) {
        if (hand[card][0] == hand[card + 1][0]) {
            times[index]++;
        } else {
            index++;
        }
    }

    for (int i = 0; i < index; ++i) {
        if (times[i] == 2)
            pairs++;
        if (times[i] == 3)
            three = true;
        if (times[i] == 4)
            four = true;
    }
}

/**********************************************************
 * print_result: Prints the classification of the hand,   *
 *               based on the values of the external      *
 *               variables straight, flush, four, three,  *
 *               and pairs.                               *
 **********************************************************/
void print_result(void) {
    if (royal && flush)         printf("Royal flush");
    else if (straight && flush) printf("Straight flush");
    else if (four)              printf("Four of a kind");
    else if (three &&
             pairs == 1)        printf("Full house");
    else if (flush)             printf("Flush");
    else if (straight)          printf("Straight");
    else if (three)             printf("Three of a kind");
    else if (pairs == 2)        printf("Tow pairs");
    else if (pairs == 1)        printf("Pair");
    else                        printf("High card");

    printf("\n\n");
}

void quicksort(int hand[][2], int low, int high) {
    int middle;

    if (low >= high) return;
    middle = split(hand, low, high);
    quicksort(hand, low, middle - 1);
    quicksort(hand, middle + 1, high);
}

int split(int hand[][2], int low, int high) {
    int part_element = hand[low][0];
    int part_suit = hand[low][1];

    for (;;) {
        while (low < high && part_element <= hand[high][0])
            high--;
        if (low >= high) break;
        hand[low][0] = hand[high][0];
        hand[low++][1] = hand[high][1];

        while (low < high && hand[low][0] <= part_element)
            low++;
        if (low >= high) break;
        hand[high][0] = hand[low][0];
        hand[high--][1] = hand[low][1];
    }

    hand[low][0] = part_element;
    hand[low][1] = part_suit;
    return high;
}
