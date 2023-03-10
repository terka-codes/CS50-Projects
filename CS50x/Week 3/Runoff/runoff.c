#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // loop through the candidates
    {
        if (strcmp(name, candidates[i].name) == 0) // checks if the name is in the array
        {
            preferences[voter][rank] = i;  // records the vote
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    for (int i = 0; i < voter_count; i++) // loops through the votes
    {
        for (int j = 0; j < candidate_count; j++) // loops throught the candidates
        {
            if (candidates[preferences[i][j]].eliminated == false) //checks if candidate is still not eliminated
            {
                candidates[preferences[i][j]].votes++; // counts in the votes
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // loops throught the candidates
    {
        if (candidates[i].votes > (voter_count / 2)) // checks if any candidate has more than half of the votes
        {
            printf("%s\n", candidates[i].name); // if yes, prints their name
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min_votes = MAX_VOTERS; // max number of votes to compare with
    int min = 0; // zero in case no one has min
    for (int i = 0; i < candidate_count; i++) // loop through the candidates
    {
        if (candidates[i].eliminated == false
            && candidates[i].votes < min_votes) // finds not eliminated candidates and in thhey have less than min_votes
        {
            min_votes = candidates[i].votes; // if has less than min_votes records the number to new min_votes
            min = min_votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int count = 0; // sets count to 0
    int live = 0; // -||-
    for (int i = 0; i < candidate_count; i++) // loops throught the candidates
    {
        if (candidates[i].eliminated == false) //checks if candidate is eliminated
        {
            live++; // if not, add to live
            if (min == candidates[i].votes) //checks if candidates have min votes
            {
                count++; // if yes, counts in
            }
        }
    }
    if (count == live) // compares if count and live are the same, if yes means it is tie and returns true
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++) // loops throught the candidates
    {
        if (candidates[i].eliminated == false
            && min == candidates[i].votes) // looks for candidate who has not been eliminated and has the min votes
        {
            candidates[i].eliminated = true; // when finds the candidate it eliminates them
        }
    }
    return;
}