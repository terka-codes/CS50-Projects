#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

bool vote(string name)
{
    // Loops throught the names of candidates to see if it is the same as the input
    // Then counts plus one
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j].name, name) == 0)
        {
            candidates[j].votes++;
            return true;
        }
    }
    return false;
}

void print_winner(void)
{
    // Seting a new variable to help with looking for the person with most votes
    int biggest = 0;

    // Looping through the numbers of votes of each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If anyone has more votes than 0, the variable of biggest changes to that number of votes
        // If anyone has more votes than the biggest nuber so far, biggest chnages to that that number
        if (candidates[i].votes > biggest)
        {
            biggest = candidates[i].votes;
        }
    }

    // Looping through the numbers of votes of each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // If any candidate has the same amout of votes as the value of biggest it prints their name
        // If more candidates have the same amount of votes, it prints them all
        if (candidates[i].votes == biggest)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}