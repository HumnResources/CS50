from sys import argv
import csv


def main():
    if len(argv) != 3:
        print("Please double check your command arguments:\npython dna.py <STR-DB-Path> <DNA-file-path>")
        return

    # Database contains a list with index 0 being the name.
    # This allows for len() to iterate over any # STRs provided
    database = []
    # Store individual STRs
    str_list = []
    # Store STR counts
    str_counts = []

    # Read in database file containing people's DNA sequence's
    with open(argv[1], "r") as csvfile:
        reader = csv.reader(csvfile)

        # Iterate over the csv file contents
        # We add the header information for the
        # DNA sequences in str_list
        for idx, row in enumerate(reader):
            if idx == 0:
                for idy, col in enumerate(row):
                    if idy != 0:
                        str_list.append(col)
            else:
                database.append(row)

    # Read in DNA sequence to compare against
    file = open(argv[2], "r")
    dna = file.readline().strip()
    file.close()

    # For each of our STRs, loop through and find the longest substring in sequence
    for STR in str_list:
        longest_substring = ""
        str_length = len(STR)

        # Iterate over the dna string provided
        for i in range(len(dna)):
            char = dna[i].upper()
            curr_substring = ""

            # Checks for start of substring
            if char == STR[0]:
                tmp = dna[i:i+str_length].upper()

                # Iterate until we are no longer in a sequence
                # Creating a substring to compare with
                while tmp == STR:
                    curr_substring += tmp
                    i = i + str_length
                    tmp = dna[i:i+str_length].upper()

            # If we found a substring longer, update
            if len(curr_substring) > len(longest_substring):
                longest_substring = curr_substring

        # Cast the count to a string for comparison to the database
        # As that gets loaded in as a string
        # Cast to int to truncate the decimal place
        count = str(int(len(longest_substring) / str_length))
        str_counts.append(count)

    # Checks if we have an exact match in our database
    for row in database:
        for i in range(len(str_counts)):
            # No Match
            if row[i + 1] != str_counts[i]:
                break
            # If we got to the end of the DNA sequence - Match Found
            elif i == len(str_counts) - 1:
                print(row[0])
                return

    # If we get this far we did not find a match
    print("No match")


main()