from cs50 import get_int

scores = []

for i in range(3):
    scores.append(get_int("score: "))


avg = sum(scores) / len(scores)

print(f"average: {avg}")
