/*
SUMMARY:
21 VERSION 6

TO DO
Make card picking truly random. [COMPLETED]
Allow bets. [COMPLETED]
Give the computer a range. [COMPLETED]
Maybe have things be in functions. [COMPLETED]
Have a game loop. [COMPLETED]
Implement a high-score system. [COMPLETED]
Remove unnesscary global variables. [COMPLETED]
A selection for aces. (Possibly a counter for aces) [COMPLETED, MIGHT NEED A FEW TWEAKS]
Finite deck. [Finished]
Loops to ensure that they can't input a invalid option. [COMPLETED]

Tidy up program.
Test program.

*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>




int Total = 0; //Total of the value of player cards.
int ComTotal = 0 ;  //Total of the value of computer's cards.
int Cash = 1000; //Overall Cash
int Bet; //The bet you put down
int ace_counter; //Number of aces in play, so that aces values can be 1 or 11.


int menu() //A starting menu for the game
{
    int choice;
    puts("Would you like to play 21?");
    puts("1. Yes");
    puts("2. No");
    printf("-> ");
    scanf("%d", &choice);
    return choice;
}



int DrawOrStick() //A Choice to allow someone to keep their cards or add one more.
{
    int DS;
    printf("1. Draw\n");
    printf("2. Stick\n");
    printf("-> ");
    scanf("%d", &DS);

    while ((DS > 2) || (DS < 0)){
        printf("INVALID OPTION\n");
        printf("1. Draw\n");
        printf("2. Stick\n");
        printf("-> ");
        scanf("%d", &DS);
    }

    return DS;

}

void Specific_Card(int card_index)//Displays the specific card.
{
    char*cards[52] = {"Ace of Spades", "Two of Spades", "Three of Spades",
                        "Four of Spades", "Five of Spades", "Six of Spades",
                        "Seven of Spades", "Eight of Spades", "Nine of Spades",
                        "Ten of Spades", "Jack of Spades", "Queen of Spades",
                        "King of Spades", "Ace of Clubs", "Two of Clubs",
                        "Three of Clubs", "Four of Clubs", "Five of Clubs",
                        "Six of Clubs", "Seven of Clubs", "Eight of Clubs",
                        "Nine of Clubs", "Ten of Clubs", "Jack of Clubs",
                        "Queen of Clubs", "King of Clubs", "Ace of Hearts",
                        "Two of Hearts", "Three of Hearts", "Four of Hearts",
                        "Five of Hearts", "Six of Hearts", "Seven of Hearts",
                        "Eight of Hearts", "Nine of Hearts", "Ten of Hearts",
                        "Jack of Hearts", "Queen of Hearts", "King of Hearts",
                        "Ace of Diamonds", "Two of Diamonds", "Three of Diamonds",
                        "Four of Diamonds", "Five of Diamonds", "Six of Diamonds",
                        "Seven of Diamonds", "Eight of Diamonds", "Nine of Diamonds",
                        "Ten of Diamonds", "Jack of Diamonds", "Queen of Diamonds", "King of Diamonds"};
    printf("%s\n", cards[card_index]);
}

int check_card(int card_index, int drawn_deck[52], int num_drawn_cards) //A function to check if the card is a duplicate or not.
{
    //int drawn_deck[52];
    //int num_drawn_cards;
    int card_drawn = 0;
    int counter = 0;

    while(counter < 52){
        if(card_index == drawn_deck[counter]){
          //  printf("DEBUG MODE \n");
          //  printf("Index=%d \t Drawn deck index=%d\n", card_index,counter);
         //   printf("Card is duplicate!\n");

            return 0; //False - card is duplicate!
        }
        counter++;
    }

   // printf("DEBUG MODE 2 \n");
   // printf("Index=%d \t Drawn deck index=%d\n", index,counter);
  // printf("Card is unique!\n");

    return 1; //True
}

int pick_card(int drawn_deck[52], int num_drawn_cards) //Function to pick a random card from our infinite deck
{

    int valuecards[52] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
                        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    int card_index;

    //Keep drawing until non duplicate card found
    int status = 0;
    while(status == 0){
        card_index = rand() % 52 ;
        status = check_card(card_index,drawn_deck,num_drawn_cards);
    }

    //Prints card name
    Specific_Card(card_index);

    drawn_deck[num_drawn_cards] = card_index;

    return valuecards[card_index];
}

void Draw(int drawn_deck[52], int num_drawn_cards) //Function of a player drawing a card beyond their two cards from the start.
{
    int nextcard;
    printf("The card you drawed was: \n");
    nextcard = pick_card(drawn_deck, num_drawn_cards);

    num_drawn_cards++;

    if ((nextcard == 1) && (ace_counter == 0)){
       ace_counter = ace_counter + 1;
       Total = Total + 10;
    }

    Total = Total + nextcard;

    if ((Total > 21) && (ace_counter == 1)){
        Total = Total - 10;
        ace_counter = ace_counter + 1;
    }

    printf("Your total is: %d\n", Total);
}

void ComDraw(int drawn_deck[52], int num_drawn_cards) //Function to allow Computer to draw cards
{
    int nextcard;
     printf("The card the computer drawed was: ");
    nextcard = pick_card(drawn_deck, num_drawn_cards);
    ComTotal = ComTotal + nextcard ;
    num_drawn_cards++;

    if ((nextcard == 1) && (ace_counter == 0)){
        ace_counter = ace_counter + 1;
        ComTotal = ComTotal + 10;
    }

    if ((ComTotal > 21) && (ace_counter == 1)){
        ComTotal = ComTotal - 10;
        ace_counter = ace_counter + 1;
    }

    printf("Computer's Total is: %d\n", ComTotal);
}

void start(int drawn_deck[52], int num_drawn_cards) //The function to start of a 21 game
{
    int card1;
    int card2;
    int ace_counter;
    printf("Your cash total currently is: %d\n", Cash);
    printf("How much do you want to bet?\n");
    printf("-> ");
    scanf("%d", &Bet);

    while ((Bet > Cash) || (Bet < 0)){

        if (Bet > Cash){
            printf("You can't bet more than what you have in your wallet.\n");
        }
        else if (Bet < 0){
            printf("You can't bet negative money.\n");
        }

        printf("Your cash total currently is: %d\n", Cash);
        printf("How much do you want to bet?\n");
        printf("-> ");

        scanf("%d", &Bet);
    }

    Cash = Cash - Bet ;

    puts("Your two cards are: ");
    card1 = pick_card(drawn_deck,num_drawn_cards);

    num_drawn_cards++;

    card2 = pick_card(drawn_deck,num_drawn_cards);
    num_drawn_cards++;

    Total = card1 + card2;

     if ((card1 == 1) && (ace_counter == 0)){
        ace_counter = ace_counter + 1;
        Total = Total + 10;
    }

    if ((card2 == 1) && (ace_counter == 0)){
        ace_counter = ace_counter + 1;
        Total = Total + 10;
    }
    printf("Your total is: %d\n", Total);
}

int GameLoop() //Function to allow the game to played over and over again without needing to open up the program every time.
{
    int GameLoopChoice;

    printf("Your cash total is: %d\n", Cash);

    printf("Would you like to play again?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("-> ");
    scanf("%d", &GameLoopChoice);

    while ((GameLoopChoice > 2) || (GameLoopChoice < 1))
{
    printf("INVALID OPTION\n");
    printf("Would you like to play again?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("-> ");
    scanf("%d", &GameLoopChoice);
}
return GameLoopChoice;
}

void GameEnd() //Function that ends the game along with showing/saving the highscore
{
    int line[255];
    printf("Your cash: %d\n", Cash);
    FILE * fpointer = fopen("highscore.txt", "r");
    int highscore = atoi(fgets(line, 255, fpointer));
    printf("HIGHSCORE = %d \n", highscore);

    if (Cash > highscore){
        printf("You've set a new highscore of %d !\n", Cash);
        fclose(fpointer);
        FILE * fpointer = fopen("highscore.txt", "w+");
        fprintf(fpointer, "%d", Cash);
        fclose(fpointer);
    }
    else
    {
        printf("The current highscore is: %d\n", highscore);
    }


        puts("------------------------------");
        puts("   THANK YOU FOR PLAYING 21   ");
        puts("------------------------------");
}





int main()
{
    int choice;
    int DS;
    int GameLoopChoice = 1;

    srand( time(NULL) );

    puts("-----------------------------");
    puts("        WELCOME TO 21        ");
    puts("-----------------------------");

    choice = menu();

    while ((choice > 2) || (choice < 1))
    {
        printf("INVALID OPTION\n");
        choice = menu();
    }

    switch(choice){

            case 1:

                while(GameLoopChoice == 1){
                    Total = 0;
                    ComTotal = 0;
                    Bet = 0;
                    ace_counter = 0;
                    int drawn_deck[52];
                    int num_drawn_cards = 0;

                    for (int i ; i = 0 ; i < 52){
                        drawn_deck[i] = 99; //A random number that doesn't exist in a pack of cards or in any of the other arrays. It will never be generated by card_index.
                        i++;
                    }

                    start(drawn_deck, num_drawn_cards);

                    DS = DrawOrStick();

                    //A loop where it keeps asking if you want to draw or stick until you go bust.

                    while(DS == 1){
                        Draw(drawn_deck, num_drawn_cards);

                        if (Total >= 22){

                            printf("BUST. You lose.\n");
                            break;

                        }
                        DS = DrawOrStick();
                    }

                    ace_counter = 0;

                    while((ComTotal < 19) && (Total < 22)){
                        ComDraw(drawn_deck, num_drawn_cards);
                    }

                    if(Total < 22){
                         if ((ComTotal > Total) && (ComTotal < 22)){
                            printf("You lose.\n");
                         }
                         else if (ComTotal == Total){
                            printf("It's a draw.\n");
                            Cash = Cash + Bet ;
                         }
                         else if (ComTotal > 21){
                            printf("The Computer Has Gone Bust. You win!\n");
                            Cash = Cash + (Bet * 2) ;
                         }
                         else {
                            printf("You win!\n");
                            Cash = Cash + (Bet * 2) ;
                         }
                    }

                    if(Cash <= 0){
                        printf("You've run out of funds.\n");
                        GameEnd();
                        break;
                    }

                    if(Cash > 0){
                        GameLoopChoice = GameLoop();
                    }
                }

        if(Cash > 0){
            GameEnd();
        }

        break;

        case 2:
            //printf("Debug mode");
            //printf("Card name : %s\n", cards[0]);
            //printf("Card Value: %d\n", valuecards[0]);
            puts("Exiting Program");
            break;

    }

        return 0;
}

