import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    # TODO: Read database file into a variable
    # Store info for each individual
    people = []
    database = sys.argv[1]
    header = []
    with open(database,"r") as file:
        reader = csv.reader(file)
        header = next(reader)
        for row in reader:
            people.append(row)
    # TODO: Read DNA sequence file into a variable
    sequence = sys.argv[2]
    file = open(sequence, "r")
    text = file.read()
    file.close()

    # TODO: Find longest match of each STR in DNA sequence
    # Add each STR header to a dictionary and intialize the value to 0
    STRs ={}
    for i in range(1, len(header)):
        STRs[header[i]] = 0
    # Find the longest match and replace the value of the STR
    for STR in STRs:
        STRs[STR] = longest_match(text, STR)

    # TODO: Check database for matching profiles
    # Check each person using their name
    STRs_tested = len(header) - 1
    # Person to be compared
    person_number = 0
    for person in people:
        STR_number = 0
        STR_matches = 0
        for STR in STRs:
            # The STR being tested
            STR_number += 1
    # Check each STR count and compare it to the longest match in STRs[STR]
            STR_count = people[person_number][STR_number]
            if int(STR_count) == STRs[STR]:
                STR_matches += 1
            # If the person matched eached STR tested
            if STR_matches == STRs_tested:
                print(people[person_number][0])
                return
        person_number += 1
    # If no person matched
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
