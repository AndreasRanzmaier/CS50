import csv
import sys


def main():

    # DONE: Check for command-line usage
    if len(sys.argv) != 3:
        print("incorrect number of cmd-line arguments")

    # DONE: Read database file into a variable
    database = []
    with open(sys.argv[1], newline='\n') as csvfile:
        for element in csvfile:
            database.append(element.replace('\n', ''))

    # DONE: Read DNA sequence file into a variable
    sequence = ""
    with open(sys.argv[2], newline= '\n') as file:
        for element in file:
            sequence += element


    # DONE: Find longest match of each STR in DNA sequence
    subsequences = database[:1:][0].split(",")
    longestmatches = ""
    for subsequence in subsequences[1::]:
        longestmatches += str(longest_match(sequence, subsequence)) + ","
    longestmatches =longestmatches[:-1]

    # DONE: Check database for matching profiles
    found = False
    for row in database[1::]:
        if longestmatches in row:
            print(row.split(",")[0])
            found = True
    if found == False:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsed uence
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
