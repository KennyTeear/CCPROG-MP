/* Name: Chan, Kendrick Martin C.
Date Last Modified: June 12, 2022
Sources: Lessons, https://www.javatpoint.com/random-function-in-c, https://www.johnslots.com/en/blackjack/rules/
*/
// Global variable
int gameover = 0;

// include stuff
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// colors 
void red () //change text to red
{
  printf ("\033[1;31m");
}

void yellow () //change text to yellow
{
  printf ("\033[1;33m");
}

void cyan () //change text to cyan
{
  printf ("\033[0;36m");
}

void green () //change text to green
{
  printf ("\033[0;32m");
}

void blue () //change text to blue
{
  printf ("\033[0;34m");
}

void reset () // change back to white
{
  printf ("\033[0m");
}


// Function Prototypes
void startscreen ();
char gamescreen ();
int getSymbol ();
int getCard (int playertotal);
int currentMoney ();
void gameend (int bank);
int LuckTester ();
int SimpleMath ();

// void betting (int bank, int money_bet); cancelled function 

// main function
int
main ()
{
  int total1, total2, playertotal, a, money_bet, hit, comhit;
  int playerwin = 0, bank, extrabank;
  int total3, total4, computertotal;
  char Nickname[20];
  srand (time (NULL));
  yellow();
  printf ("Enter your nickname: ");
  reset();
  scanf (" %s", Nickname);
  red();
  printf ("Welcome %s ,to the World of Games!\n", Nickname);
  reset();
  startscreen ();
  printf ("How much would you convert into chips? : ");	// money to chips 
  scanf ("%d", &bank);
  red();
  printf ("Chips converted: %d\n", bank);


  while (!gameover)
    {
      green();
      printf ("How much would you bet: ");
      scanf ("%d", &money_bet);

      // for player
      blue();
      printf ("Starting deck: \n");
      total1 = getCard (playertotal);
      getSymbol ();
      total2 = getCard (playertotal);
      getSymbol ();
      reset();
      
      // for computer
      red();
      printf ("Computer's deck: \n");
      total3 = getCard (playertotal);
      getSymbol ();
      total4 = getCard (playertotal);
      getSymbol ();
      playerwin = 0;
      reset();
      
      //   betting (money_bet);
      extrabank = bank - money_bet;	// Just to show how much you bet
      printf ("Current Chips : %d \n", extrabank);
      playertotal = total1 + total2;
      printf ("Current Deck: %d\n", playertotal);

      computertotal = total3 + total4;
      printf ("Computer's Deck: %d\n", computertotal);
      while (computertotal <= 14)
	{
	  printf ("Computer draw: \n");
	  comhit = getCard (computertotal);
	  getSymbol ();
	  computertotal = computertotal + comhit;
	  printf ("Computer's Deck: %d\n", computertotal);
	  if (computertotal > 21)
	    {
	      printf ("computer card is over 21\n");
	      playerwin = 1;
	      bank = bank + money_bet;
	    }
	}
      while (playerwin == 0)
	{
	  a = gamescreen ();
	  switch (a)
	    {
	    case 'H':		// Hit
	    case 'h':
	      printf ("Card Drawn :");
	      hit = getCard (playertotal);
	      getSymbol ();
	      playertotal = playertotal + hit;
	      printf ("Current Card: %d\n", playertotal);
	      break;
	    case 'S':		// Stand
	    case 's':
	      // compare with computer card
	      if (playertotal > computertotal)
		{
		  playerwin = 1;
		  printf (" Your total is higher! \n");
		  bank = bank + money_bet;
		  printf ("Current Chips: %d\n", bank);
		}
	      else if (computertotal > playertotal)
		{
		  playerwin = 1;
		  printf (" Computer's total is higher! \n");
		  bank = bank - money_bet;
		  printf ("Current Chips: %d\n", bank);
		}
	      else
		{
		  playerwin = 1;
		  printf (" Equal! \n");
		  bank = bank + money_bet;
		  printf ("Current Chips: %d\n", bank);
		}
	      break;
	    case 'D':		// Double
	    case 'd':
	      printf ("Card Drawn :");
	      hit = getCard (playertotal);
	      getSymbol ();
	      playertotal = playertotal + hit;
	      printf ("Current Card: %d\n", playertotal);
	      if (playertotal > 21)
		break;
	      if (playertotal > computertotal)
		{
		  playerwin = 1;
		  printf (" Your total is higher! \n");
		  bank = bank + (money_bet * 2);
		  printf ("Current Chips: %d\n", bank);
		}
	      else if (computertotal > playertotal)
		{
		  playerwin = 1;
		  printf (" Computer's total is higher! \n");
		  bank = bank - (money_bet * 2);
		  printf ("Current Chips: %d\n", bank);
		}
	      else
		{
		  playerwin = 1;
		  printf (" Equal! \n");
		  printf ("Current Chips: %d\n", bank);
		}
	      break;
	    case 'F':		// Surrender
	    case 'f':
	      printf (" I give up\n");
	      bank = bank - money_bet;
	      printf ("Current Chips: %d\n", bank);
	      break;
	    case 'X':		// Quit Game
	    case 'x':
	      gameend (bank);
	      return 0;
	      break;
	    default:
	      break;
	    }
	  if (playertotal > 21)
	    {
	      // player loses his bet 
	      bank = bank - money_bet;
	      playerwin = 1;
	      printf ("You've gone over 21! You lose!\n\n");
	      printf ("(Current Money: %d)\n", bank);
	    }
	  else if (playertotal == computertotal)
	    {
	        printf("Equal!");
	        printf("(Current Money: %d)\n", bank);
	    }
	  else if (playertotal == 21)
	    {
	      // player has black Jack
	      bank = bank + money_bet;
	      printf ("BlackJack! You Won!\n");
	      printf ("(Current Money: %d)\n", bank);
	    }
	}
      if (bank <= 0)
	{
	  gameend (bank);
	  gameover = 1;
	}
    }
  return 0;
}


