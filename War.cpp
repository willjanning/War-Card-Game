#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHRandom.h>

using namespace std;

//create a class named War. This is the required class specified on page 1 of the APP
//38 write-up
class War
{
    //make public functions shuffle, war, dispStats, and dispWinner
public:
    War();
    void shuffle();
    void war();
    void dispStats();
    void dispWinner();
    void reset();
    //make private members p1wins, p2wins, p1losses, p2losses, ties, p1[26],
    //p2[26], and deck[52]
private:
    int p1wins;
    int p2wins;
    int p1losses;
    int p2losses;
    int ties;
    int p1[26], p2[26];
    int deck[52];
};




int main(void)
{
    LCD.Clear(BLACK);
    LCD.WriteLine("Welcome to war!");
    Sleep(4.0);

    //This is the instantiation of the required object specified on
    //page 1 of the APPC38-1 write-up and instructions
    War war;
    //continuously check for a touch on the four buttons
    while(true)
    {
          //clear the screen and create 4 buttons: Declare war, Stats, See Rules,
          // Credits
          LCD.Clear(BLACK);
          FEHIcon::Icon start_game;
          start_game.SetProperties("Declare war", 20, 20, 130, 90, RED, GRAY);
          start_game.Draw();

          FEHIcon::Icon stats;
          stats.SetProperties("Stats", 170, 20, 130, 90, RED, GRAY);
          stats.Draw();

          FEHIcon::Icon rules;
          rules.SetProperties("See Rules", 20, 130, 130, 90, RED, GRAY);
          rules.Draw();

          FEHIcon::Icon credits;
          credits.SetProperties("Credits", 170, 130, 130, 90, RED, GRAY);
          credits.Draw();

          while(!LCD.Touch())
          {
            //wait for user to touch the screen
          }
           float x, y;
           //LCD.Touch detects where on the screen the user is pressing
            LCD.Touch(&x, &y);
          while(LCD.Touch()){
            //wait for user to release the screen
          }
            //if the declare war button is touched, run the code within
            //the if selection statement
            if(start_game.Pressed(x,y,1))
            {   //begin main game
                war.reset();

                LCD.Clear(BLACK);

                //start shuffling
                war.shuffle();

                //start the card game
                war.war();

                //display the winner
                war.dispWinner();
                Sleep(4.0);
               }
            //return to beginning of while loop

            //run code if stats button is pressed
            else if(stats.Pressed(x,y,1))
            {
                LCD.Clear(BLACK);
                war.dispStats();
              Sleep(3.0);
            }
            //run if statement if rules button is pressed
            else if(rules.Pressed(x,y,0))
            {   //clear the screen and write the rules of the game to the screen
                    LCD.Clear(BLACK);
                    LCD.Write("Touch the screen to play a card. The computer
                      will play a card too.");
                    LCD.WriteLine("Whoever has the higher card wins the round. If you tie, you must tap");
                    LCD.WriteLine("the screen as fast as possible against the computer. Whoever taps the fastest");
                    LCD.WriteLine("wins the round.");
                    Sleep(3.0);
            }
            //if credits buton is pressed, show who developed the game and who helped
            else if(credits.Pressed(x,y,0))
            {
                LCD.Clear(BLACK);
                LCD.Write("Credits:");
                LCD.WriteLine("Programmers: Lucas Rashilla & Will Janning");
                LCD.WriteLine("TAs: Lucas Nestor & Samara Einstein");
                LCD.WriteLine("Professor: Krieger");
                Sleep(4.0);
            }
    }

}



//These are the required user-defined functions specified in the APP C38-1 write-up

//Define constructor function
War::War()
{
    //initialize all members except deck to 0, then initialize deck to the
    //standard values in a deck of cards
    p1wins = 0;
    p2wins = 0;
    p1losses = 0;
    p2losses = 0;
    ties = 0;

    for(i = 0; i<26; i++)
    {
     p1[i] = 0;
     p2[i] = 0;
    }
    for(int i = 0; i<13; i++)
    {
      for(int j = 0; j < 4; j++)
      {
        deck[i*4 + j] = i + 2;
      }
    }
}
//Define shuffle function
void War::shuffle()
{
    //declare counter variables
       int j;
       int k = 1;
       int l = 1;
       int m;
       int i;
       //generate a random integer
   Random.RandInt();

//shuffle p1 deck
   //this is the required for loop specified in the APP C38-1 write-up.
       for(i = 0; i<26; i++)
       {			l = 1;
                   do
                   {//start while
               //make sure integer is between 0 and 52
                       m = (Random.RandInt() % 52);
                       if(deck[m] != 0)
                       {//start if
                           p1[i] = deck[m];
                           deck[m] = 0;
                           l = 0;
                       }//end if

                   }while(l);

           }//end for

       //shuffle p2 deck
       for(i = 0; i<26; i++)
       {			l = 1;
                   //this is the required do-while specified in the APP C38-1 write-up
                   do
                   {//start while
               //make sure integer is between 0 and 52
                       m = (Random.RandInt()%52);
                       if(deck[m] != 0)
                       {//start if
                           p2[i] = deck[m];
                           deck[m] = 0;
                           l = 0;
                       }//end if
                   }while(l);
           }//end for

//end shuffling
}
//Define war function for playing the game
void War::war()
{
    int i;
    //loop for 26 cards in each player's deck
    for(i = 0; i<26; i++)
        {
       float x_position, y_position;

        LCD.WriteLine("Tap to draw");
        //this is the required while loop specified in the APP C38-1 write-up
        while(!LCD.Touch(&x_position, &y_position))
        {
            //wait for button to be touched
        }
        while(!LCD.Touch(&x_position, &y_position)){
          //wait for button to be released
        }

        //This is the required if/else selection structure specified in the APP C38-1 write-up
        //tell the player which cards  were drawn
       if(p1[i] == 11)
       {
           LCD.WriteLine("Your card is: Jack");
       }
       else if(p1[i] == 12)
       {
           LCD.WriteLine("Your card is: Queen");
       }
       else if(p1[i] == 13)
       {
           LCD.WriteLine("Your card is: King");
       }
       else if(p1[i] == 14)
       {
           LCD.WriteLine("Your card is: Ace");
       }
       else
       {
           LCD.Write("Your card is: ");
           LCD.WriteLine(p1[i]);
       }
       if(p2[i] == 11)
       {
           LCD.WriteLine("The enemy's card is: Jack");
       }
       else if(p2[i] == 12)
       {
           LCD.WriteLine("The enemy's card is: Queen");
       }
       else if(p2[i] == 13)
       {
          LCD.WriteLine("The enemy's card is: King");
       }
       else if(p2[i] == 14)
       {
          LCD.WriteLine("The enemy's card is:  Ace");
       }
       else
       {
           LCD.Write("The enemy's card is: ");
           LCD.WriteLine(p2[i]);
       }

        Sleep(2.0);
        LCD.Clear(BLACK);
        //display an icon for whatever card was played by the player and computer
        //this is the required switch/case selection structure specified in the
        //APP C38-1 write-up
        switch(p1[i])
        {
        case 2:
        {
            //display card 2
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon twocard[1];
            char label32[1][20] = {"2"};
            FEHIcon::DrawIconArray(twocard,1,1, 128, 128, 130, 20, label32, RED, RED);


        break;
        }
        case 3:
             {
            //display card 3
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon threecard[1];
            char label31[1][20] = {"3"};
            FEHIcon::DrawIconArray(threecard,1,1, 128, 128, 130, 20, label31, RED, RED);

        break;
        }
        case 4:
               {
            //display card 4
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon fourcard[1];
            char label30[1][20] = {"4"};
            FEHIcon::DrawIconArray(fourcard,1,1, 128, 128, 130, 20, label30, RED, RED);


        break;
        }
        case 5:
        {
            //display card 5
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon fivecard[1];
            char label29[1][20] = {"5"};
            FEHIcon::DrawIconArray(fivecard,1,1, 128, 128, 130, 20, label29, RED, RED);


        break;
        }
        case 6:
        {
            //display card 6
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon sixcard[1];
            char label28[1][20] = {"6"};
            FEHIcon::DrawIconArray(sixcard,1,1, 128, 128, 130, 20, label28, RED, RED);


        break;
        }
        case 7:
        {
            //display card 7
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon sevencard[1];
            char label27[1][20] = {"7"};
            FEHIcon::DrawIconArray(sevencard,1,1, 128, 128, 130, 20, label27, RED, RED);

        break;
        }
        case 8:
        {
            //display card 8
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon eightcard[1];
            char label26[1][20] = {"8"};
            FEHIcon::DrawIconArray(eightcard,1,1, 128, 128, 130, 20, label26, RED, RED);

        break;
        }
        case 9:
        {
            //display card 9
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon ninecard[1];
            char label25[1][20] = {"9"};
            FEHIcon::DrawIconArray(ninecard,1,1, 128, 128, 130, 20, label25, RED, RED);

        break;
        }
        case 10:
        {
            //display card 10
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon tencard[1];
            char label24[1][20] = {"10"};
            FEHIcon::DrawIconArray(tencard,1,1, 128, 128, 130, 20, label24, RED, RED);

        break;
        }
        case 11:
        {
            //display card jack
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon jackcard[1];
            char label23[1][20] = {"Jack"};
            FEHIcon::DrawIconArray(jackcard,1,1, 128, 128, 130, 20, label23, RED, RED);

        break;
        }
        case 12:
        {
            //display card queen
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon queencard[1];
            char label20[1][20] = {"Queen"};
            FEHIcon::DrawIconArray(queencard,1,1, 128, 128, 130, 20, label20, RED, RED);

        break;
        }
        case 13:
        {
            //display card king
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon kingcard[1];
            char label21[1][20] = {"King"};
            FEHIcon::DrawIconArray(kingcard,1,1, 128, 128, 130, 20, label21, RED, RED);

        break;
        }
        default:

            //display card ace
            LCD.Clear(FEHLCD::Black);
            FEHIcon::Icon acecard[1];
            char label22[1][20] = {"Ace"};
            FEHIcon::DrawIconArray(acecard,1,1, 128, 128, 130, 20, label22, RED, RED);

        break;
        }
        switch(p2[i])
        {
        case 2:
        {
            //display card 2

            FEHIcon::Icon twocard[1];
            char label32[1][20] = {"2"};
            FEHIcon::DrawIconArray(twocard,1,1, 128, 128, 20, 20, label32, RED, RED);

        break;
        }
        case 3:
             {
            //display card 3

            FEHIcon::Icon threecard[1];
            char label31[1][20] = {"3"};
            FEHIcon::DrawIconArray(threecard,1,1, 128, 128, 20, 20, label31, RED, RED);

        break;
        }
        case 4:
               {
            //display card 4

            FEHIcon::Icon fourcard[1];
            char label30[1][20] = {"4"};
            FEHIcon::DrawIconArray(fourcard,1,1, 128, 128, 20, 20, label30, RED, RED);

        break;
        }
        case 5:
        {
            //display card 5

            FEHIcon::Icon fivecard[1];
            char label29[1][20] = {"5"};
            FEHIcon::DrawIconArray(fivecard,1,1, 128, 128, 20, 20, label29, RED, RED);

        break;
        }
        case 6:
        {
            //display card 6

            FEHIcon::Icon sixcard[1];
            char label28[1][20] = {"6"};
            FEHIcon::DrawIconArray(sixcard,1,1, 128, 128, 20, 20, label28, RED, RED);

        break;
        }
        case 7:
        {
            //display card 7

            FEHIcon::Icon sevencard[1];
            char label27[1][20] = {"7"};
            FEHIcon::DrawIconArray(sevencard,1,1, 128, 128, 20, 20, label27, RED, RED);

        break;
        }
        case 8:
        {
            //display card 8

            FEHIcon::Icon eightcard[1];
            char label26[1][20] = {"8"};
            FEHIcon::DrawIconArray(eightcard,1,1, 128, 128, 20, 20, label26, RED, RED);

        break;
        }
        case 9:
        {
            //display card 9

            FEHIcon::Icon ninecard[1];
            char label25[1][20] = {"9"};
            FEHIcon::DrawIconArray(ninecard,1,1, 128, 128, 20, 20, label25, RED, RED);

        break;
        }
        case 10:
        {
            //display card 10

            FEHIcon::Icon tencard[1];
            char label24[1][20] = {"10"};
            FEHIcon::DrawIconArray(tencard,1,1, 128, 128, 20, 20, label24, RED, RED);

        break;
        }
        case 11:
        {
            //display card jack

            FEHIcon::Icon jackcard[1];
            char label23[1][20] = {"Jack"};
            FEHIcon::DrawIconArray(jackcard,1,1, 128, 128, 20, 20, label23, RED, RED);

        break;
        }
        case 12:
        {
            //display card queen

            FEHIcon::Icon queencard[1];
            char label20[1][20] = {"Queen"};
            FEHIcon::DrawIconArray(queencard,1,1, 128, 128, 20, 20, label20, RED, RED);

        break;
        }
        case 13:
        {
            //display card king

            FEHIcon::Icon kingcard[1];
            char label21[1][20] = {"King"};
            FEHIcon::DrawIconArray(kingcard,1,1, 128, 128, 20, 20, label21, RED, RED);

        break;
        }
        default:

            //display card ace

            FEHIcon::Icon acecard[1];
            char label22[1][20] = {"Ace"};
            FEHIcon::DrawIconArray(acecard,1,1, 128, 128, 20, 20, label22, RED, RED);

        break;
        }
        Sleep(4.0);
        //if player 1 shows a higher card than player 2, increment p1wins and p2losses
                //below are the required relational and logical operators specified in the APP C38-1 write-up
                if(p1[i]>p2[i] && p2[i]!=0)
                {
                     LCD.Clear(FEHLCD::Black);
                    LCD.WriteLine("You have won!");

                    p1wins++;
                    p2losses++;

                }
                 //if player 2 shows a higher card than player 1, increment p2wins and p1losses
                else if(p1[i]<p2[i])
                {
                  LCD.Clear(FEHLCD::Black);
                    LCD.WriteLine("You have lost");

                    *p2wins++;
                    *p1losses++;

                }
                //if the two players show the same card run this code
                else
                { LCD.Clear(FEHLCD::Black);
                    LCD.WriteLine("Tie!");
                    LCD.WriteLine("Press the 'click' key as fast as you can!");
                    LCD.WriteLine("First one to fifteen clicks wins!");
                    int  pushes = 0;

                    //create clicker

                    FEHIcon::Icon tieclick[1];

                    char label6[1][20] = {"Click!"};

                    FEHIcon::DrawIconArray(tieclick,1,1, 160, 20, 20, 20, label6, RED, RED);

                    float x_position, y_position;

                    float t_now;
                    float t_later;

                    t_now = TimeNow();
                    int iteration = 0;
                    while(iteration<15)
                    {
                      while(!LCD.Touch(&x_position, &y_position))
                      {
                          //wait for the player to touch the screen
                      }
                      //whenever player touches, increment push counter
                      while(LCD.Touch(&x_position, &y_position)){
                        //wait for player to release button
                      }
                      iteration++;
                    }

                    t_later = TimeNow();
                    //if you made 15 clicks in less than 2.5 seconds, you win the tie-breaker
                    if(t_later - t_now < 2.50)
                    {
                        LCD.WriteLine("You won the tie-breaker!");
                        p1wins++;
                        p2losses++;
                    }
                    else
                    {
                        LCD.WriteLine("You lost the tie-breaker.");
                        p1losses++;
                        p2wins++;
                    }


                }

        //end main game

}
}
//Define dispStats function
void War::dispStats()
{
    //Display the number of wins and losses for each player
    LCD.Clear(FEHLCD::Black);
    LCD.Write("P1 Wins: ");
    LCD.WriteLine(p1wins);
    LCD.Write("P1 Losses: ");
    LCD.WriteLine(p1losses);
    LCD.Write("P2 Wins: ");
    LCD.WriteLine(p2wins);
    LCD.Write("P2 Losses: ");
    LCD.WriteLine(p2losses);
    LCD.Write("Ties: ");
    LCD.WriteLine(ties);

}
//Define dispWinner function
void War::dispWinner()
{
    //Display if player 1 has won or lost more battles than the computer
    if(p1wins>p2wins)
    {
        LCD.Clear(BLACK);
        LCD.WriteLine("You have won the most battles!");
    }
    else if(p2wins>p1wins)
    {
        LCD.Clear(BLACK);
        LCD.WriteLine("You have lost the most battles.");
    }
    else
    {
        LCD.Clear(BLACK);
        LCD.WriteLine("Stalemate.");
    }
}

void War::reset()
{
  //reset all members except deck to 0, then initialize deck to the
  //standard values in a deck of cards
  p1wins = 0;
  p2wins = 0;
  p1losses = 0;
  p2losses = 0;
  ties = 0;

  for(i = 0; i<26; i++)
  {
   p1[i] = 0;
   p2[i] = 0;
  }
  for(int i = 0; i<13; i++)
  {
    for(int j = 0; j < 4; j++)
    {
      deck[i*4 + j] = i + 2;
    }
  }
}
