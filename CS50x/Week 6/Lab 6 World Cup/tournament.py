# Simulate a sports tournament

import csv
import sys
import random

# Number of simluations to run
N = 1000


def main():

    # Ensure correct usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    # TODO - DONE: Read teams into memory from file and store them in the teams array
    # as a dictionary, where each team will have name and rating value
    # using csv.DictReader read from the csv file and there store them in the teams dictionary
    with open(sys.argv[1]) as file:  # open the name of the file wrom the comnad in terminal
        reader = csv.DictReader(file)  # this leats us read the csv file as a dictionary on each line
        for team in reader:  # for each team in the file
            team["rating"] = int(team["rating"])  # the teams rating is a rating from the csv file converted to nuber
            teams.append(team)  # append the teams

    counts = {}
    # TODO - DONE: Simulate N tournaments and keep track of win counts
    # count is a dictonary, that maps key to values, the keys are the names
    # of the temas and the values are how many turnaments the team has won,
    # so if team wind 100 times, the name is gonna be the name and the value
    # is gonna be 100

    # the simulate_tournament function that simulates the N turnaments and then
    # keep track of the winners in the counts dictionary
    counts = {}
    for i in range(N):
        winner = simulate_tournament(teams)
        if winner in counts:  # if the winner is already in the dicionary increase number
            counts[winner] += 1
        else:  # esle declare the winnder with number 1 (first time they won tournament)
            counts[winner] = 1

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

    return winners  # returns list of the winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    # TODO - DONE #this should simulate the entire tournaments, starting
    # with all of the teams and repeatedly simulating rounds until
    # we are down to just one

    while len(teams) > 1:  # if tehrere is more than one team we have
        # to simulate another round
        teams = simulate_round(teams)
    return teams[0]["team"]  # i wanna only return the team's name from the teams


if __name__ == "__main__":
    main()
