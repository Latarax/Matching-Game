#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum { false, true } bool;

struct players_struct
{
    int playerID;
    int points;
    bool isTurn;
};

typedef struct players_struct player;

// card prototype with necessary attributes
struct cards_struct
{
    char cardLetter;
    char cardFace;
    int location;
    bool isFlipped;
    bool isMatched;
} card_default = {'z', 't', 0, false, false}; // arbitrary default values for error checking

typedef struct cards_struct card;

void printBoard(card cards[]);
int flipCard(card cards[], char cardToFlip[], int* flipPtr);
int checkMatch(card cards[], int flipIndex);


int main()
{
    // random number generator
    time_t t;    
    srand((unsigned) time(&t));
    
    printf("Two players (for now, will update)\n");
    // scanf(numPlayers);
    // player players[numPlayers];

    player players[2];

    int i;
    for (i = 0; i < 2; i++)
    {
        players[i].playerID = i;
        players[i].points = 0;
        players[i].isTurn = false;
    }
    
    // array of cards, and count of flipped cards
    card cards[18];
    int numFlipped = 0;
    int *flipPtr = &numFlipped;

    // symbols to be randomly assigned to cards
    char symbols[] = {'=', '&', '?', '#', '!', '}', '@', '%', '*', 
                      '=', '&', '?', '#', '!', '}', '@', '%', '*'};
    
    // iteration variables
    char x;
    int symbolIndex;
    int y = 0;
    
    // initialize cards, assign letter and symbol to each card 
    for (x = 'a'; x != 's'; x++)
    {
        cards[y] = card_default;
        cards[y].cardLetter = x;
        
        // choosing random symbol from array and assigning to card
        do {
            symbolIndex = (rand() % 18);
        } while (symbols[symbolIndex] == '/'); // '/' used as indicator for symbol that has been used already

        cards[y].cardFace = symbols[symbolIndex];
        symbols[symbolIndex] = '/';
        cards[y].location = y;
        y++;
    }

    printBoard(cards);

    while(numFlipped < 18) 
    {
        char firstCard[1];
        printf("Choose first card to flip: ");
        scanf("%s", firstCard);

        while(flipCard(cards, firstCard, flipPtr) == 1)
        {
            printf("Please choose a valid card from the board: ");
            scanf("%s", firstCard);
        }

        char secondCard[1];
        printf("Choose second card to flip: ");
        scanf("%s", secondCard);

        while(flipCard(cards, secondCard, flipPtr) == 1)
        {
            printf("Please choose a valid card from the board: ");
            scanf("%s", secondCard);
        }

        printf("\n\n");

        printBoard(cards);
    }

    printf("GAME OVER!");
    
    return 0;
}

// function to print current state of board
void printBoard(card cards[])
{
    printf("Current Game Board\n\n");
    char x;
    int y = 0;
    for (x = 'a'; x != 'g'; x++)
    {
        if (cards[y].isMatched) 
        {
            printf(" \t");
            y++;
            continue;
        }
        if (cards[y].isFlipped) {printf("%c\t", cards[y].cardFace);}
        else {printf("%c\t", cards[y].cardLetter);} 
        y++;
    }

    printf("\n\n");

    for (x = 'g'; x != 'm'; x++)
    {   
        if (cards[y].isMatched) 
        {
            printf(" \t");
            y++;
            continue;
        }
        if (cards[y].isFlipped) {printf("%c\t", cards[y].cardFace);}
        else {printf("%c\t", cards[y].cardLetter);}
        y++;
    }

    printf("\n\n");

    for (x = 'm'; x != 's'; x++)
    {
        if (cards[y].isMatched) 
        {
            printf(" \t");
            y++;
            continue;
        }
        if (cards[y].isFlipped) {printf("%c\t", cards[y].cardFace);}
        else {printf("%c\t", cards[y].cardLetter);}
        y++;
    }

    printf("\n\n");
}

// function that flips card and updates count of flipped cards
int flipCard(card cards[], char cardToFlip[], int* flipPtr)
{
    int i;
    for (i = 0; i < 18; i++)
    {
        if (cards[i].cardLetter == cardToFlip[0])
        {
            if (cards[i].isFlipped) {return 1;}
            cards[i].isFlipped = true;
            checkMatch(cards, i);
            //cards[i].cardLetter = cards[i].cardFace;
            *flipPtr += 1;
            return 0;
        }
    }
    return 1;
}

int checkMatch(card cards[], int flipIndex)
{
    int i;
    for (i = 0; i < 18; i++)
    {
        if (i == flipIndex) {continue;}

        if (cards[i].cardFace == cards[flipIndex].cardFace && cards[i].isFlipped && cards[flipIndex].isFlipped)
        {
            cards[i].isMatched = true;
            cards[flipIndex].isMatched = true;

            printf("MATCH! Cards %c and %c matched with the symbol %c\n", cards[i].cardLetter, cards[flipIndex].cardLetter, cards[flipIndex].cardFace);
            return 0;
        }
    }
    return 1;
}