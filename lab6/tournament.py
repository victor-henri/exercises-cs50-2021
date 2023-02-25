import csv
import sys
import random


# Número de simulações
N = 1000

def main():

    # Assegura o uso correto
    if len(sys.argv) != 2:
        sys.exit("Usage: python tournament.py FILENAME")

    teams = []
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            teams.append({'team': row['team'], 'rating': int(row['rating'])})

    counts = {}
    # Simula N torneios e mantém um registo das contagens de vitórias
    for tournament in range(N):
        winner = simulate_tournament(teams)

        if winner not in counts:
            counts.update({winner: int(1)})
        else:
            value = int(counts[winner] + 1)
            counts.update({winner: value})
    print(counts)

    # Imprime as chances de vitória de cada equipe, de acordo com a simulação
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

    # Simula jogos para todos os pares de equipes
    for i in range(0, len(teams), 2):
        if simulate_game(teams[i], teams[i + 1]):
            winners.append(teams[i])
        else:
            winners.append(teams[i + 1])

    return winners


def simulate_tournament(teams):
    """Simulate a tournament. Return name of winning team."""
    while len(teams) > 1:
        teams = simulate_round(teams)

    return teams[0]['team']


if __name__ == "__main__":
    main()
