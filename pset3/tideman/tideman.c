#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// Adjecency Matrix
// true = locked
// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    // Usses indicies
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Checks that the name is valid
        if (strcmp(candidates[i], name) == 0)
        {
            // Sets the rank to index of candidate
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // Check to see if we're comparing the same candidate.
            if (ranks[i] == ranks[j])
                continue;

            // Add one if the rank is higher.
            if (ranks[i] < ranks[j])
                preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // If candidate i has more votes than candidate j
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

void merge_sort(pairs * tmpPairs[])
{

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Bubble Sort
    pair tmpPair;
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count - 2; j++)
        {
            if (pairs[j].winner > pairs[i].winner)
            {
                tmpPair = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmpPair;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int winner_i;
    int loser_i;
    // locked[winner_i][loser_i] = true;
    for (int i = 0; i < pair_count; i++)
    {
        winner_i = pairs[i].winner;
        loser_i = pairs[i].loser;

        // Checks to see if either adjacent node is already locked.
        // If there's already a locked node, continue to prevent cycling.
        if (locked[winner_i + 1][loser_i + 1] || locked[winner_i - 1][loser_i - 1]) {
            continue;
        }

        locked[winner_i][loser_i] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // if (locked[pairs[i].winner][pairs[i].loser])
        // {
        //     printf("%d. %s\n", i, candidates[pairs[i].winner]);
        // }

        printf("Pairs[%d] winner:%d loser:%d\n", i, pairs[i].winner, pairs[i].loser);
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (locked[pairs[i].winner][pairs[i].loser])
        {
            printf("locked[pairs[%d]][pairs[%d]] winner:%s loser:%s\n", i, i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
        }
    }

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i == j) continue;

            printf("preferences[%d][%d]: %d\n", i, j, preferences[i][j]);
        }
    }
    return;
}