// This function is to get a symbol for your card
int
getSymbol ()
{
  int num;
  num = rand () % 4 + 1;
  switch (num)
    {
    case 1:
      return printf ("♣\n");
    case 2:
      return printf ("♦\n");
    case 3:
      return printf ("♥\n");
    case 4:
      return printf ("♠\n");
    default:
      return 0;
    }
}

// This function is the card getting function, it will randomly give you a card from cases 1-13
int
getCard (int playertotal)
{
  int num;
  num = rand () % 13 + 1;
  switch (num)
    {
    case 1:
      printf ("A");
      if (playertotal <= 11)
	return 11;
      else if (playertotal >= 11)
	return 1;
      else;
      break;
    case 2:
      printf ("2");
      return 2;
      break;
    case 3:
      printf ("3");
      return 3;
      break;
    case 4:
      printf ("4");
      return 4;
      break;
    case 5:
      printf ("5");
      return 5;
      break;
    case 6:
      printf ("6");
      return 6;
      break;
    case 7:
      printf ("7");
      return 7;
      break;
    case 8:
      printf ("8");
      return 8;
      break;
    case 9:
      printf ("9");
      return 9;
      break;
    case 10:
      printf ("10");
      return 10;
      break;
    case 11:
      printf ("J");
      return 10;
      break;
    case 12:
      printf ("Q");
      return 10;
      break;
    case 13:
      printf ("K");
      return 10;
      break;
    default:
      return 0;
    }
}

// for betting purposes || failed function
// int
// betting (int *bank, int *money_bet)
// {
//   int a = 1000, b = money_bet;
//   int c = a;
//   a = a - money_bet;
//   printf ("Current Bank: %d - %d = %d chips\n", c, b, a);
// }

