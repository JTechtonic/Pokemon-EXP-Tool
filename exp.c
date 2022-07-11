/**
 * Name: Jeovan Teixeira
 * Last Edited: 7/11/2022
 * Purpose: This program is meant to be a helper program that calculates how much experience grinding is left to do for the user's pokemon. Random idea that I had the urge to code cuz why not lol.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int CalculateTargetEXP(int rate, int targetLevel);
void Test();

int main()
{
    // This test function is to see if the CalculateTargetEXP function makes a correct exp table
    //Test();

    // These integer variables help keep track of where we are in terms of experience
    int targetLevel, currentExp, currentLevel, levelingRate;
    int expGained = 0;

    // Get the data of our experience from the user
    printf("What level are you going for: ");
    scanf("%d", &targetLevel);

    printf("How much EXP do you currently have: ");
    scanf("%d", &currentExp);

    printf("What level are you currently on: ");
    scanf("%d", &currentLevel);

    printf("Which leveling rate is the pokemon\n");
    printf("0 = Erratic\n1 = Fast\n2 = Medium Fast\n3 = Medium Slow\n4 = Slow\n5 = Fluctuating\n");
    scanf("%d", &levelingRate);

    printf("\n\n");

    // Calculate how much exp we need to reach our target and print it
    int targetExp = CalculateTargetEXP(levelingRate, targetLevel);
    printf("Target EXP Amount: %d\n\n", targetExp);
    
    // Create a loop that the user can enter how much experience earned from battles
    while(expGained >= 0)
    {
        // Get the remaining exp we need to level up once using our function
        int remainingExpForLevelUp = CalculateTargetEXP(levelingRate, currentLevel + 1) - currentExp;

        // Get the remaining exp we need to reach our goal
        int remainingExpForTarget = targetExp - currentExp;

        // Display that information
        printf("Remaining Exp to get to level %d: %d\n", currentLevel + 1, remainingExpForLevelUp);
        printf("Remaining Exp to get to final target: %d\n", remainingExpForTarget);
        
        // Find out how much exp we gained from our previous battle (The user can enter -1 if they are done grinding)
        printf("How much Exp gained (-1 to quit) : ");
        scanf("%d", &expGained);

        // Break out if the user is done
        if(expGained == -1) break;

        // Add our exp gained to our current exp
        currentExp += expGained;

        // If we reached enough exp to reach our target goal then we are done
        if(remainingExpForTarget - expGained <= 0)
        {
            printf("Target Reached!\n");
            break;
        }
        else if(remainingExpForLevelUp - expGained <= 0) // Otherwise check to see if we leveled up if so then increment our level
        {
            currentLevel++;
            printf("Level up! Now at %d\n", currentLevel);
        }

        printf("\n");
    }

    return 0;
}


/**
 * This function will calculate the target experience we need for a certain level using the different leveling rates pokemon uses. There are 6 total leveling rates in the game all with different functions
 */
int CalculateTargetEXP(int rate, int targetLevel)
{
    // Variable that will hold our target exp that we will return
    double targetExp = 0;

    if(targetLevel == 1) return 0;

    switch(rate)
    {
        case 0: // Case 0 is for the "erratic" experience group (link to piecewise function: https://bulbapedia.bulbagarden.net/wiki/Experience#Erratic)
            if(targetLevel < 50)
            {
                targetExp = (pow(targetLevel, 3) * (100 - targetLevel)) / 50.0;
                targetExp = floor(targetExp);
            }
            else if(targetLevel >= 50 && targetLevel < 68)
            {
                targetExp = (pow(targetLevel, 3) * (150 - targetLevel)) / 100.0;
                targetExp = floor(targetExp);
            }
            else if(targetLevel >= 68 && targetLevel < 98)
            {
                targetExp = (pow(targetLevel, 3) * ((1911 - (10 * targetLevel)) / 3)) / 500.0;
                targetExp = floor(targetExp);
            }
            else if(targetLevel >= 98 && targetLevel <= 100)
            {
                targetExp = (pow(targetLevel, 3) * (160 - targetLevel)) / 100.0;
                targetExp = floor(targetExp);
            }
            break;

        case 1: // Case 1 is for the "fast" experience group
            targetExp = (4 * pow(targetLevel, 3)) / 5.0; // (4 * n^3) / 5
            targetExp = floor(targetExp);
            break;

        case 2: // Case 2 is for the "medium fast" experience group
            targetExp = pow(targetLevel, 3); // n^3
            targetExp = floor(targetExp);
            break;

        case 3: // Case 3 is for the "medium slow" experience group
            targetExp = ((6.0 / 5.0) * pow(targetLevel, 3)) - (15 * pow(targetLevel, 2)) + (100 * targetLevel) - 140; // (6/5 * n^3) - (15 * n^2) + (100 * n) - 140
            targetExp = floor(targetExp);
            break;

        case 4: // Case 4 is for the "slow" experience group
            targetExp = (5 * pow(targetLevel, 3)) / 4; // (5 * n^3) / 4
            targetExp = floor(targetExp);
            break;

        case 5: // Case 5 is for the "fluctuating" experience group (link to piecewise function: https://bulbapedia.bulbagarden.net/wiki/Experience#Fluctuating)
            if(targetLevel < 15)
            {
                targetExp = pow(targetLevel, 3) * ((((targetLevel + 1) / 3.0) + 24) / 50.0);
                targetExp = floor(targetExp);
            }
            else if(targetLevel >= 15 && targetLevel < 36)
            {
                targetExp = pow(targetLevel, 3) * ((targetLevel + 14) / 50.0);
                targetExp = floor(targetExp);
            }
            else if(targetLevel >= 36 && targetLevel <= 100)
            {
                targetExp = pow(targetLevel, 3) * (((targetLevel / 2.0) + 32) / 50.0);
                targetExp = floor(targetExp);
            }
            break;
    }

    // Return our data
    return (int)targetExp;
}

void Test()
{
    FILE* output;
    output = fopen("table.txt", "w");

    for(int i = 1; i <= 100; i++)
    {
        fprintf(output, "%-4d: %-8d\t%-8d\t%-8d\t%-8d\t%-8d\t%-8d\n", i, CalculateTargetEXP(0, i), CalculateTargetEXP(1, i), CalculateTargetEXP(2, i), CalculateTargetEXP(3, i), CalculateTargetEXP(4, i), CalculateTargetEXP(5, i));
    }

    fclose(output);
}