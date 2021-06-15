/*
    Anthony Dalia
    Sarah Angel
    Program 6 - Treasure Chest
    10/28/2017
*/

//Libs
#include <stdio.h>
#include <stdlib.h>

//Consts
#define MIN 0
#define MAX 100

int main(void)
{

    //Vars
    FILE *ifp;
    char fileName[20];
    int i, j, guesses = 0, correct = 0,valid = 1, GuessInputed;
    int correctCombo[7] = {0};
    int inputCombo[7] = {0};

    //Prompt the user to enter a file name
    printf("What is the name of the file? \n:");

    scanf("%s", fileName);

    ifp = fopen(fileName, "r");

    //Ensure the file works
    if (ifp == NULL)
    {
        printf("The file could not be opened properly.");
        return 0;
    }

    //Transport vals into the solution array
    for (i = 0; i < 7; i++)
    {
        //Scan in the var
        int val;
        fscanf(ifp, "%d", &val);

        //Read the value into the input array
        correctCombo[i] = val;
        //printf("%d \n", val);
    }

    //Say the begining line
    printf("------------------------------\nTo get to me treasure you'll have to figure out which of me 100 keys are used in the 7 locks of me treasure chest. \n\n");
    while (correct == 0)
    {

        //Clear the loop for the next set of guesses
        guesses = 0;
        valid = 1;
        int resultArray[7] = {-1};

        //Ask for guesses
        printf("Which Keys Will Ye Use?\n");

        //Get some guesses goin
        while (guesses < 7)
        {

            //Get a guess
            scanf("%d", &GuessInputed);

            if (GuessInputed > MIN && GuessInputed < MAX)
            {
                inputCombo[guesses] = GuessInputed;
                guesses ++;
            }
            else
            {
                printf("Please ensure you enter a number between %d and %d. \n", MIN, MAX);
            }

        }

        //Check for duplicates
        for (i = 0; i < 7; i++)
        {

            for(j = (i+1); j < 7; j++)
            {
                //printf("DEBUG - %d(val - %d) against %d(val - %d) \n", i, inputCombo[i], j, inputCombo[j]);

                if (inputCombo[i] == inputCombo[j] && valid != 0)
                {
                    printf("You can only use each key once, matey! \n\n");
                    valid = 0;
                }
            }
        }


        //Skip everything else if there are duplicates
        if (valid != 0)
        {

            //Check for valid order
            for (i = 0; i < 7; i++)
            {

                if (inputCombo[i] == correctCombo[i])
                {
                    //Set to 1 indicating a correct value in the correct spot
                    resultArray[i] = 1;
                }
            }

            //Check for valid key numbers
            for(i = 0; i < 7; i++)
            {
                for(j = 0; j < 7; j++)
                {
                    //printf("DEBUG - %d(val - %d) against %d(val - %d) \n", i, inputCombo[i], j, correctCombo[j]);
                    if (inputCombo[i] == correctCombo[j])
                    {
                        if (resultArray[i] != 1)
                        {
                            //Set to 2 indicating correct value in an incorrect spot
                            resultArray[i] = 2;

                            //printf("DEBUG -Found Correct %d(val | %d) against %d(val | %d) \n", i, inputCombo[i], j, correctCombo[j]);
                        }
                    }
                }
            }

            /*DEBUG - Print Result Array
            printf("-----RESULT ARRAY-----\n");
            for(i = 0; i < 7; i++)
                printf("%d\n", resultArray[i]);

            printf("\n\n");
            */

            //Assess the results
            int correctKeys = 0;
            int correctOrder = 0;

            for (i = 0; i < 7; i++)
            {

                if (resultArray[i] == 1)
                {
                    correctOrder++;
                }
                else if (resultArray[i] == 2)
                {
                    correctKeys++;
                }
                else
                {
                    //Do nothing
                }
            }

            //DEBUG - PRINT OUT CORRECT KEYS
            //printf("DEBUG - CORRECT KEYS (%d), CORRECT ORDER (%d) \n", correctKeys, correctOrder);

            //Print out the result
            if(correctOrder == 7)
            {

                //All the correct keys in the correct order
                printf("Arr! You've opened me treasure chest and found a map to Treasure Island! \n\n");
                correct = 1;
                break;
            }
            if ((correctOrder > 0 && correctOrder < 7) || correctKeys > 0)
            {
                //Some keys are correct but not enough to win
                printf("%d of those are correct, matey! But are they in the right order? \n\n", (correctOrder+correctKeys));
            }
        }

    }

    //Close the file to reduce chance of couruption.
    fclose(ifp);
}
