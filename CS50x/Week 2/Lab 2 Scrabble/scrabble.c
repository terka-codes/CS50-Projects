#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Setting a variable for keeping the score
    int score = 0;

    // Looping through each character of the word
    for (int i = 0; i < strlen(word); i++)
    {
        // if the character is a letter we can continue
        if (isalpha(word[i]))
        {
            // If the letter is in lower case this will make it in upper case
            word[i] = toupper(word[i]);
            // The letter in upper case have the numbers 65 to 90, so to assign the right
            // score to each number the program will take the number of the letter eg. A = 65
            // and subtract 65 so that 65 - 65 = 0, so the points of letter A = POINTS[O] which is 0
            // works the same for other letter eg. Q = 81, so 81 - 65 = 16 and POINTS[16] = 10.
            // And the function adds the points value to a current score.
            score += POINTS[(word[i] - 65)];
        }
    }
    return score;
}
#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    // Setting a variable for keeping the score
    int score = 0;

    // Looping through each character of the word
    for (int i = 0; i < strlen(word); i++)
    {
        // if the character is a letter we can continue
        if (isalpha(word[i]))
        {
            // If the letter is in lower case this will make it in upper case
            word[i] = toupper(word[i]);
            // The letter in upper case have the numbers 65 to 90, so to assign the right
            // score to each number the program will take the number of the letter eg. A = 65
            // and subtract 65 so that 65 - 65 = 0, so the points of letter A = POINTS[O] which is 0
            // works the same for other letter eg. Q = 81, so 81 - 65 = 16 and POINTS[16] = 10.
            // And the function adds the points value to a current score.
            score += POINTS[(word[i] - 65)];
        }
    }
    return score;
}
