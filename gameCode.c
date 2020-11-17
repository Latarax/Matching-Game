#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// boolean functionality
typedef enum { false, true } bool;

// player prototype
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

// function prototypes
void printBoard(card cards[]);
int flipCard(card cards[], char cardToFlip[], int* flipPtr, player players[]);
int checkMatch(card cards[], char firstCard[], char secondCard[], int* flipPtr, player players[]);
void pointAllocation(card cards[], player players[]);


int main()
{
    // random number generator
    time_t t;    
    srand((unsigned) time(&t));
    
    // scanf(numPlayers);
    // player players[numPlayers];

    // initializing player count (player functionality not working at the moment)
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

    players[0].isTurn = true;

    // game loop
    while(numFlipped < 18) 
    {
        char firstCard[1];
        printf("Choose first card to flip (only first letter of input will be read): ");
        scanf("%s", firstCard);

        while(flipCard(cards, firstCard, flipPtr, players) == 1)
        {
            printf("Please choose a valid card from the board: \n");
            scanf("%s", firstCard);
        }

        printBoard(cards);

        char secondCard[1];
        printf("Choose second card to flip (only first letter of input will be read): ");
        scanf("%s", secondCard);

        while(flipCard(cards, secondCard, flipPtr, players) == 1)
        {
            printf("Please choose a valid card from the board: \n");
            scanf("%s", secondCard);
        }

        printf("\n\n");

        printBoard(cards);

        checkMatch(cards, firstCard, secondCard, flipPtr, players);
    }

    printf("GAME OVER!");

    // for (i = 0; i < 2; i++)
    // {
    //     printf("Player %d: %d\n", i+1, players[i].points);
    // }
    
    return 0;
}

// function to print current state of board. 3 for loops used for formatting
void printBoard(card cards[])
{
    printf("\nCurrent Game Board\n\n");
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
int flipCard(card cards[], char cardToFlip[], int* flipPtr, player players[])
{
    int i;
    for (i = 0; i < 18; i++)
    {
        if (cards[i].cardLetter == cardToFlip[0])
        {
            if (cards[i].isFlipped) {return 1;}
            cards[i].isFlipped = true;
            *flipPtr += 1;
            return 0;
        }
    }
    return 1;
}

// function that checks if flipped cards match. If not, cards will be flipped back and count is updated.
int checkMatch(card cards[], char firstCard[], char secondCard[], int* flipPtr, player players[])
{
    int i, firstIndex, secondIndex;

    for (i = 0; i < 18; i++)
    {
        if (cards[i].cardLetter == firstCard[0])
        {
            firstIndex = i;
        }
    }

    for (i = 0; i < 18; i++)
    {
        if (i == firstIndex) {continue;}

        if (cards[i].cardLetter == secondCard[0])
        {
            secondIndex = i;
        }
    }

    if (cards[firstIndex].cardFace == cards[secondIndex].cardFace)
    {
        cards[firstIndex].isMatched = true;
        cards[secondIndex].isMatched = true;
        printf("MATCH! Cards %c and %c matched with the symbol %c\n\n", cards[firstIndex].cardLetter, cards[secondIndex].cardLetter, cards[secondIndex].cardFace);            
        return 0;
    }
    else
    {
        cards[firstIndex].isFlipped = false;
        cards[secondIndex].isFlipped = false;
        *flipPtr -= 2;
        printf("NO MATCH! Next turn.\n\n");
    }
    
    
    return 1;
}

// function for allocating points to players
void pointAllocation(card cards[], player players[])
{
    if (players[0].isTurn)
    {
        players[0].points += 2;
    }
}