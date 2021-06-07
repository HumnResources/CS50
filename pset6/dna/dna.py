from sys import argv
import csv

def main():
    if len(argv) != 3:
        print("Please double check your command arguments:\npython dna.py <STR-DB-Path> <DNA-file-path>")
        return

    # List of dicts for each person
    database = []

    # Read in database file containing people's DNA sequence's
    with open(argv[1], "r") as csvfile:
        reader = csv.DictReader(csvfile)
        for row in reader:
            database.append(row)

    # Read in DNA sequence to compare against
    file = open(argv[2], "r")
    dna = file.readline().strip()
    file.close()




main()