// The game menu
void
startscreen ()
{
  int a, bank;
  printf (" [1] Start Game\n");
  printf (" [2] About\n");
  printf (" [3] Credits\n");
  scanf ("%d", &a);
  if (a == 1)			// return to main function
    {
      printf ("Choose a game :\n");
      red();
      printf(" [1] BlackJack  \n");
      yellow();
      printf(" [2] Luck Tester\n");
      cyan();
      printf(" [3] Simple Math Game\n");
      reset();
      printf("Your Choice of Game: ");
      scanf ("%d", &a);
      if (a == 1)
	return;
      else if (a == 2)
	LuckTester ();
      else if (a == 3)
	SimpleMath ();
      else{
          red();
          printf("Input Error");
          reset();
          startscreen ();
      }

    }
  else if (a == 2)		// about the game and stuff then return to startscreen again
    {
      printf (" About the game:\n");
      printf (" ~Blackjack (formerly Black Jack and Vingt-Un) is a casino banking game.\n");
      printf (" The most widely played casino banking game in the world, it uses decks of 52 cards.\n");
      printf (" Basically who has the closest to 21 wins yay! \n\n");
      startscreen ();
    }
  else if (a == 3)		// Show credits, then return startscreen;
    {
      printf (" Credits:\n");
      printf (" This blackjack game was made by Kendrick Chan. Enjoy the game!\n\n");
      startscreen ();
    }
  else				// return startscreen if input is not 1-3
    {
      printf ("Input not found, please try again\n");
      startscreen ();
    }
}

// Test your luck
int
LuckTester ()
{
  int a, b;
  yellow();
  printf ("Welcome to your luck tester! \n");
  reset();
  printf ("You have a 10 %% chance of winning! Goodluck! \n");
  printf ("Choose a number 1-10: ");
  scanf ("%d", &b);
  a = rand () % 10 + 1;
  printf ("\n Number Drawn: %d \n", a);
  if (b == a)
    {
      yellow();
      printf ("Oh wow you are LUCKY! Now go back to startscreen\n");
      reset();
      startscreen ();
    }
  else
    {
      blue();
      printf ("Well you tried, now go back to startscreen!\n");
      reset();
      startscreen ();
    }
}

// start game menu
char
gamescreen ()
{
  char move;
  printf ("Card Dealer vs You\n");
  printf ("[H] Hit  |  [S] Stand  | [D] Double | [F] Surrender | [X] Quit\n");
  printf("Move Input: ");
  scanf (" %c", &move);
  return move;
}

int
SimpleMath () //simple math game
{
  int outer, inner, symbol, total, input;
  outer = rand () % 100 + 1;
  inner = rand () % 100 + 1;
  symbol = rand () % 4 + 1;
  switch (symbol)
    {
    case 1:
      printf ("%d + %d is equal to =? \n", inner, outer);
      break;
    case 2:
      printf ("%d - %d is equal to =? \n", inner, outer);
      break;
    case 3:
      printf ("%d / %d is equal to =? \n", inner, outer);
      break;
    case 4:
      printf ("%d * %d is equal to =? \n", inner, outer);
      break;
    default:
      return 0;
    }
  printf ("Your Answer: ");
  scanf ("%d", &input);

  if (symbol == 1)
    {
      total = inner + outer;
      if (input == total)
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("You got it right! now go back\n\n");
	}
      else
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("aw you got it wrong! now go back\n\n");
	}
      startscreen ();
    }
  else if (symbol == 2)
    {
      total = inner - outer;
      if (input == total)
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("You got it right! now go back\n\n");
	}
      else
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("aw you got it wrong! now go back\n\n");
	}
      startscreen ();
    }
  else if (symbol == 3)
    {
      total = inner / outer;
      if (input == total)
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("You got it right! now go back\n\n");
	}
      else
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("aw you got it wrong! now go back\n\n");
	}
      startscreen ();
    }
  else if (symbol == 4)
    {
      total = inner * outer;
      if (input == total)
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("You got it right! now go back\n\n");
	}
      else
	{
	  printf("Correct Answer is = %d\n", total);
	  printf ("aw you got it wrong! now go back\n\n");
	}
      startscreen ();
    }
  else
    {
      startscreen ();
    }
}

// if game ends
void
gameend (int bank)
{
    red();
  if (bank < 0)
    {
      printf ("Thank you for playing Blackjack! You are now %d in debt!", bank);
    }
  else if (bank == 0)
    {
      printf ("Congrats for losing all your money! Thank you for enjoying the game!");
    }
  else
    {
      printf ("Why'd you leave the game and not finish? anyways, Thank you for playing!");
    }
}

