#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
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
    // TODO
    for (int i = 0; i < candidate_count; i++){
        if (strcmp(name, candidates[i]) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++){
        for (int j = i + 1; j < candidate_count; j++){
            preferences[ranks[i]][ranks[j]]++;
            }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++){
        for (int j = i + 1; j < candidate_count; j++){
            // Pairs[i].winner = int i    Pairs[i].loser = int i
            int first_candidate = preferences[i][j];
            int second_candidate = preferences[j][i];
            if (first_candidate > second_candidate){
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (first_candidate < second_candidate){
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int strength[pair_count];
    for (int i = 0; i < pair_count; i++){
        strength[i] = (preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner]);
    }
    for (int j = 0; j < pair_count - 1; j++){
        for (int k = j + 1; k < pair_count; k++){
            // How many prefer winner over loser. Winner - loser votes = strength.
            if (strength[k] > strength[j]){
                int temp_strength = strength[j];
                strength[j] = strength[k];
                strength[k] = temp_strength;

                pair temp_pair = pairs[j];
                pairs[j] = pairs[k];
                pairs[k] = temp_pair;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
bool is_circle(int loser, int winner)
{
    if (loser == winner){
        return true;
    }
    for (int i = 0; i < candidate_count; i++){
        if (locked[loser][i]){
            if (is_circle(i, winner)){
                return true;
            }
        }
    }
    return false;
}
void lock_pairs(void)
{
    // TODO
    // If adding a locked pair makes a specific column of a candidate true, stop so you dont create a cycle.
    for (int i = 0; i < pair_count; i++){
        if(!is_circle(pairs[i].loser, pairs[i].winner)){
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // If the column of a candidate is all false, then they are the source and the winner.
    // Column is the second number of the 2D array.
    for (int i = 0; i < candidate_count; i++){
        int score = candidate_count;
        for (int j = 0; j < candidate_count; j++){
            if(locked[j][i] == false){
                score--;
                if (score == 0){
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}