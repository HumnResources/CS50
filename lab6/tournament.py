# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 10000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    counts = {}
    teams = []
    # Read teams into memory from file
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        if reader is None:
            print(f"Could not open file {sys.argv[1]}")

        # Adds header information to label k,v repsectively as team,rating
        next(reader)

        # Add to list of teams the name + rating
        # Populate team names for simulation scores
        i = 0
        for row in reader:
            key = row[0]
            val = int(row[1])
            teams.append({"team": key, "rating": val})
            counts[key] = 0
            i += 1

    # Simulate N tournaments and keep track of win counts
    for i in range(N):
        winner = simulate_tournament(teams)
        counts[winner] += 1

    # Print each team's chances of winning, according to simulation
    for team in sorted(counts, key=lambda team: counts[team], reverse=True):
        print(f"{team}: {counts[team] * 100 / N:.1f}% chance of winning")


def simulate_game(team1, team2):
    """Simulate a game. Return True if team1 wins, False otherwise."""
    rating1 = team1["rating"]
    rating2 = team2["rating"]
    probability = 1 / (1 + 10 ** ((rating2 - rating1) / 600))
    return random.random() < probability


def simulate_round(teams):
    """Simulate a round. Return a list of winning teams."""
    winners = []

    # Simulate games for all pairs of teams
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    if len(teams) == 1:
        return teams[0]["team"]

    # Recursively call updating winning teams each iteration
    # This simulates all games for all possible pairs
    for i in range(0, len(teams)):
        winners = simulate_round(teams)
        return simulate_tournament(winners)


if __name__ == "__main__":
    main()
