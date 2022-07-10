/**
 * Name: Jeovan Teixeira
 * Last Edited: 7/9/2022
 * Purpose: This program is meant to be a helper program that calculates how much experience grinding is left to do for the user's pokemon. Random idea that I had the urge to code cuz why not lol.
 * (UNFINISHED)
 */

#include <stdio.h>
#include <math.h>

int CalculateTargetEXP(int rate, int targetLevel);

int main()
{
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
 * (UNFINISHED ONLY WORKS FOR SLOW & MEDIUM SLOW EXPERIENCE GROUP)
 */
int CalculateTargetEXP(int rate, int targetLevel)
{
    // Variable that will hold our target exp that we will return
    double targetExp = 0;

    switch(rate)
    {
        case 3: // Case 3 is for the "medium slow" experience group
            targetExp = ((6.0 / 5.0) * pow(targetLevel, 3)) - (15 * pow(targetLevel, 2)) + (100 * targetLevel) - 140; // (6/5 * n^3) - (15 * n^2) + (100 * n) - 140
            targetExp = floor(targetExp);
            break;

        case 4: // Case 4 is for the "slow" experience group
            targetExp = (5 * pow(targetLevel, 3)) / 4; // (5 * n^3) / 4
            targetExp = floor(targetExp);
            break;
    }

    // Return our data
    return (int)targetExp;
}